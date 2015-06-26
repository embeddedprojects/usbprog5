/*
 * USBprog 5.0 JTAG/SWD driver
 * heavily based on JTAG to VPI, bitbang and JLink driver
 *
 * Copyright (C) 2014, 2015 Benedikt Heinz, <Zn000h@gmail.com>
 * Copyright (C) 2013 Franck Jullien, <elec4fun@gmail.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <jtag/interface.h>
#include <jtag/swd.h>
#include <jtag/commands.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NO_TAP_SHIFT	0
#define TAP_SHIFT		1

volatile uint32_t *iomem;

#define IOCFG_BASE	0x13003000
#define IOCFG_END 	0x13003200

#define IOCFG_GPIO		(0x1C0/4)
#define IOCFG_SPI		(0x240/4)

/* mode bits:
 * m1=0, m0=0: input
 * m1=0, m0=1: output controlled by device
 * m1=1, m0=0: output low
 * m1=1, m0=1: output high
 */

#define IO_PINS			(0/4)
#define IO_MODE0		(0x10/4)
#define IO_MODE0_SET	(0x14/4)
#define IO_MODE0_RESET	(0x18/4)
#define IO_MODE1		(0x20/4)
#define IO_MODE1_SET	(0x24/4)
#define IO_MODE1_RESET	(0x28/4)

/* GPIO mapping:
 * 18: TDO
 * 17: TCK
 *  2: TDI
 * 16: SRST
 * 13: TMS
 * 12: TRST
 */
//#define GPIO_TDO_BIT	12
#define GPIO_TCK_BIT	11
//#define GPIO_TDI_BIT	2
#define GPIO_SRST_BIT	10
#define GPIO_TMS_BIT	7
#define GPIO_TRST_BIT	6

#define SPI_MISO_BIT	0
#define SPI_MOSI_BIT	1
#define SPI_CSIN_BIT	2
#define SPI_SCK_BIT		3
#define SPI_CSOUT_BIT	4

volatile uint32_t *spimem;

#define SPI_BASE	0x15002000
#define SPI_END		0x15003000

#define SPI_CONFIG			(0/4)
#define SPI_SLAVE_ENABLE	(4/4)
#define SPI_TXFIFO_FLUSH	(8/4)
#define SPI_FIFO_DATA		(0xC/4)
#define SPI_NHP_POP			(0x10/4)
#define SPI_NHP_MODE		(0x14/4)
#define SPI_DMA_SETTINGS	(0x18/4)
#define SPI_STATUS			(0x1C/4)
#define SPI_HW_INFO			(0x20/4)

#define SPI_SLV0_SETTINGS1	(0x24/4)
#define SPI_SLV0_SETTINGS2	(0x28/4)
#define SPI_SLV1_SETTINGS1	(0x2C/4)
#define SPI_SLV1_SETTINGS2	(0x30/4)
#define SPI_SLV2_SETTINGS1	(0x34/4)
#define SPI_SLV2_SETTINGS2	(0x38/4)

#define SPI_INT_THRESHOLD	(0xFD4/4)
#define SPI_INT_CLR_ENABLE	(0xFD8/4)
#define SPI_INT_SET_ENABLE	(0xFDC/4)
#define SPI_INT_STATUS		(0xFE0/4)
#define SPI_INT_ENABLE		(0xFE4/4)
#define SPI_CLR_STATUS		(0xFE8/4)
#define SPI_SET_STATUS		(0xFEC/4)

#define SPI_CFG_UPDATE_EN	7
#define SPI_CFG_RESET		6	
#define SPI_CFG_SPI_EN		0

#define SPI_TXFLUSH			0

#define SPI_STATUS_BUSY		4
#define SPI_STATUS_RXFULL	3
#define SPI_STATUS_RXEMPTY	2
#define SPI_STATUS_TXFULL	1
#define SPI_STATUS_TXEMPTY	0

#define FIFO_DEPTH			64

/* f_sck = f_spiclk / (div2 * (div1+1)) - f_spiclk: 90 MHz */
#define SPI_SLVx1_DIV2		8
#define SPI_SLVx1_DIV1		0

#define SPI_PCLK			90000000

#define SPI_MAX_DIVIDER 	65024
#define SPI_MIN_DIVIDER		2

/* ~100ns per iteration (18*5.55ns)
 * base delay w/ val=0: 290 ns
 */
static void udelay(uint32_t val) {
	do {
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
	} while(val--);
}

static uint32_t tck_halfcycle_delay = 10;
static int swd_mode = 0;
static int queued_retval = ERROR_OK;

static void spi_init(uint32_t freq)
{
	uint32_t div1, div2, halfcycle_ns;
	/* div1, div2 calculation is stolen from the Linux kernel :) */
	uint32_t clkdiv = (SPI_PCLK + freq / 2) / freq;
	if (clkdiv > SPI_MAX_DIVIDER)
		clkdiv = SPI_MAX_DIVIDER;
	if (clkdiv < SPI_MIN_DIVIDER)
		clkdiv = SPI_MIN_DIVIDER;

	div2 = (((clkdiv - 1) / 512) + 1) * 2;
	div1 = (((clkdiv + div2 / 2) / div2) - 1);

	/* halfcycle in nanoseconds */
	halfcycle_ns = (1000000000/freq)>>1;
	
	/* minimum udelay invocation time: 290 ns */
	if (halfcycle_ns <= 290)
		tck_halfcycle_delay = 0;
	else
		tck_halfcycle_delay = ((halfcycle_ns - 290) / 100)+1;

	/* UM10314 SPI programming guide:
	 * - set slave_settings1,2
	 * - set slave_enable
	 * - set spi_config
	 * - enable bit in spi_config for start on fifo write
	 * - write to data reg
	 */
	 
	/* reset SPI peripheral */
	spimem[SPI_CONFIG] = (1<<SPI_CFG_RESET);

	/* slave config */
	spimem[SPI_SLV0_SETTINGS1] = (div2&0xff)<<SPI_SLVx1_DIV2 | (div1&0xff)<<SPI_SLVx1_DIV1;

	/* TODO: verify phase */
	spimem[SPI_SLV0_SETTINGS2] = 7;

	/* slave enable */
	spimem[SPI_SLAVE_ENABLE] = 1;

	/* update slave config */
	spimem[SPI_CONFIG] = (1<<SPI_CFG_UPDATE_EN);

	/* wait until new config applied */
	while((spimem[SPI_CONFIG]>>SPI_CFG_UPDATE_EN)&1) {}
	
	/* enable transmissions on fifo data write */
	spimem[SPI_CONFIG] = (1<<SPI_CFG_SPI_EN);
}

/**
 * usbp5_reset - ask to reset the JTAG device
 * @trst: 1 if TRST is to be asserted
 * @srst: 1 if SRST is to be asserted
 */
static int usbp5_reset(int trst, int srst)
{
	int ofs;
	
	/* nTRST and nSRST are low active */
	
	ofs = trst ? IO_MODE0_RESET : IO_MODE0_SET;
	iomem[IOCFG_GPIO + ofs] = 1<<GPIO_TRST_BIT;
	
	ofs = srst ? IO_MODE0_RESET : IO_MODE0_SET;
	iomem[IOCFG_GPIO + ofs] = 1<<GPIO_SRST_BIT;
	
	return 0;
}

static int iomem_init(void)
{
	int fd = open("/dev/mem", O_RDWR | O_SYNC);
	if (fd < 0)
		return fd;
		
	iomem =
	    (volatile uint32_t *)mmap(NULL, IOCFG_END - IOCFG_BASE,
				      PROT_READ | PROT_WRITE, MAP_SHARED, fd,
				      IOCFG_BASE);
		
	spimem =
	    (volatile uint32_t *)mmap(NULL, SPI_END - SPI_BASE,
				      PROT_READ | PROT_WRITE, MAP_SHARED, fd,
				      SPI_BASE);
					      
	close(fd);

	if (iomem == MAP_FAILED)
		return -1;
	if (spimem == MAP_FAILED)
		return -1;

	/* configure SPI IOs for SPI mode */
	iomem[IOCFG_SPI + IO_MODE0] = 0x1f;
	iomem[IOCFG_SPI + IO_MODE1] = 0;
		
	/* configure TCK and TMS as general purpose outputs, drive low */
	iomem[IOCFG_GPIO + IO_MODE0_RESET] = (1<<GPIO_TCK_BIT) | (1<<GPIO_TMS_BIT);
	iomem[IOCFG_GPIO + IO_MODE1_SET] = (1<<GPIO_TCK_BIT) | (1<<GPIO_TMS_BIT);
	
	/* configure nTRST and nSRST as outputs, drive hi (inactive) */
	iomem[IOCFG_GPIO + IO_MODE0_SET] = (1<<GPIO_TRST_BIT) | (1<<GPIO_SRST_BIT);
	iomem[IOCFG_GPIO + IO_MODE1_SET] = (1<<GPIO_TRST_BIT) | (1<<GPIO_SRST_BIT);
	
	return 0;
}

static void iomem_close(void)
{
	munmap((void *)iomem, IOCFG_END - IOCFG_BASE);
	munmap((void *)spimem, SPI_END - SPI_BASE);
}

/* always leave TCK in low state when returning */

/**
 * usbp5_tms_seq - ask a TMS sequence transition to JTAG
 * @bits: TMS bits to be written (bit0, bit1 .. bitN)
 * @nb_bits: number of TMS bits (between 1 and 8)
 *
 * Write a serie of TMS transitions, where each transition consists in :
 *  - writing out TCK=0, TMS=<new_state>, TDI=<???>
 *  - writing out TCK=1, TMS=<new_state>, TDI=<???> which triggers the transition
 * The function ensures that at the end of the sequence, the clock (TCK) is put
 * low.
 */
/* bit order: least significant first */
static int usbp5_tms_seq(const uint8_t *bits, int nb_bits) {
	int ofs, bitcnt, n_bytes = DIV_ROUND_UP(nb_bits, 8);
	uint8_t bytebuf;

	for(; n_bytes; n_bytes--, bits++) {
		bytebuf = *bits;
		bitcnt = MIN(nb_bits, 8);
		
		for(;bitcnt;bitcnt--) {
			// (re)set TMS
			ofs = IOCFG_GPIO + IO_MODE0_SET + ((bytebuf&1)^1);
			iomem[ofs] = (1<<GPIO_TMS_BIT);
			udelay(tck_halfcycle_delay);
			
			// set TCK hi
			iomem[IOCFG_GPIO + IO_MODE0_SET] = (1<<GPIO_TCK_BIT);
			udelay(tck_halfcycle_delay);
			
			// set TCK low
			iomem[IOCFG_GPIO + IO_MODE0_RESET] = (1<<GPIO_TCK_BIT);
			
			bytebuf>>=1;
		}
		/* if nb_bits gets negative we don't care b/c in that case 
		 * it was the last loop cycle anyway */
		nb_bits -= 8;
	}
	return ERROR_OK;
}

static const unsigned char bitrev[] = 
{
  0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0, 
  0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8, 
  0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4, 
  0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC, 
  0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2, 
  0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
  0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6, 
  0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
  0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
  0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9, 
  0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
  0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
  0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3, 
  0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
  0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7, 
  0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF
};

 /*
  * - set TMS low
  * - shift all but last bit (copy data to SPI data fifo)
  * - wait until fifo done, read all rxbytes
  * - set TMS hi while shifting the last bit
  * 
  * tap_shift: set TMS hi during last bit
  */
/* bit order: least significant first */
static int usbp5_tdi_seq(const uint8_t *txbits, uint8_t *rxbits, int nb_bits, int tap_shift)
{
	uint8_t rxbuf, txbuf = 0; //OR: swd_en ? 0 : 0xff;
	int i, ofs, n_bytes_rx, n_bytes_tx;
	/* special handling for dummy data (tx/rxbits == NULL) during RUNTEST, etc. */
	int txstride = txbits ? 1 : 0;
	int rxstride = rxbits ? 1 : 0;
	uint8_t *rxptr = rxstride ? rxbits : &rxbuf;
	const uint8_t *txptr = txstride ? txbits : &txbuf;
	uint32_t status;
		
	if(!nb_bits)
		return ERROR_OK;
	
	/* set TMS low */
	iomem[IOCFG_GPIO + IO_MODE0_RESET] = (1<<GPIO_TMS_BIT);
	
	n_bytes_rx = n_bytes_tx = DIV_ROUND_UP(nb_bits, 8);
	
	/* we can use the SPI peripheral only to transmit full bytes and
	 * only as long as we do not need a TMS transition
	 * 
	 * we cannot transmit the last byte if less than 8 bits are used
	 * or if we need a TMS transition */
	if( (tap_shift) || (nb_bits&7) ) {
		n_bytes_rx--;
		n_bytes_tx--;
	}
	
	/* remainder - handled w/ bitbanging */
	nb_bits -= n_bytes_rx<<3;
	
	for( ; n_bytes_tx ; n_bytes_tx-- , txptr+=txstride) {
		
		/* busywait
		 * - receive one byte if possible to avoid RX overflows
		 * - wait until TX fifo has at least one free entry
		 */
		do {
			status = spimem[SPI_STATUS];
			if(!(status&(1<<SPI_STATUS_RXEMPTY))) {
				*rxptr = bitrev[spimem[SPI_FIFO_DATA]];
				rxptr+=rxstride;
				n_bytes_rx--;
			}
		} while(status&(1<<SPI_STATUS_TXFULL));
		
		/* send one byte */
		spimem[SPI_FIFO_DATA] = bitrev[*txptr];
	}
	
	/* wait until we received everything */
	do {
		status = spimem[SPI_STATUS];
		if(!(status&(1<<SPI_STATUS_RXEMPTY))) {
			*rxptr = bitrev[spimem[SPI_FIFO_DATA]];
			rxptr+=rxstride;
			n_bytes_rx--;
		}
	} while(n_bytes_rx);
	
	if(!nb_bits)
		return ERROR_OK;
	
	/* handle remainder */
	
	/* switch MOSI/TDI to general purpose output */
	iomem[IOCFG_SPI + IO_MODE1_SET] = (1<<SPI_MOSI_BIT);
	
	/* special handling for last bit if TMS action needed */
	nb_bits -= tap_shift;
	
	/* process all remaining bits if no TMS action needed
	 * otherwise process all bits but the last one */
	txbuf = *txptr;
	rxbuf = 0;
	for(i=0; i<nb_bits;	i++) {
		/* (re)set TDI */
		ofs = IOCFG_SPI + IO_MODE0_SET + ((txbuf&1)^1);
		iomem[ofs] = (1<<SPI_MOSI_BIT);
		udelay(tck_halfcycle_delay);
		
		/* sample TDO */
		rxbuf |= ((iomem[IOCFG_SPI + IO_PINS]>>SPI_MISO_BIT)&1)<<i;
		
		// set TCK hi
		iomem[IOCFG_GPIO + IO_MODE0_SET] = (1<<GPIO_TCK_BIT);
		udelay(tck_halfcycle_delay);
			
		// set TCK low
		iomem[IOCFG_GPIO + IO_MODE0_RESET] = (1<<GPIO_TCK_BIT);

		txbuf >>= 1;
	}
	
	if(!tap_shift)
		goto done;
	
	/* handle final bit with TMS transition */
	
	/* set TMS hi */
	iomem[IOCFG_GPIO + IO_MODE0_SET] = (1<<GPIO_TMS_BIT);
	
	/* (re)set TDI */
	ofs = IOCFG_SPI + IO_MODE0_SET + ((txbuf&1)^1);
	iomem[ofs] = (1<<SPI_MOSI_BIT);
	udelay(tck_halfcycle_delay);
		
	/* sample TDO */
	rxbuf |= ((iomem[IOCFG_SPI + IO_PINS]>>SPI_MISO_BIT)&1)<<i;
		
	// set TCK hi
	iomem[IOCFG_GPIO + IO_MODE0_SET] = (1<<GPIO_TCK_BIT);
	udelay(tck_halfcycle_delay);
			
	// set TCK low
	iomem[IOCFG_GPIO + IO_MODE0_RESET] = (1<<GPIO_TCK_BIT);
	
done:
	/* reset GPIO TDI so we can use the SPI peripheral again 
	 * otherwise the OR gate would keep TDI high 
	 * TODO: later if dedicated TDI GPIO */
	// iomem[IOCFG_GPIO + IO_MODE0_RESET] = (1<<GPIO_TDI_BIT);
	
	/* switch MOSI/TDI back to MOSI */
	iomem[IOCFG_SPI + IO_MODE1_RESET] = (1<<SPI_MOSI_BIT);
	iomem[IOCFG_SPI + IO_MODE0_SET] = (1<<SPI_MOSI_BIT);
	
	/* store final rxbyte */
	*rxptr = rxbuf;
	
	return ERROR_OK;	
}

/**
 * usbp5_path_move - ask a TMS sequence transition to JTAG
 * @cmd: path transition
 *
 * Write a serie of TMS transitions, where each transition consists in :
 *  - writing out TCK=0, TMS=<new_state>, TDI=<???>
 *  - writing out TCK=1, TMS=<new_state>, TDI=<???> which triggers the transition
 * The function ensures that at the end of the sequence, the clock (TCK) is put
 * low.
 */

static int usbp5_path_move(struct pathmove_command *cmd)
{
	uint8_t trans[DIV_ROUND_UP(cmd->num_states, 8)];

	memset(trans, 0, DIV_ROUND_UP(cmd->num_states, 8));

	for (int i = 0; i < cmd->num_states; i++) {
		if (tap_state_transition(tap_get_state(), true) == cmd->path[i])
			buf_set_u32(trans, i, 1, 1);
		tap_set_state(cmd->path[i]);
	}

	return usbp5_tms_seq(trans, cmd->num_states);
}

/**
 * usbp5_tms - ask a tms command
 * @cmd: tms command
 */
static int usbp5_tms(struct tms_command *cmd)
{
	return usbp5_tms_seq(cmd->bits, cmd->num_bits);
}

static int usbp5_state_move(tap_state_t state)
{
	if (tap_get_state() == state)
		return ERROR_OK;

	uint8_t tms_scan = tap_get_tms_path(tap_get_state(), state);
	int tms_len = tap_get_tms_path_len(tap_get_state(), state);

	int retval = usbp5_tms_seq(&tms_scan, tms_len);
	if (retval != ERROR_OK)
		return retval;

	tap_set_state(state);

	return ERROR_OK;
}

/**
 * usbp5_clock_tms - clock a TMS transition
 * @tms: the TMS to be sent
 *
 * Triggers a TMS transition (ie. one JTAG TAP state move).
 */
static int usbp5_clock_tms(int tms)
{
	const uint8_t tms_0 = 0;
	const uint8_t tms_1 = 1;

	return usbp5_tms_seq(tms ? &tms_1 : &tms_0, 1);
}

/**
 * usbp5_scan - launches a DR-scan or IR-scan
 * @cmd: the command to launch
 *
 * Launch a JTAG IR-scan or DR-scan
 *
 * Returns ERROR_OK if OK, ERROR_xxx if a read/write error occured.
 */
static int usbp5_scan(struct scan_command *cmd)
{
	int scan_bits;
	uint8_t *buf = NULL;
	int retval = ERROR_OK;

	scan_bits = jtag_build_buffer(cmd, &buf);

	if (cmd->ir_scan) {
		retval = usbp5_state_move(TAP_IRSHIFT);
		if (retval != ERROR_OK)
			return retval;
	} else {
		retval = usbp5_state_move(TAP_DRSHIFT);
		if (retval != ERROR_OK)
			return retval;
	}

	if (cmd->end_state == TAP_DRSHIFT) {
		retval = usbp5_tdi_seq(buf, buf, scan_bits, NO_TAP_SHIFT);
		if (retval != ERROR_OK)
			return retval;
	} else {
		retval = usbp5_tdi_seq(buf, buf, scan_bits, TAP_SHIFT);
		if (retval != ERROR_OK)
			return retval;
	}

	if (cmd->end_state != TAP_DRSHIFT) {
		/*
		 * As our JTAG is in an unstable state (IREXIT1 or DREXIT1), move it
		 * forward to a stable IRPAUSE or DRPAUSE.
		 */
		retval = usbp5_clock_tms(0);
		if (retval != ERROR_OK)
			return retval;

		if (cmd->ir_scan)
			tap_set_state(TAP_IRPAUSE);
		else
			tap_set_state(TAP_DRPAUSE);
	}

	retval = jtag_read_buffer(buf, cmd);
	if (retval != ERROR_OK)
		return retval;

	if (buf)
		free(buf);

	if (cmd->end_state != TAP_DRSHIFT) {
		retval = usbp5_state_move(cmd->end_state);
		if (retval != ERROR_OK)
			return retval;
	}

	return ERROR_OK;
}

static int usbp5_runtest(int cycles, tap_state_t state)
{
	int retval;

	retval = usbp5_state_move(TAP_IDLE);
	if (retval != ERROR_OK)
		return retval;

	retval = usbp5_tdi_seq(NULL, NULL, cycles, NO_TAP_SHIFT);
	if (retval != ERROR_OK)
		return retval;

	return usbp5_state_move(state);
}

static int usbp5_stableclocks(int cycles)
{
	return usbp5_tdi_seq(NULL, NULL, cycles, NO_TAP_SHIFT);
}

static int usbp5_execute_queue(void)
{
	struct jtag_command *cmd;
	int retval = ERROR_OK;

	for (cmd = jtag_command_queue; retval == ERROR_OK && cmd != NULL;
	     cmd = cmd->next) {
		switch (cmd->type) {
		case JTAG_RESET:
			retval = usbp5_reset(cmd->cmd.reset->trst, cmd->cmd.reset->srst);
			break;
		case JTAG_RUNTEST:
			retval = usbp5_runtest(cmd->cmd.runtest->num_cycles,
						  cmd->cmd.runtest->end_state);
			break;
		case JTAG_STABLECLOCKS:
			retval = usbp5_stableclocks(cmd->cmd.stableclocks->num_cycles);
			break;
		case JTAG_TLR_RESET:
			retval = usbp5_state_move(cmd->cmd.statemove->end_state);
			break;
		case JTAG_PATHMOVE:
			retval = usbp5_path_move(cmd->cmd.pathmove);
			break;
		case JTAG_TMS:
			retval = usbp5_tms(cmd->cmd.tms);
			break;
		case JTAG_SLEEP:
			jtag_sleep(cmd->cmd.sleep->us);
			break;
		case JTAG_SCAN:
			retval = usbp5_scan(cmd->cmd.scan);
			break;
		default:
			fprintf(stderr,"[usbprog5] unhandled command: %d\n",cmd->type);
			exit(23);
		}
	}

	return retval;
}

static int usbp5_khz(int khz, int *jtag_speed)
{
	spi_init(khz*1000);
	if(jtag_speed)
		*jtag_speed=khz;
	return ERROR_OK;
}

static int usbp5_speed(int speed)
{
	int dummy;

	return usbp5_khz(speed, &dummy);
}

static int usbp5_speed_div(int speed, int *khz)
{
	*khz = speed;

	return ERROR_OK;
}

static int usbp5_init(void)
{
	int res = iomem_init();
	if(res)
		return res;
	spi_init(100000);
	return ERROR_OK;
}

static int usbp5_quit(void)
{
	iomem_close();
	return ERROR_OK;
}

/* YUK! - but this is currently a global.... */
extern struct jtag_interface *jtag_interface;

static void swd_clear_sticky_errors(struct adiv5_dap *dap)
{
	const struct swd_driver *swd = jtag_interface->swd;
	assert(swd);

	swd->write_reg(dap, swd_cmd(false,  false, DP_ABORT),
		STKCMPCLR | STKERRCLR | WDERRCLR | ORUNERRCLR);
}

static void usbp5_swd_cmd(struct adiv5_dap *dap, uint8_t cmd, uint32_t *dst, uint32_t data)
{
	uint32_t buf32[2];
	uint8_t *buf8 = (uint8_t *)buf32;
	uint8_t ack;
	int parity=0;
	
	if (queued_retval != ERROR_OK)
		return;

	cmd |= SWD_CMD_START | SWD_CMD_PARK;
	usbp5_tdi_seq(&cmd, NULL, 8, NO_TAP_SHIFT);

	/* read */
	if (cmd & SWD_CMD_RnW) {
		usbp5_tdi_seq(NULL, &ack, 3+1, NO_TAP_SHIFT);
		ack>>=1;
		usbp5_tdi_seq(NULL, buf8, 32 + 1 + 1, NO_TAP_SHIFT);
		parity = buf8[4];
		if (parity != parity_u32(*buf32)) {
			LOG_DEBUG("Wrong parity detected - is: %x should: %x",parity,parity_u32(*buf32));
			queued_retval = ERROR_FAIL;
		}
		if(dst)
			*dst = *buf32;
		
	/* write */
	} else {
		usbp5_tdi_seq(NULL, &ack, 3+1+1, NO_TAP_SHIFT);
		ack>>=1;
		ack&=7;
		*buf32 = data;
		buf8[4] = parity_u32(data);
		usbp5_tdi_seq(buf8, NULL, 32 + 1, NO_TAP_SHIFT);
	}

	/* Insert idle cycles after AP accesses to avoid WAIT */
	if (cmd & SWD_CMD_APnDP)
		usbp5_tdi_seq(NULL, NULL, dap->memaccess_tck, NO_TAP_SHIFT);
	
	switch (ack) {
	 case SWD_ACK_OK:
		break;
	 case SWD_ACK_WAIT:
		LOG_DEBUG("SWD_ACK_WAIT");
		swd_clear_sticky_errors(dap);
		break;
	 case SWD_ACK_FAULT:
		LOG_DEBUG("SWD_ACK_FAULT");
		queued_retval = ack;
		break;
	 default:
		LOG_DEBUG("No valid acknowledge: ack=%d", ack);
		queued_retval = ack;
		break;
	}
}

static int usbp5_swd_init(void)
{
	LOG_INFO("USBprog5 SWD mode enabled");
	swd_mode = 1;
	return ERROR_OK;
}

static int_least32_t usbp5_swd_frequency(struct adiv5_dap *dap, int_least32_t hz)
{
	if (hz > 0)
		usbp5_khz(hz / 1000, NULL);

	return hz;
}

static int usbp5_swd_switch_seq(struct adiv5_dap *dap, enum swd_special_seq seq)
{
	const uint8_t *s;
	unsigned int s_len;

	switch (seq) {
	case LINE_RESET:
		LOG_DEBUG("SWD line reset");
		s = swd_seq_line_reset;
		s_len = swd_seq_line_reset_len;
		break;
	case JTAG_TO_SWD:
		LOG_DEBUG("JTAG-to-SWD");
		s = swd_seq_jtag_to_swd;
		s_len = swd_seq_jtag_to_swd_len;
		break;
	case SWD_TO_JTAG:
		LOG_DEBUG("SWD-to-JTAG");
		s = swd_seq_swd_to_jtag;
		s_len = swd_seq_swd_to_jtag_len;
		break;
	default:
		LOG_ERROR("Sequence %d not supported", seq);
		return ERROR_FAIL;
	}

	usbp5_tdi_seq(s, NULL, s_len, NO_TAP_SHIFT);

	return ERROR_OK;
}

static void usbp5_swd_read_reg(struct adiv5_dap *dap, uint8_t cmd, uint32_t *value)
{
	assert(cmd & SWD_CMD_RnW);
	usbp5_swd_cmd(dap, cmd, value, 0);
}

static void usbp5_swd_write_reg(struct adiv5_dap *dap, uint8_t cmd, uint32_t value)
{
	assert(!(cmd & SWD_CMD_RnW));
	usbp5_swd_cmd(dap, cmd, NULL, value);
}

static int usbp5_swd_run_queue(struct adiv5_dap *dap)
{
	int retval;
	/* A transaction must be followed by another transaction or at least 8 idle cycles to
	 * ensure that data is clocked through the AP. */
	usbp5_tdi_seq(NULL, NULL, 8, NO_TAP_SHIFT);
	retval = queued_retval;
	queued_retval = ERROR_OK;
	LOG_DEBUG("SWD queue return value: %02x", retval);
	return retval;
}

static const struct command_registration usbp5_command_handlers[] = {
	COMMAND_REGISTRATION_DONE
};

static const char * const usbp5_transports[] = {"jtag", "swd", NULL};

static const struct swd_driver usbprog5_swd = {
	.init = usbp5_swd_init,
	.frequency = usbp5_swd_frequency,
	.switch_seq = usbp5_swd_switch_seq,
	.read_reg = usbp5_swd_read_reg,
	.write_reg = usbp5_swd_write_reg,
	.run = usbp5_swd_run_queue
};

struct jtag_interface usbprog5_interface = {
	.name = "usbprog5",
	.supported = DEBUG_CAP_TMS_SEQ,
	.commands = usbp5_command_handlers,
	.transports = usbp5_transports,
	.swd = &usbprog5_swd,

	.khz = usbp5_khz,
	.speed = usbp5_speed,
	.speed_div = usbp5_speed_div,

	.init = usbp5_init,
	.quit = usbp5_quit,
	.execute_queue = usbp5_execute_queue,
};
