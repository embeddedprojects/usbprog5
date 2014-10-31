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
#include "avr.h"
#include "pindefs.h"
#include "pgm.h"
#include "bitbang.h"

#if HAVE_USBPROG5

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

/* IO mapping:
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

/* mapping: reset = 1, sck = 2, mosi = 3, miso = 4 */
static const int io_bit[] = {SPI_RST_BIT, GPIO_SCK_BIT, SPI_MOSI_BIT, GPIO_MISO_BIT};
static const int io_ofs[] = {IOCFG_SPI, IOCFG_GPIO, IOCFG_SPI, IOCFG_GPIO};

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
	return (iomem[IOCFG_GPIO + IO_PINS]>>GPIO_MISO_BIT)&1;
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

int iomem_init(void)
{
	int fd = open("/dev/mem", O_RDWR | O_SYNC);
	if (fd < 0)
		return fd;
		
	iomem =
	    (volatile uint32_t *)mmap(NULL, IOCFG_END - IOCFG_BASE,
				      PROT_READ | PROT_WRITE, MAP_SHARED, fd,
				      IOCFG_BASE);
						      
	close(fd);

	if (iomem == MAP_FAILED)
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
  
  /* switch AVR_MOSI and AVR_RST to GPIOs */
  iomem[IOCFG_SPI + IO_MODE1_SET] = (1<<SPI_MOSI_BIT) | (1<<SPI_RST_BIT);
  
  /* switch SCK to output, MISO to input */
  iomem[IOCFG_GPIO + IO_MODE0_RESET] = (1<<GPIO_MISO_BIT);
  iomem[IOCFG_GPIO + IO_MODE1_RESET] = (1<<GPIO_MISO_BIT);
  iomem[IOCFG_GPIO + IO_MODE1_SET] = (1<<GPIO_SCK_BIT);
  
 return(0);
}

static void usbprog5_close(PROGRAMMER *pgm)
{
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
