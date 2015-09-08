/*
 * avrdude - A Downloader/Uploader for AVR device programmers
 * Support for bitbanging on USBprog5
 * 
 * Copyright (C) 2014 Benedikt Heinz <hunz@mailbox.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ac_cfg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <sys/mman.h>
#include <stdint.h>
#include <assert.h>

#include "avrdude.h"
#include "libavrdude.h"

#include "bitbang.h"

#if HAVE_USBPROG5

struct pdata
{
  /* Start address of Xmega boot area */
  unsigned long boot_start;
};

#define PDATA(pgm) ((struct pdata *)(pgm->cookie))

void usbprog5_setup(PROGRAMMER * pgm)
{
  if ((pgm->cookie = malloc(sizeof(struct pdata))) == 0) {
    avrdude_message(MSG_INFO, "%s: usbprog5_setup(): Out of memory allocating private data\n",
                    progname);
    exit(1);
  }
  memset(pgm->cookie, 0, sizeof(struct pdata));
  PDATA(pgm)->boot_start = ULONG_MAX;
}

void usbprog5_teardown(PROGRAMMER * pgm)
{
  free(pgm->cookie);
}

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

/* AVR prog. IO mapping:
 * AVR  - LPC
 * MOSI - SPI_MISO
 * RST  - SPI_MOSI
 * SCK  - GPIO_20
 * MISO - GPIO_19
 */
#define SPI_MOSI_BIT	0
#define SPI_RST_BIT		1
#define GPIO_SCK_BIT	14
#define GPIO_MISO_BIT	13

/* free IOs for PDI
 * GPIO16
 * GPIO13
 * GPIO12
 * (GPIO20)
 * (GPIO19)
 */

/* PDI IO mapping:
 * PDI  - LPC
 * MISO - SPI_MISO
 * SCK  - SPI_SCK (GPIO17: Bit 11)
 * MOSI - SCK_MOSI
 * RST  - GPIO12	GPIO Bit 6
 * nCS  - GPIO13	GPIO Bit 7
 * INT  - GPIO16	GPIO Bit 10
 */

#define GPIO_PDI_RST_BIT	6
#define GPIO_PDI_NCS_BIT	7
#define GPIO_PDI_INT_BIT	10
#define SPI_PDI_SCK_BIT		3
#define GPIO_PDI_SCK_BIT	11
#define SPI_PDI_MOSI_BIT	1
#define SPI_PDI_MISO_BIT	0

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

static void spi_init(uint32_t freq)
{
	uint32_t div1, div2; //, halfcycle_ns;
	/* div1, div2 calculation is stolen from the Linux kernel :) */
	uint32_t clkdiv = (SPI_PCLK + freq / 2) / freq;
	if (clkdiv > SPI_MAX_DIVIDER)
		clkdiv = SPI_MAX_DIVIDER;
	if (clkdiv < SPI_MIN_DIVIDER)
		clkdiv = SPI_MIN_DIVIDER;

	div2 = (((clkdiv - 1) / 512) + 1) * 2;
	div1 = (((clkdiv + div2 / 2) / div2) - 1);

	/* halfcycle in nanoseconds */
	//halfcycle_ns = (1000000000/freq)>>1;
	
	/* minimum udelay invocation time: 290 ns */
	/*
	if (halfcycle_ns <= 290)
		tck_halfcycle_delay = 0;
	else
		tck_halfcycle_delay = ((halfcycle_ns - 290) / 100)+1;
	*/

	/* configure SPI IOs for SPI mode */
	iomem[IOCFG_SPI + IO_MODE0] = 0x1f;
	iomem[IOCFG_SPI + IO_MODE1] = 0;
		
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
	
	printf("SPI init\n");
}

static int spi_cs = 0;

/* len: bytes */
static void spi_xfer(const uint8_t *src, uint8_t *dst, uint32_t len) {
	uint8_t rxbuf, txbuf = 0;
	uint32_t n_bytes_rx=len, n_bytes_tx=len;
	uint32_t txstride = src ? 1 : 0;
	uint32_t rxstride = dst ? 1 : 0;
	uint8_t *rxptr = rxstride ? dst : &rxbuf;
	const uint8_t *txptr = txstride ? src : &txbuf;
	uint32_t status;
	
	//printf("xfer src %p dst %p len %d\n",src,dst,len);
	
	if(!spi_cs) {
		/* CS low */
		iomem[IOCFG_GPIO + IO_MODE0_RESET] = (1<<GPIO_PDI_NCS_BIT);
		udelay(20*10);
		spi_cs = 1;
	}

	for(;n_bytes_tx;n_bytes_tx--,txptr+=txstride) {
		/* busywait
		 * - receive one byte if possible to avoid RX overflows
		 * - wait until TX fifo has at least one free entry
		 */
		do {
			status = spimem[SPI_STATUS];
			if(!(status&(1<<SPI_STATUS_RXEMPTY))) {
				*rxptr = spimem[SPI_FIFO_DATA];
				rxptr+=rxstride;
				n_bytes_rx--;
			}
			/* ensure that delta between tx and rx doesn't get too big 
			 * max. fifo size is 64 */
		} while((status&(1<<SPI_STATUS_TXFULL)) || ((n_bytes_rx - n_bytes_tx) > 50));
		
		/* send one byte */
		spimem[SPI_FIFO_DATA] = *txptr;
	}
	
	//printf("remainder %d\n",n_bytes_rx);
	
	/* wait until we received everything */
	do {
		status = spimem[SPI_STATUS];
		if(!(status&(1<<SPI_STATUS_RXEMPTY))) {
			*rxptr = spimem[SPI_FIFO_DATA];
			rxptr+=rxstride;
			n_bytes_rx--;
		}
	} while(n_bytes_rx);
	
	//printf("/xfer\n");
}

static void spi_finish(void) {
	uint8_t foo=0;
	
	// do a dummy transfer to flush all buffers
	spi_xfer(&foo,&foo,1);
	
	/* CS hi */
	iomem[IOCFG_GPIO + IO_MODE0_SET] = (1<<GPIO_PDI_NCS_BIT);
	spi_cs=0;
}

enum {
	RST_PIN =0,
	SCK_PIN,
	MOSI_PIN,
	MISO_PIN
};

/* mapping: reset = 1, sck = 2, mosi = 3, miso = 4 */
static const int usbprog_bit[] = {SPI_RST_BIT, GPIO_SCK_BIT, SPI_MOSI_BIT, GPIO_MISO_BIT};
static const int usbprog_ofs[] = {IOCFG_SPI, IOCFG_GPIO, IOCFG_SPI, IOCFG_GPIO};

static const int *io_bit = usbprog_bit;
static const int *io_ofs = usbprog_ofs;

/* PDI IO mapping:
 * PDI  - LPC
 * MISO - SPI_MISO
 * SCK  - SPI_SCK (GPIO17)
 * MOSI - SCK_MOSI
 * RST  - GPIO12	GPIO Bit 6
 * nCS  - GPIO13	GPIO Bit 7
 * INT  - GPIO16	GPIO Bit 10
 */
static const int pdi_bit[] = { GPIO_PDI_RST_BIT, GPIO_PDI_SCK_BIT, SPI_PDI_MOSI_BIT, SPI_PDI_MISO_BIT};
static const int pdi_ofs[] = { IOCFG_GPIO, IOCFG_GPIO, IOCFG_SPI, IOCFG_SPI};

static int usbprog5_setpin(PROGRAMMER * pgm, int pinfunc, int value)
{
	int reg_ofs;
	
	if((pinfunc<3)||(pinfunc>6))
		return 0;
	
	pinfunc-=3;
	
	reg_ofs = io_ofs[pinfunc] + IO_MODE0_SET + ((value&1)^1);
	iomem[reg_ofs] = 1<<io_bit[pinfunc];
	
	if (pgm->ispdelay > 1)
		bitbang_delay(pgm->ispdelay);
		
	return 0;
}

static int usbprog5_getpin(PROGRAMMER * pgm, int pinfunc)
{
	return (iomem[io_ofs[MISO_PIN] + IO_PINS]>>io_bit[MISO_PIN])&1;
}

static int usbprog5_highpulsepin(PROGRAMMER * pgm, int pinfunc)
{

//	printf("pulsepin %d\n",pinfunc);
  usbprog5_setpin(pgm, pinfunc, 1);
  usbprog5_setpin(pgm, pinfunc, 0);

  return 0;
}

static void usbprog5_display(PROGRAMMER *pgm, const char *p)
{
    fprintf(stderr, "%sPin assignment  :\n",p);
    pgm_display_generic_mask(pgm, p, SHOW_AVR_PINS);
}

static void usbprog5_dummy(PROGRAMMER *pgm) {}

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
	
	return 0;
}

static int usbprog5_open(PROGRAMMER *pgm, char *port)
{
  int res;
  
  bitbang_check_prerequisites(pgm);
  
  res = iomem_init();
  if(res) {
	fprintf(stderr,"cannot mmap /dev/mem\n");
	return res;
  }
  
  if(port) {
	  if(!(strcmp(port,"pdi_update"))) {
		  printf("PDI adapter firmware update mode\n");
		  io_ofs = pdi_ofs;
		  io_bit = pdi_bit;
	  }
  }

  /* RST GPIO ouput */
  iomem[io_ofs[RST_PIN] + IO_MODE1_SET] = (1<<io_bit[RST_PIN]);
  
  /* MOSI GPIO output */
  iomem[io_ofs[MOSI_PIN] + IO_MODE1_SET] = (1<<io_bit[MOSI_PIN]);
  
  /* MISO GPIO input */
  iomem[io_ofs[MISO_PIN] + IO_MODE0_RESET] = (1<<io_bit[MISO_PIN]);
  iomem[io_ofs[MISO_PIN] + IO_MODE1_RESET] = (1<<io_bit[MISO_PIN]);
  
  /* SCK GPIO output */
  iomem[io_ofs[SCK_PIN] + IO_MODE1_SET] = (1<<io_bit[SCK_PIN]);

 return(0);
}

/* TODO: SCK OR gate */

static void usbprog5_close(PROGRAMMER *pgm)
{
	/* TODO: FIX */
	if((iomem) && (iomem != MAP_FAILED)) {
		/* configure SPI IOs for SPI mode */
	    iomem[IOCFG_SPI + IO_MODE0] = 0x1f;
	    iomem[IOCFG_SPI + IO_MODE1] = 0;
  
		/* switch SCK to input */
		iomem[IOCFG_GPIO + IO_MODE1_RESET] = (1<<GPIO_SCK_BIT);
		iomem[IOCFG_GPIO + IO_MODE0_RESET] = (1<<GPIO_SCK_BIT);
		
		munmap((void *)iomem, IOCFG_END - IOCFG_BASE);
		iomem = NULL;
	}
}

enum {
	ATXMEGA_MEM_TYPE_NONE,
	ATXMEGA_MEM_TYPE_APPL,
	ATXMEGA_MEM_TYPE_BOOT,
	ATXMEGA_MEM_TYPE_EEPROM,
	ATXMEGA_MEM_TYPE_FUSE,
	ATXMEGA_MEM_TYPE_LOCKBITS,
	ATXMEGA_MEM_TYPE_USERSIG,
	ATXMEGA_MEM_TYPE_FACTORY_CALIBRATION
};

/*
static unsigned char usbprog5_pdi_memtype(PROGRAMMER * pgm, unsigned long addr)
{
    if (addr >= PDATA(pgm)->boot_start)
        return ATXMEGA_MEM_TYPE_BOOT;
    else
        return ATXMEGA_MEM_TYPE_APPL;
}
*/

#define SPI_BUFSIZE		(1+3+2+256)

#define STATUS_READY	0x80
#define STATUS_ERROR	0x40

#define CMD_NEW			0x80
#define CMD_MASK		0x3f

#define ID_MAGIC1		0xc2
#define ID_MAGIC2		0xd8

#define VERSION_MSB		1
#define VERSION_LSB		0

#define CMD_BUFFER		0x20
#define BUFFER_ERASE	0x10

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

#define READ_CMD_MASK	0x30
#define READ_CMD		0x10

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

/* ioconfig for PDI mode
 * mode bits:
 * M1 M0
 *  0  0   input
 *  0  1   output device
 *  1  0   low
 *  1  1   hi
 */

#define BUSYWAIT_TIMEOUT	500000	/* max value observed in the wild: 14k */

static int pdi_busywait(void) {
	int ready;
	uint32_t cnt=BUSYWAIT_TIMEOUT;
	do {
		ready = (iomem[IOCFG_GPIO + IO_PINS]>>GPIO_PDI_INT_BIT)&1;
		cnt--;
	} while((!ready) && (cnt));
	if(!cnt)
		fprintf(stderr,"\nbusywait timeout\n");
	return cnt ? 0 : -1;
}

#ifdef DEBUG
static void hexdump(uint8_t *d, int n) {
	for(;n;n--,d++)
		printf("%02x ",*d);
	printf("\n");
}
#endif

static void checksum_send(const uint8_t *d, int len) {
	uint8_t val=0x55;
	for(;len;len--,d++)
		val ^= *d;
	spi_xfer(&val, NULL, 1);
}

static int checksum_verify(const uint8_t *d, int len) {
	uint8_t val;
	spi_xfer(NULL,&val,1);
	for(;len;len--,d++)
		val ^= *d;
	return val ^ 0x55;
}

static int usbprog5_pdi_cmd(uint8_t cmd, uint32_t addr, uint16_t len, uint8_t *data) {
	uint8_t txbuf[8];
	uint8_t rxbuf[8];
	int i, res, res2, hdr_len = 8;
	int read_cmd = ((cmd & READ_CMD_MASK) == READ_CMD);
	
	txbuf[0] = cmd | CMD_NEW;
	
	txbuf[1] = addr&0xff;
	txbuf[2] = (addr>>8)&0xff;
	txbuf[3] = (addr>>16)&0xff;
	txbuf[4] = (addr>>24)&0xff;
	
	txbuf[5] = len&0xff;
	txbuf[6] = (len>>8)&0xff;
	
	/* checksum */
	txbuf[7] = 0x55;
	for(i=0;i<7;i++)
		txbuf[7] ^= txbuf[i];
	
	/* send cmd */
	spi_xfer(txbuf,rxbuf,hdr_len);
#ifdef DEBUG
	printf("cmd: ");
	hexdump(txbuf,8);
#endif

	/* check if ready */
	//printf("status: %02x\n",rxbuf[0]);
	if(!(rxbuf[0]&STATUS_READY)) {
		spi_finish();
		fprintf(stderr,"PDI adapter not ready\n");
		return -1;
	}
	
	/* transmit data (if any data given and not a read command) */
	if((data) && (!read_cmd)) {
		spi_xfer(data,NULL,len);
		checksum_send(data,len);
	}

	spi_finish();
	
	res=pdi_busywait();	
	if(res) {
		fprintf(stderr,"timeout after command\n");
		return res;
	}
	
	/* nothing to read -> done */
	if(!read_cmd) {
		/* check for error before return */
		txbuf[0]=0;
		spi_xfer(txbuf,rxbuf,1);
		spi_finish();
		if(rxbuf[0] != STATUS_READY) {
			fprintf(stderr,"PDI adapter not ready: %02x\n",rxbuf[0]);
			return -(rxbuf[0]&0x1f);
		}
		res = pdi_busywait();
		if(res) {
			fprintf(stderr,"timeout after status read cmd %02x\n",cmd);
		}
		return res;
	}

	/* fix checksum */
	txbuf[7] ^= txbuf[0] ^ CMD_NOP;
	
	/* send NOP cmd */
	txbuf[0]=CMD_NOP;
	
	spi_xfer(txbuf,rxbuf,hdr_len);
	
	/* check if ready */
	if((!(rxbuf[0]&STATUS_READY)) || (rxbuf[0]&STATUS_ERROR)) {
		spi_finish();
		fprintf(stderr,"error %02x after command %02x\n",rxbuf[0],cmd);
		return -1;
	}
	
	/* read data */
	spi_xfer(NULL,data,len);
#ifdef DEBUG
	printf("rx: ");
	hexdump(data,len);
#endif
	
	res = checksum_verify(data,len);
	
	spi_finish();
	
	res2 = pdi_busywait();
	
	if(res) {
		fprintf(stderr,"checksum error: %02x\n",res);
		return res;
	}
	if(res2)
		fprintf(stderr,"timeout after read\n");
	return res2;
}

static int usbprog5_pdi_program_enable(PROGRAMMER * pgm, AVRPART * p)
{
	float bitclock = pgm->bitclock * 1000000;
	int bc_i = bitclock;
	bc_i = bc_i > 16 ? 16 : bc_i;
	uint8_t div;
	for(div=0;(1<<div)<bc_i;div++) {}
	//printf("sck %f bc_i %d div %d %d\n",pgm->bitclock,bc_i,div,1<<div);
	printf("using %d us SCK period\n",1<<div);
	return usbprog5_pdi_cmd(CMD_INIT, div, 0, NULL);
}

static void usbprog5_pdi_disable(PROGRAMMER * pgm)
{
	usbprog5_pdi_cmd(CMD_DEINIT, 0, 0, NULL);
}

static unsigned char usbprog5_pdi_memid(PROGRAMMER * pgm, unsigned long addr)
{
    if (addr >= PDATA(pgm)->boot_start)
        return DST_FLASH_BOOT; //ATXMEGA_MEM_TYPE_BOOT;
    else
        return DST_FLASH_APP; //ATXMEGA_MEM_TYPE_APPL;
}

static int get_dst(PROGRAMMER * pgm, AVRMEM * mem, unsigned long addr) {
	if (strcmp(mem->desc, "flash") == 0) {
        return usbprog5_pdi_memid(pgm, addr);
    } else if (strcmp(mem->desc, "application") == 0 ||
               strcmp(mem->desc, "apptable") == 0) {
        return DST_FLASH_APP;
    } else if (strcmp(mem->desc, "boot") == 0) {
        return DST_FLASH_BOOT;
    } else if (strcmp(mem->desc, "eeprom") == 0) {
        return DST_EEPROM;
    } else if (strcmp(mem->desc, "usersig") == 0) { /* this is a hack... */
        return DST_FLASH_APP;
	}
	return -1;  
}

static int usbprog5_pdi_write_byte(PROGRAMMER * pgm, AVRPART * p, AVRMEM * mem,
				   unsigned long addr, unsigned char data)
{
	uint8_t memcode=ATXMEGA_MEM_TYPE_NONE;
/*
	if (strcmp(mem->desc, "flash") == 0) {
        memcode = usbprog5_pdi_memtype(pgm, addr);
    } else if (strcmp(mem->desc, "application") == 0 ||
               strcmp(mem->desc, "apptable") == 0) {
        memcode = ATXMEGA_MEM_TYPE_APPL;
    } else if (strcmp(mem->desc, "boot") == 0) {
        memcode = ATXMEGA_MEM_TYPE_BOOT;
    } else if (strcmp(mem->desc, "eeprom") == 0) {
        memcode = ATXMEGA_MEM_TYPE_EEPROM;
        */
    if (strncmp(mem->desc, "lock", strlen("lock")) == 0) {
        memcode = ATXMEGA_MEM_TYPE_LOCKBITS;
    } else if (strncmp(mem->desc, "fuse", strlen("fuse")) == 0) {
        memcode = ATXMEGA_MEM_TYPE_FUSE;
    //} else if (strcmp(mem->desc, "usersig") == 0) {
    //    memcode = ATXMEGA_MEM_TYPE_USERSIG;
    } else {
        avrdude_message(MSG_INFO, "%s: usbprog5_pdi_write_byte(): unknown memory \"%s\"\n",
                        progname, mem->desc);
        return -1;
    }
    addr += mem->offset;
    
//    assert((memcode == ATXMEGA_MEM_TYPE_LOCKBITS) || (memcode == ATXMEGA_MEM_TYPE_FUSE));
    return usbprog5_pdi_cmd(CMD_WRITEFUSE, addr, 1, &data);
}

static int usbprog5_pdi_read_byte(PROGRAMMER * pgm, AVRPART * p, AVRMEM * mem,
                                  unsigned long addr, unsigned char * value)
{
   	return usbprog5_pdi_cmd(CMD_READ, addr + mem->offset, 1, value);
}

static int usbprog5_pdi_paged_load(PROGRAMMER * pgm, AVRPART * p, AVRMEM * mem,
                                   unsigned int page_size,
                                   unsigned int addr, unsigned int n_bytes)
{
	unsigned int offset = addr;
    int ret, n_bytes_orig = n_bytes;
    addr += mem->offset;
	
	while(n_bytes>0) {
		int chunk_size = (n_bytes > 256) ? 256 : n_bytes;
		ret = usbprog5_pdi_cmd(CMD_READ, addr, chunk_size, mem->buf+offset);
		assert(!ret);
		n_bytes -= chunk_size;
		offset += chunk_size;
		addr += chunk_size;		
	}
		
	return n_bytes_orig;
}

//#define AUTO_ERASE

#define BUFFER_CHUNK_SIZE	256

static int usbprog5_pdi_paged_write(PROGRAMMER * pgm, AVRPART * p, AVRMEM * mem,
                                    unsigned int page_size,
                                    unsigned int addr, unsigned int n_bytes)
{
	int dst = get_dst(pgm,mem,addr);
	int ret=0, first=1, offset = 0;
	int usersig = (strcmp(mem->desc, "usersig") == 0);
	assert(dst >= 0);
	assert(dst <= DST_EEPROM);
	while(n_bytes) {
		int chunk_size = (n_bytes < BUFFER_CHUNK_SIZE) ? n_bytes : BUFFER_CHUNK_SIZE;
		int last = (chunk_size == n_bytes);
		uint8_t cmd = CMD_BUFFER | dst;
		if(first) {
			cmd |= BUFFER_ERASE;
			first=0;
		}
		if(last) {
#ifdef AUTO_ERASE
			cmd |= WRMODE_ERASE_WRITE;
#else
			cmd |= WRMODE_WRITE;
#endif
			if(usersig)
				cmd = CMD_WRITEUSERSIGN;
		}
		ret = usbprog5_pdi_cmd(cmd, mem->offset + addr + offset, chunk_size, mem->buf + addr + offset);
		if(ret)
			break;
		n_bytes -= chunk_size;
		offset += chunk_size;
	}

	return ret;
}

static int usbprog5_pdi_chip_erase(PROGRAMMER * pgm, AVRPART * p)
{
	printf("chip erase\n");
	//return 0;
	return usbprog5_pdi_cmd(CMD_CHIPERASE, 0, 0, NULL);
}

static int usbprog5_pdi_page_erase(PROGRAMMER * pgm, AVRPART * p, AVRMEM * mem,
                                   unsigned int addr)
{
	int ret=0;
#ifndef AUTO_ERASE
	int dst = get_dst(pgm,mem,addr);
	uint8_t cmd;
	assert(dst >= 0);
	assert(dst <= DST_EEPROM);
	cmd = CMD_BUFFER | dst | WRMODE_ERASE;
	ret = usbprog5_pdi_cmd(cmd, mem->offset + addr, 0, NULL);
#endif
    return ret;
}

/*
 * Modify pgm's methods for PDI operation.
 */
static void usbprog5_setup_pdi(PROGRAMMER * pgm)
{
	printf("switch to PDI mode\n");
    pgm->program_enable = usbprog5_pdi_program_enable;
    pgm->disable = usbprog5_pdi_disable;
    pgm->write_byte = usbprog5_pdi_write_byte;
    pgm->read_byte = usbprog5_pdi_read_byte;
    pgm->paged_load = usbprog5_pdi_paged_load;
    pgm->paged_write = usbprog5_pdi_paged_write;
    pgm->chip_erase = usbprog5_pdi_chip_erase;
    pgm->page_erase = usbprog5_pdi_page_erase;
    
    /* configure nCS as output, drive hi (inactive) */
	iomem[IOCFG_GPIO + IO_MODE0_SET] = (1<<GPIO_PDI_NCS_BIT);
	iomem[IOCFG_GPIO + IO_MODE1_SET] = (1<<GPIO_PDI_NCS_BIT);
	spi_cs = 0;
    
    /* nINT as input */
    iomem[IOCFG_GPIO + IO_MODE0_RESET] = (1<<GPIO_PDI_INT_BIT);
	iomem[IOCFG_GPIO + IO_MODE1_RESET] = (1<<GPIO_PDI_INT_BIT);
    
    spi_init(120000);    
    //spi_init(50000);

	/* reset PDI adapter */
	iomem[IOCFG_GPIO + IO_MODE1_SET] = (1<<GPIO_PDI_RST_BIT);
	iomem[IOCFG_GPIO + IO_MODE0_RESET] = (1<<GPIO_PDI_RST_BIT);
	usleep(200000);
	iomem[IOCFG_GPIO + IO_MODE0_SET] = (1<<GPIO_PDI_RST_BIT);
	usleep(200000);
}

static int usbprog5_initialize(PROGRAMMER * pgm, AVRPART * p)
{
	if ((p->flags & AVRPART_HAS_PDI) != 0) {
		int res;
		uint8_t id[4];
      /*
       * Find out where the border between application and boot area
       * is.
       */
      AVRMEM *bootmem = avr_locate_mem(p, "boot");
      AVRMEM *flashmem = avr_locate_mem(p, "flash");
      if (bootmem == NULL || flashmem == NULL) {
        avrdude_message(MSG_INFO, "%s: usbprog5_initialize(): Cannot locate \"flash\" and \"boot\" memories in description\n",
                        progname);
      } else {
        PDATA(pgm)->boot_start = bootmem->offset - flashmem->offset;
      }
      usbprog5_setup_pdi(pgm);
      res=usbprog5_pdi_cmd(CMD_ID, 0, 4, id);
      if((res < 0) || (id[0]!=ID_MAGIC1) || (id[1]!=ID_MAGIC2)) {
		  fprintf(stderr,"connection to PDI adapter failed\n");
		  fprintf(stderr,"please make sure the adapter is connected\n");
		  return res ? res : -1;
	  }
      printf("PDI fw version: %d.%02d\n",id[2],id[3]);
      if((id[2] == VERSION_MSB) && (id[3] >= VERSION_LSB))
		return pgm->program_enable(pgm, p);
	  fprintf(stderr,"PDI fw incompatible. expecting %d.x (x>=%02d)\n",VERSION_MSB,VERSION_LSB);
	  fprintf(stderr,"please install a compatible firmware\n");
	  return -1;
    }
    else
		return bitbang_initialize(pgm, p);
}

void usbprog5_initpgm(PROGRAMMER *pgm)
{
  strcpy(pgm->type, "usbprog5");

  pgm_fill_old_pins(pgm); // TODO to be removed if old pin data no longer needed

  pgm->rdy_led        = bitbang_rdy_led;
  pgm->err_led        = bitbang_err_led;
  pgm->pgm_led        = bitbang_pgm_led;
  pgm->vfy_led        = bitbang_vfy_led;
  pgm->initialize     = bitbang_initialize;
  pgm->display        = usbprog5_display;
  pgm->enable         = usbprog5_dummy;
  pgm->disable        = usbprog5_dummy;
  pgm->powerup        = usbprog5_dummy;
  pgm->powerdown      = usbprog5_dummy;
  pgm->program_enable = bitbang_program_enable;
  pgm->chip_erase     = bitbang_chip_erase;
  pgm->cmd            = bitbang_cmd;
  pgm->open           = usbprog5_open;
  pgm->close          = usbprog5_close;
  pgm->setpin         = usbprog5_setpin;
  pgm->getpin         = usbprog5_getpin;
  pgm->highpulsepin   = usbprog5_highpulsepin;
  pgm->read_byte      = avr_read_byte_default;
  pgm->write_byte     = avr_write_byte_default;
  pgm->setup			= usbprog5_setup;
  pgm->teardown			= usbprog5_teardown;
  pgm->initialize		= usbprog5_initialize;
  
}

const char usbprog5_desc[] = "USBprog5 interface";

#else  /* !HAVE_usbprog5 */

void usbprog5_initpgm(PROGRAMMER * pgm)
{
  fprintf(stderr,
	  "%s: USBprog5 support not available in this configuration\n",
	  progname);
}

const char usbprog5_desc[] = "USBprog5 interface (not available)";

#endif /* HAVE_USBPROG5 */
