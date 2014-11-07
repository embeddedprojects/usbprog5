#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
 
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




#define mmioReg(a) (*(volatile unsigned long *)(a))
 
/* !! Warning !!
 * GPIO4 (1 << 4) is only as INPUT available.
 * Setting the MODE0-Register for Pin 4 to 1 will cause a crash of the system!
 */

 
 
#define sck     (1 << 13)
#define cs      (1 << 14)
#define sdi     (1 << 11)



void byebye(void);
 
//Memory Map
char *mymem;
int last_cs=0,last_sck=1,last_sdi=1; 
int main( int argc, char *argv[])
{



int mem_fd;
    atexit(byebye);
    if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) {
        printf("can't open /dev/mem \n");
        exit(-1);
    }
    printf("mem_fd = %d\n", mem_fd);
    printf("getpagesize() -> %d\n", getpagesize());
    mymem = mmap(0, 
                 getpagesize(), 
                 PROT_READ|PROT_WRITE, 
                 MAP_SHARED, 
                 mem_fd, 
                 IOCONFIG);
    if (mymem == MAP_FAILED) {
        printf("mmap error %d\n", errno);
        exit(-1);
    }
    else {
        printf("mymem = 0x%x\n", (unsigned int)mymem);
    }
int help;

//setting cs sck sdi as output

*(volatile unsigned int *)(mymem + FBLO_GPIO + MODE1_SET) = cs;

 *(volatile unsigned int *)(mymem + FBLO_GPIO + MODE1_SET) = sck;

 *(volatile unsigned int *)(mymem + FBLO_GPIO + MODE1_SET) = sdi;

//setting starting values of cs sck sdi

sdi_low();
sck_low();
cs_high();

tcon();

//while (1) {

//takt();


//printf("decre");
//decre();

//printf("%s\n",argv[1]);
//pirintf("%s\n",argv[2]);
//printf("\n");
if (argc == 2){
    write_int(atoi(argv[1]));
}
else{
    if(argc == 3){
        if ((*argv[1]!=*argv[2])&&((*argv[1]=='0')||(*argv[1]=='1'))&&((*argv[2]=='0')||(*argv[2]=='1'))){
        if ((*argv[1]=='0')&&(*argv[2]=='1')){
            incre();
        }
        if ((*argv[1]=='1')&&(*argv[2]=='0')){
            decre();
        }
        }
        else{
            printf("\n\nERROR: type commands like this:\nincrement = 0 1\n decrement = 1 0\n write (for example 12) = 12\n");
        }
    }
    else{
        printf("\n\nERROR: type commands like this:\nincrement = 0 1\n decrement = 1 0\n write (for example 12) = 12\n");
    }
}
/*
sleep(1);
sleep(1);
*/
//}
}
// *(unsigned int *)(mymem + FBLO_GPIO + MODE1_SET) |= (1 << 12);// set output
// *(unsigned int *)(mymem + FBLO_GPIO + MODE0_SET) = (1 << 12);// set high
//temp = (*(volatile unsigned int *)(mymem + FBLO_GPIO + 0x00));

void write_int(int val){

     
    int i;
    int in[9];
    for (i = 0; i <= 7; i++){
        in[0+i] = 0 + ((val >> i) & 0x1);
        //printf("%x", in[0+i]);
    }
    printf("\n%x%x%x%x%x%x%x%x", in[7], in[6], in[5], in[4], in[3], in[2], in[1], in[0]);
    printf("\n%x",in[7]);
    
     
    i=7; 
//always the same start -- address + mode + bit 9,8     
     cs_low();
     sdi_low();
     takt();
     sdi_low();
     takt();
     sdi_low();
     takt();
     sdi_low();
     takt();
     sdi_low();
     takt();
     sdi_low();
     takt();
     sdi_low();
     takt();
     sdi_low();
     takt();
     //printf("\n");
     while (i>=0){
         if (in[0+i]==0){
             sdi_low();
             //printf("0");
         }
         else{
             sdi_high();
             //printf("1");
         }
         takt();
         i--;
     }
     cs_high();
     return;
    
    
}

void takt(){
    sck_high();
    sck_low();
}

void tcon(){
    cs_low();
    sdi_low();
    takt();
    sdi_high();
    takt();
    sdi_low();
    takt();
    sdi_low();
    takt();
    sdi_low();
    takt();
    sdi_low();
    takt();
    sdi_low();
    takt();
    sdi_high();
    takt();
    sdi_low();
    takt();
    sdi_low();
    takt();
    sdi_low();
    takt();
    sdi_low();
    takt();
    sdi_high();
    takt();
    sdi_high();
    takt();
    sdi_low();
    takt();
    cs_high();
}



void incre(){
    cs_low();
    sdi_low();
    takt();
    sdi_low();
    takt();
    sdi_low();
    takt();
    sdi_low();
    takt();
    sdi_low();
    takt();
    sdi_high();
    takt();
    sdi_low();
    takt();
    sdi_low();
    takt();
    cs_high();
     
}

void decre(){
    cs_low();
    sdi_low();
    takt();
    sdi_low();
    takt();
    sdi_low();
    takt();
    sdi_low();
    takt();
    sdi_high();
    takt();
    sdi_low();
    takt();
    sdi_low();
    takt();
    sdi_low();
    takt();

    cs_high();

}


void cs_low()
{
    if (last_cs == 1){
        last_cs=0;
        *(volatile unsigned int *)(mymem + FBLO_GPIO + MODE0_RESET) = cs;
    }




}


void cs_high(){
    if (last_cs == 0){
        last_cs=1;
        *(volatile unsigned int *)(mymem + FBLO_GPIO + MODE0_SET) = cs;
    }
}






 
void sdi_low()
{
  //  printf("sdi_low");
        if (last_sdi == 1){
                last_sdi=0;
                *(volatile unsigned int *)(mymem + FBLO_GPIO + MODE0_RESET) = sdi;
                                }




}


void sdi_high(){
//    printf("sdi_high");
        if (last_sdi == 0){
            last_sdi=1;
            *(volatile unsigned int *)(mymem + FBLO_GPIO + MODE0_SET) = sdi;
                                }
}



void sck_low()
{
        if (last_sck == 1){
                last_sck=0;
                *(volatile unsigned int *)(mymem + FBLO_GPIO + MODE0_RESET) = sck;
                                }




}


void sck_high(){
        if (last_sck == 0){
            last_sck=1;
            *(volatile unsigned int *)(mymem + FBLO_GPIO + MODE0_SET) = sck;
                                }
}




void bin_output(int val) 
{
        int i;
            char str[33];
                for (i = 31; i >= 0; i--)
                        str[31-i] = '0' + ((val >> i) & 0x1);
                            str[32] = 0;
                                puts(str);
                                    return;
}


void byebye()
{
    sck_low();
    sdi_low();
    cs_low();
    //printf("cleaning up\n");
    /* when not explicitly given, munmap() will automatically
       be called on exit (see 'man munmap') */
    munmap(mymem, getpagesize()); 
}

