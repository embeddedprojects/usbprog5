/*
 * avrdude - A Downloader/Uploader for AVR device programmers
 * Support for bitbanging GPIO pins using the /sys/class/gpio interface
 * 
 * Copyright (C) 2013 Radoslav Kolev <radoslav@kolev.info>
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
#include <sys/types.h>
#include <sys/stat.h>



#include "avrdude.h"
#include "avr.h"
#include "pindefs.h"
#include "pgm.h"
#include "bitbang.h"


/* LPC3131 UM chapter 15 */
#define IOCONFIG    0x13003000
#define FBLO_GPIO   0x1C0  /* GPIO functional block */

/* offset in GPIO functional block  */
#define PINS        0x00
#define MODE0       0x10
#define MODE0_SET   0x14
#define MODE0_RESET 0x18
#define MODE1       0x20
#define MODE1_SET   0x24
#define MODE1_RESET 0x28

/* !! Warning !!
 * GPIO4 (1 << 4) is only as INPUT available.
 * Setting the MODE0-Register for Pin 4 to 1 will cause a crash of the system!
 */

#if HAVE_LINUXGPIO

/*
 * GPIO user space helpers
 *
 * Copyright 2009 Analog Devices Inc.
 * Michael Hennerich (hennerich@blackfin.uclinux.org)
 *
 * Licensed under the GPL-2 or later
 */

/*
 * GPIO user space helpers
 * The following functions are acting on an "unsigned gpio" argument, which corresponds to the 
 * gpio numbering scheme in the kernel (starting from 0).  
 * The higher level functions use "int pin" to specify the pins with an offset of 1:
 * gpio = pin - 1;
 */

#define GPIO_DIR_IN	0
#define GPIO_DIR_OUT	1

char *mymem;
int pointer=0;
int direct_gn()
{
  int mem_fd;
  if(pointer==0){
  if ((mem_fd = open("/dev/mem", O_RDWR | O_RSYNC | O_SYNC)) < 0) {
        printf("can't open /dev/mem \n");
        exit(-1);
    }

        //printf("vor mmap \n");
      mymem = mmap(0,
                 getpagesize(),
                 PROT_READ|PROT_WRITE,
                 MAP_SHARED,
                 mem_fd,
                 IOCONFIG);



      if (mymem == MAP_FAILED) {
        //printf("mmap error %d\n", errno);
        exit(-1);
    }
    else {
        //printf("mymem = 0x%x\n", (unsigned int)mymem);
    }
 pointer=1;
}
return 1;

}
static int linuxgpio_export(unsigned int gpio)
{

//perror("hier kommt er noch hin(ex)");

  int fd, len, r;
  char buf[11];

  //len = snprintf(buf, sizeof(buf), "%d", gpio);

  //      return len;

  //fd = open("/sys/class/gpio/export", O_WRONLY);#
  fd=1;
  if (fd < 0) {
    perror("Can't open /root/avrdude-6.0rc1/derp");
    return fd;
  }
  int a;
  a=direct_gn();
  len = snprintf(buf, sizeof(buf), "%d", gpio);
  //r = write(fd, buf, len);
  //close(fd);

  return r;
 }

static int linuxgpio_unexport(unsigned int gpio)
{

//perror("hier kommt er noch hin(unex)");
  int fd, len, r;
  char buf[11];

  //len = snprintf(buf, sizeof(buf), "%d", gpio);
  //      return len;


  //fd = open("/sys/class/gpio/unexport", O_WRONLY);
  fd=2;
  if (fd < 0) {
    perror("Can't open /sys/class/gpio/unexport");
    return fd;
  }

  len = snprintf(buf, sizeof(buf), "%d", gpio);
  //r = write(fd, buf, len);
  //close(fd);

  return r;
}

static int linuxgpio_openfd(unsigned int gpio)
{
  char filepath[60];

  snprintf(filepath, sizeof(filepath), "/sys/class/gpio/gpio%d/value",gpio);
  return (1);//open(filepath, O_RDWR));
}

static int linuxgpio_dir(unsigned int gpio, unsigned int dir)
{
//perror("hier kommt er noch hin(dir)");
//  if (dir == GPIO_DIR_OUT)
//	return 4;
//  else
//	return 3;
  int fd, r;
  char buf[60];

  snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction",gpio);
    /*
  fd = open(buf, O_WRONLY);
  if (fd < 0) {
    perror("Can't open gpioX/direction");
    return fd;
  }
*/
  if (dir == GPIO_DIR_OUT)
    //r = write(fd, "out", 4);
    r=3;
  else
    //r = write(fd, "in", 3);
    r=2;
    int led;
        switch(gpio){
        case 1:led=0  ; break;
        case 0:led=1  ; break;
        case 2:led=2  ; break;
        case 3:led=3  ; break;
        case 11:led=5  ; break;
        case 12:led=6  ; break;
        case 13:led=7  ; break;
        case 14:led=8  ; break;
        case 15:led=9  ; break;
        case 16:led=10  ; break;
        case 17:led=11 ; break;
        case 18:led=12  ; break;
        case 19:led=13  ; break;
        case 20:led=14  ; break;
        }

        
  if (dir == GPIO_DIR_OUT)
  {
        *(volatile unsigned int *)(mymem + FBLO_GPIO + MODE1_RESET) = (1 << led);
        *(volatile unsigned int *)(mymem + FBLO_GPIO + MODE0_SET) = (1 << led);
  } else {
      *(volatile unsigned int *)(mymem + FBLO_GPIO + MODE1_RESET) = (1 << led);
        *(volatile unsigned int *)(mymem + FBLO_GPIO + MODE0_RESET) = (1 << led);
  }

  //close(fd);

  return r;
}

static int linuxgpio_dir_out(unsigned int gpio)
{
  return linuxgpio_dir(gpio, GPIO_DIR_OUT);
}

static int linuxgpio_dir_in(unsigned int gpio)
{


  return linuxgpio_dir(gpio, GPIO_DIR_IN);
}

/*
 * End of GPIO user space helpers
 */

#define N_GPIO (PIN_MAX + 1)

/*
* an array which holds open FDs to /sys/class/gpio/gpioXX/value for all needed pins
*/
static int linuxgpio_fds[N_GPIO] ;

int ledar[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//memset(ledar, '2' , sizeof(ledar));
int leda;
static int linuxgpio_setpin(PROGRAMMER * pgm, int pin, int value)
{
  int r;
/*
  if (pin & PIN_INVERSE)
  {
    value  = !value;
    pin   &= PIN_MASK;
  }

  if ( linuxgpio_fds[pin] < 0 )
  {
    return -1;
  }
*/
  //printf("PIN=%d\n", pin); 
  switch(pin){
  //case 1:leda=0  ; break;
  //case 0:leda=1  ; break;
  case 2:leda=2  ; break;
  //case 3:leda=3  ; break;
  //case 11:leda=5  ; break;
  //case 12:leda=6  ; break;
  //case 13:leda=7  ; break;
  //case 14:leda=8  ; break;
  //case 15:leda=9  ; break;
  //case 16:leda=10  ; break;
  //case 17:leda=11 ; break;
  case 18:leda=12  ; break;
  case 19:leda=13  ; break;
  case 20:leda=14  ; break;
  default:leda=(-1);break;//printf("\n%d\n",pin);break;
  }  

    //printf("leda==%d , gpio==%d",leda,pin);

  *(unsigned int *)(mymem + FBLO_GPIO + MODE1_SET) = (1 << leda); 
  if (value){
    r = 1;
    if (ledar[leda]!=1){
    *(unsigned int *)(mymem + FBLO_GPIO + MODE0_SET) = (1 << leda);
    //r = write(linuxgpio_fds[pin], "1", 1);
    }
    ledar[leda]=1;
    }
  else{
    r = 1;
    if (ledar[leda]!=0){

    *(unsigned int *)(mymem + FBLO_GPIO + MODE0_RESET) = (1 << leda);
    }
    ledar[leda]=0;
    //r = write(linuxgpio_fds[pin], "0", 1);
    }




  if (r!=1) return -1;
  //pgm->ispdelay = 0;
  if (pgm->ispdelay > 1)
    bitbang_delay(pgm->ispdelay);

  return 0;
}




void bin_output(int val) 
{
        int i;
        char str[33];
        for (i = 31; i >= 0; i--)
            str[31-i] = '0' + ((val >> i) & 0x1);
        str[32] = 0;
        //puts(str);
        return;
}










	volatile unsigned int 	temp = 0,temp2 = 0,temp3 = 0;


static int linuxgpio_getpin(PROGRAMMER * pgm, int pin)
{

  switch(pin){
  //case 1:leda=0  ; break;
  //case 0:leda=1  ; break;
  case 2:leda=2  ; break;
  //case 3:leda=3  ; break;
  //case 11:leda=5  ; break;
  //case 12:leda=6  ; break;
  //case 13:leda=7  ; break;
  //case 14:leda=8  ; break;
  //case 15:leda=9  ; break;
  //case 16:leda=10  ; break;
  //case 17:leda=11 ; break;
  case 18:leda=12  ; break;
  case 19:leda=13  ; break;
  case 20:leda=14  ; break;
  default:leda=(-1);break;
  }
//printf("leda==%d , gpio==%d",leda,pin);
//printf("%d == %d",leda,pin);
//*(volatile unsigned int *)(mymem + FBLO_GPIO + MODE1_RESET) = (1 << leda);
 
//*(volatile unsigned int *)(mymem + FBLO_GPIO + MODE0_RESET) = (1 << leda);

/*printf("MODE0=%d;MODE1=%d\n",

            ((*(volatile unsigned int * )(mymem + FBLO_GPIO + MODE0)))&(1 << leda),

            ((*(volatile unsigned int * )(mymem + FBLO_GPIO + MODE1)))&(1 << leda));

*/
  unsigned char invert=0;
      char c;
if (temp2>=0){
    
    temp = (*(volatile unsigned int *)(mymem + FBLO_GPIO + 0x00));
//bin_output(temp);
//printf("%s data=0x%x(%d)\n",__func__,temp,temp);
//temp2 = (1 <<  (leda));
//bin_output(temp2);
//temp2 = (1 << leda);
//bin_output(temp2);
//printf("%s - data=0x%x(%d)\n",__func__,temp2,temp2);
   temp3 =temp & (1 << (leda));
//puts("-----------------------"); 
//temp=temp-temp2;
//printf("%s = data=0x%x(%d)\n",__func__,temp,temp);
//printf("%s & data=0x%x(%d)\n",__func__,temp3,temp3);







//printf("temp=%x",temp);
//printf("test= %x\n",temp);


  //unsigned char invert=0;
  //char c;

 /* if (pin & PIN_INVERSE)
  {
    invert = 1;
    pin   &= PIN_MASK;
  }*/

  //if (lseek(linuxgpio_fds[pin], 0, SEEK_SET)<0)
    //      return -1;



if (temp3>=1){
        //perror("kein error");
        return 1-invert;
}
else
    return 0+invert;


}
temp2 += 1;
  if ( linuxgpio_fds[pin] < 0 )
    return -1;

  if (lseek(linuxgpio_fds[pin], 0, SEEK_SET)<0)
    return -1;

  if (read(linuxgpio_fds[pin], &c, 1)!=1)
    return -1;

  //if ((c==0)&&(temp3==0))
  //  perror ("beide 0");

  //if ((c>=1)&&(temp3>=1))
  //  perror ("beide 1");    

  if (c=='0')  
    return 0+invert;
  else if (c=='1')
    return 1-invert;
  else
    return -1;

}

static int linuxgpio_highpulsepin(PROGRAMMER * pgm, int pin)
{

  //if ( linuxgpio_fds[pin & PIN_MASK] < 0 )
   // return -1;

  linuxgpio_setpin(pgm, pin, 1);
  linuxgpio_setpin(pgm, pin, 0);

  return 0;
}



static void linuxgpio_display(PROGRAMMER *pgm, const char *p)
{
    fprintf(stderr, "%sPin assignment  : /sys/class/gpio/gpio{n}\n",p);
    pgm_display_generic_mask(pgm, p, SHOW_AVR_PINS);
}

static void linuxgpio_enable(PROGRAMMER *pgm)
{
  /* nothing */
}

static void linuxgpio_disable(PROGRAMMER *pgm)
{
  /* nothing */
}

static void linuxgpio_powerup(PROGRAMMER *pgm)
{
  /* nothing */
}

static void linuxgpio_powerdown(PROGRAMMER *pgm)
{
  /* nothing */
}
int helper=0;
static int linuxgpio_open(PROGRAMMER *pgm, char *port)
{
  int r, i, pin;

  bitbang_check_prerequisites(pgm);


  for (i=0; i<N_GPIO; i++)
    linuxgpio_fds[i] = -1;
  //Avrdude assumes that if a pin number is 0 it means not used/available
  //this causes a problem because 0 is a valid GPIO number in Linux sysfs.
  //To avoid annoying off by one pin numbering we assume SCK, MOSI, MISO 
  //and RESET pins are always defined in avrdude.conf, even as 0. If they're
  //not programming will not work anyway. The drawbacks of this approach are
  //that unwanted toggling of GPIO0 can occur and that other optional pins
  //mostry LED status, can't be set to GPIO0. It can be fixed when a better 
  //solution exists.
  /*
  for (i=2; i<N_PINS; i++) {
    if ( pgm->pinno[i] != 0 ||
         i == PIN_AVR_RESET ||
         i == PIN_AVR_SCK   ||
         i == PIN_AVR_MOSI  ||
         i == PIN_AVR_MISO ) {
        pin = pgm->pinno[i] & PIN_MASK;
        if ((r=linuxgpio_export(pin)) < 0) {
            fprintf(stderr, "Can't export GPIO %d, already exported/busy?: %s",
                    pin, strerror(errno));
            return r;
        }
        if (i == PIN_AVR_MISO)
            r=linuxgpio_dir_in(pin);
        else
            r=linuxgpio_dir_out(pin);

        if (r < 0)
            return r;

        //if ((linuxgpio_fds[pin]=linuxgpio_openfd(pin)) < 0)
            //return linuxgpio_fds[pin];
	//return 1;
    }
  }
*/

  switch(helper){
        case 0:r=linuxgpio_export(2); r=linuxgpio_dir_out(2);helper=helper+1;return r  ; break;
        case 1:r=linuxgpio_export(20); r=linuxgpio_dir_out(20);helper=helper+1;return r   ; break;
        case 2:r=linuxgpio_export(19); r=linuxgpio_dir_in(19);helper=helper+1;return r   ; break;
        case 3:r=linuxgpio_export(18); r=linuxgpio_dir_out(18);helper=helper+1;return r   ; break;
        default :return 0;  ; break;

}

 return(0);
}

static void linuxgpio_close(PROGRAMMER *pgm)
{
  int i, reset_pin;

  linuxgpio_setpin(pgm,2,1);

  //reset_pin = pgm->pinno[PIN_AVR_RESET] & PIN_MASK;

  //first configure all pins as input, except RESET
  //this should avoid possible conflicts when AVR firmware starts
  for (i=0; i<N_GPIO; i++) {
    if (linuxgpio_fds[i] >= 0 && i != reset_pin) {
       //close(linuxgpio_fds[i]);
       //linuxgpio_dir_in(i);
       //linuxgpio_unexport(i);
    }
  }
  //configure RESET as input, if there's external pull up it will go high
  if (linuxgpio_fds[reset_pin] >= 0) {
    //close(linuxgpio_fds[reset_pin]);
    //linuxgpio_dir_in(reset_pin);
    //linuxgpio_unexport(reset_pin);
  }
}

void linuxgpio_initpgm(PROGRAMMER *pgm)
{
  strcpy(pgm->type, "linuxgpio");

  pgm_fill_old_pins(pgm); // TODO to be removed if old pin data no longer needed

  pgm->rdy_led        = bitbang_rdy_led;
  pgm->err_led        = bitbang_err_led;
  pgm->pgm_led        = bitbang_pgm_led;
  pgm->vfy_led        = bitbang_vfy_led;
  pgm->initialize     = bitbang_initialize;
  pgm->display        = linuxgpio_display;
  pgm->enable         = linuxgpio_enable;
  pgm->disable        = linuxgpio_disable;
  pgm->powerup        = linuxgpio_powerup;
  pgm->powerdown      = linuxgpio_powerdown;
  pgm->program_enable = bitbang_program_enable;
  pgm->chip_erase     = bitbang_chip_erase;
  pgm->cmd            = bitbang_cmd;
  pgm->open           = linuxgpio_open;
  pgm->close          = linuxgpio_close;
  pgm->setpin         = linuxgpio_setpin;
  pgm->getpin         = linuxgpio_getpin;
  pgm->highpulsepin   = linuxgpio_highpulsepin;
  pgm->read_byte      = avr_read_byte_default;
  pgm->write_byte     = avr_write_byte_default;
}

const char linuxgpio_desc[] = "GPIO bitbanging using the Linux sysfs interface";

#else  /* !HAVE_LINUXGPIO */

void linuxgpio_initpgm(PROGRAMMER * pgm)
{
  fprintf(stderr,
	  "%s: Linux sysfs GPIO support not available in this configuration\n",
	  progname);
}

const char linuxgpio_desc[] = "GPIO bitbanging using the Linux sysfs interface (not available)";

#endif /* HAVE_LINUXGPIO */
