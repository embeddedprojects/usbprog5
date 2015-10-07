/*
 * modified AVR1612 appnote for PDI programming
 * modifications by hunz@mailbox.org
 * see license conditions for original appnote below
 * modified parts may be redistributed under the
 * same conditions as the original code from Atmel
 */

/**
 * \file main.c
 *
 * \brief PDI programmer unit test.
 *
 * This file defines various status codes returned by functions,
 * indicating success or failure as well as what kind of failure.
 *
 * Copyright (C) 2009 Atmel Corporation. All rights reserved.
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 * Atmel AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */
#include "config.h"

/* PDI driver includes */
#include <atxmega128a1_nvm_regs.h>
#include <xmega_pdi_nvm.h>

#include <util/delay.h>

#include <status_codes.h>

#include <avr/interrupt.h>
#include <avr/power.h>
//#include <avr/sleep.h>

/* 1: Mega48
 * 2: AVR SPI code
 * 3: LPC SPI code
 */ 

/* extra signal for ready/busy: PB1 */

#define SPI_BUFSIZE		(1+4+2+1+256+5)
static volatile uint8_t spibuf[SPI_BUFSIZE] = { 0 };
static volatile uint8_t *spiptr = spibuf;

#define STATUS_READY	0x80
#define STATUS_ERROR	0x40
#define STATUS_ERRORMASK	0x3F

static volatile uint8_t status =0 ;

#define CMD_NEW			0x80
#define CMD_MASK		0x3f

#define ID_MAGIC1		0xc2
#define ID_MAGIC2		0xd8

#define VERSION_MSB		1
#define VERSION_LSB		0

/* normal non-buffer commands */
enum {
	CMD_NOP 		= 0x00,
	CMD_INIT 		= 0x01,
	CMD_DEINIT 		= 0x02,
	CMD_CHIPERASE 	= 0x03,
	CMD_WRITEFUSE	= 0x04,
	CMD_WRITEUSERSIGN	= 0x05,
	
	CMD_ID 			= 0x10,
	CMD_READ 		= 0x11,
};

#define CMD_BUFFER		0x20

#define BUFFER_ERASE	0x10

enum {
	WRMODE_NONE			= 0,
	WRMODE_ERASE		= 4,
	WRMODE_WRITE		= 8,
	WRMODE_ERASE_WRITE	= 0xc
};

enum {
	DST_FLASH 		= 0,
	DST_FLASH_APP 	= 1,
	DST_FLASH_BOOT	= 2,
	DST_EEPROM		= 3
};

#define DST_MASK		3

static volatile uint8_t rx_complete=0;

ISR(INT0_vect)
{
	uint8_t edge=(EICRA & (1<<ISC00));
	
	// falling edge: load SPDR with current status, set pointer if not busy
	if(!edge) {
		SPDR = status;
		spiptr = (status&STATUS_READY) ? spibuf : NULL;
		status = 0; // clear ready flag
		PORTB &= ~(1<<PB1); // set busy flag
		PORTD|=(1<<PD7); // busy LED
	}
	else
		rx_complete=1;
	
	EICRA = edge ^ (1<<ISC00);
}

ISR(SPI_STC_vect)
{
	if(spiptr) {
		uint8_t tmp = SPDR;
		SPDR = *spiptr;
		*spiptr = tmp;
		spiptr++;
		if(spiptr >= (spibuf+SPI_BUFSIZE))
			spiptr=NULL;
	}
	else
		SPDR = status;
}

static uint8_t pdi_connected = 0;

/* cmd bits 3,2: write mode (0: nop, 1: erase, 2: write, 3: erase + write)
 * cmd bits 1,0: dst (0: flash, 1: app, 2: boot, 3: eeprom)
 */
static const uint8_t write_cmds[12] = {
	/* erase */
	XNVM_CMD_ERASE_FLASH_PAGE,
	XNVM_CMD_ERASE_APP_PAGE,
	XNVM_CMD_ERASE_BOOT_PAGE,
	XNVM_CMD_ERASE_EEPROM_PAGE,
	
	/* write */
	XNVM_CMD_WRITE_FLASH_PAGE,
	XNVM_CMD_WRITE_APP_SECTION,
	XNVM_CMD_WRITE_BOOT_PAGE,
	XNVM_CMD_WRITE_EEPROM_PAGE,
	
	/* erase + write */
	XNVM_CMD_ERASE_AND_WRITE_FLASH_PAGE,
	XNVM_CMD_ERASE_AND_WRITE_APP_SECTION,
	XNVM_CMD_ERASE_AND_WRITE_BOOT_PAGE,
	XNVM_CMD_ERASE_AND_WRITE_EEPROM
};

static uint8_t checksum(const volatile uint8_t *d, uint16_t len) {
	uint8_t val = 0x55;
	for(;len;len--,d++)
		val ^= *d;
	return val;
}

static uint8_t cmd_buffer(uint32_t addr, volatile uint8_t *d, uint16_t len) {
	uint8_t cmd = spibuf[0];
	uint8_t wr_cmd = cmd&0xf;
	uint8_t dst_eeprom = ((cmd&DST_MASK)==DST_EEPROM);
	enum status_code ret = STATUS_OK;
	
	/* buffer erase flag */
	if(cmd & BUFFER_ERASE) {
		/* erase buffer */
		ret = xnvm_erase_buffer(dst_eeprom, WAIT_RETRIES_NUM);
		if(ret != STATUS_OK)
			return ret;
		/* start load buffer */
		ret = xnvm_ctrl_cmd_write(dst_eeprom ? XNVM_CMD_LOAD_EEPROM_PAGE_BUFFER : XNVM_CMD_LOAD_FLASH_PAGE_BUFFER);
		if(ret != STATUS_OK)
			return ret;
		ret = xnvm_st_ptr(addr);
		if(ret != STATUS_OK)
			return ret;
	}
	
	/* load buffer */
	if(len) {
		ret = xnvm_load_buffer(d,len);
		if(ret != STATUS_OK)
			return ret;
	}
	
	/* erase/write command */
	if(wr_cmd >= 4) {
		ret = xnvm_ctrl_cmd_write(write_cmds[wr_cmd-4]);
		if(ret != STATUS_OK)
			return ret;
		
		/* Dummy write for starting the erase and write command */
		ret = xnvm_st_ptr(addr);
		if(ret != STATUS_OK)
			return ret;
		
		ret = xnvm_st_star_ptr_postinc(DUMMY_BYTE);
		if(ret != STATUS_OK)
			return ret;
		
		ret = xnvm_ctrl_wait_nvmbusy(WAIT_RETRIES_NUM);
	}
	return ret;
}

static uint8_t process_cmd(void) {
	uint32_t addr = spibuf[1]|((uint32_t)spibuf[2]<<8)|(((uint32_t)spibuf[3])<<16)|(((uint32_t)spibuf[4])<<24);
	uint16_t len = spibuf[5]|(((uint16_t)spibuf[6])<<8);
	uint8_t cmd = spibuf[0];
	enum status_code ret = STATUS_OK;
	
	if(len > 256)
		return STATUS_ERROR | 8;
	
	if(cmd & CMD_BUFFER) {
		if(len) {
			/* verify checksum */
			if(checksum(spibuf+8,len+1))
				return STATUS_ERROR | 4;
		}
		ret = cmd_buffer(addr,spibuf+8,len);
		goto out;
	}
	
	switch(cmd&CMD_MASK) {
		case CMD_NOP:
			break;
		case CMD_ID:
			spibuf[7]=ID_MAGIC1;
			spibuf[8]=ID_MAGIC2;
			spibuf[9]=VERSION_MSB;
			spibuf[10]=VERSION_LSB;
			spibuf[11]=checksum(spibuf+7,4);
			break;
		case CMD_INIT:
			ret = xnvm_init(addr&0xff);
			if(ret == STATUS_OK) {
				PORTB|=(1<<PB0);
				pdi_connected = 1;
			}
			break;
		case CMD_DEINIT:
			PORTB&=~(1<<PB0);
			pdi_connected=0;
			ret = xnvm_deinit();
			break;
		case CMD_CHIPERASE:
			ret = xnvm_chip_erase();
			break;
		case CMD_READ:
			ret = xnvm_read_memory(addr,(uint8_t*)(spibuf+7),len);
			spibuf[7+len] = checksum(spibuf+7,len);
			//ret = (ret == len) ? 0 : ERR_IO_ERROR;
			break;
		case CMD_WRITEFUSE:
			/* verify checksum */
			if(spibuf[8] ^ spibuf[9] ^ 0x55)
				return STATUS_ERROR | 4;
			ret = xnvm_write_fuse_bit(addr, spibuf[8], 1000);
			break;
		case CMD_WRITEUSERSIGN:
			/* load buffer */
			if(len) {
				/* verify checksum */
				if(checksum(spibuf+8,len+1))
					return STATUS_ERROR | 4;
					
				ret = xnvm_load_buffer(spibuf+8,len);
				if(ret != STATUS_OK)
					return ret;
			}
			/* erase + write buffer */
			ret = xnvm_erase_program_user_sign();
			break;
		default:
			ret = ERR_INVALID_ARG;
	}
out:
	if(ret > 0) ret = 0;
	return ret ? (((ret)&STATUS_ERRORMASK)|STATUS_ERROR) : 0;
}
 
/* TODOs: 
 * timeouts for all commands 
 * set baudrate
 * spi checksum
 * */

int main(void) {
	
	/* use 8MHz/2 = 4MHz clock (max. freq. for 1.8V operation) */
	clock_prescale_set(clock_div_2);
	
	/* Set MISO output, all others input */
	DDRB = (1<<PB4);
	
	DDRB |= (1<<PB1); // ready/busy
	PORTB &= ~(1<<PB1);
	
	DDRB |= (1<<PB0); // LEDs
	DDRD |= (1<<PD7);
	
	
	PORTB&=~(1<<PB0);
	PORTD&=~(1<<PD7);
	
	/* Enable SPI */
	SPCR = (1<<SPE) | (1<<SPIE);
	
	/* falling INT0 for CS */
	EICRA = (1<<ISC01);
	
	EIMSK = (1<<INT0);
	
	sei();
		
	while(1)
	{

		status |= STATUS_READY;
		PORTB |= (1<<PB1); // ready signal
		PORTD &= ~(1<<PD7); // busy LED
		
		while(!rx_complete) {
			// TODO: sleep
		}
		
		rx_complete=0;
		if(spibuf[0] & CMD_NEW) {
			if(checksum(spibuf,8))
				status = STATUS_ERROR | 4;
			else
				status = process_cmd();
			spibuf[0] &= ~(CMD_NEW);
		}
		
	}
}
