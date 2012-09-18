#include<iaza.h>
#include<iazawin5.c>
#include<rft5.c>
union REGS r;
struct SREGS sr;
struct
{
 unsigned char drive;
 unsigned char unit;
 unsigned int bytexsec;
 unsigned char secxclus;
 unsigned char boh;
 unsigned int boot_sec_num;
 unsigned char FAT_num;
 unsigned int root_entries_num;
 unsigned int data_off;
 unsigned int cluster_num;
 unsigned char secxFAT;
 unsigned char boh3;
 unsigned char root_off;
 unsigned int device_off;
 unsigned int device_seg;
 unsigned char status;
 unsigned char media_byte;
 unsigned int next_off;
 unsigned int next_seg;
 unsigned int boh2[30];
}far *ss0;
struct
{
 char ll,lll,llll;
 char sign[8];
} far *sss0;

char bugg[512];
int n,driveinfo,kd;
unsigned int i60seg,i61seg;
unsigned int i60off,i61off;
int formatta(void)
{
 char buff[60*512],ii[]="Iazasoft";
 unsigned int cluster,x=5,y=8,piolo=0,vdata;
 double data,gg,gg1;
 double data1;
 piolo=absread(driveinfo,1,0,bugg);
 if(piolo==0)
 {
  for(piolo=3;piolo<=11;piolo++) bugg[piolo]=ii[piolo-3];
  abswrite(driveinfo,1,0,bugg);
 }
 absread(driveinfo,ss0->secxFAT,1,buff);
 for(n=3;n<=5;n++)
 {
  vt_gotoxy(wi[0].x1+1,wi[0].y1+n);
  vt_puts("                          ");
 }
 vt_gotoxy(wi[0].x1+5,wi[0].y1+6);
 vt_color=0xb0;
 vt_printf("Executing...");
 vt_color=0x3e;
 for(cluster=2;cluster<=ss0->cluster_num;cluster++)
 {
  gg=(double)cluster;
  gg1=(double)ss0->cluster_num;
  data=gg*100;
  data1=data/gg1;
  data=data1*30;
  data1=data/100;
  vt_gotoxy(wi[0].x1+5,wi[0].y1+8);
  piolo=(unsigned int)data1;
  for(n=0;n<=piolo;n++)
  {
   vt_putch('²');
  }
  if(ss0->cluster_num>4080)
  {
   vdata=prossimo_16b(cluster,&buff);
   if(vdata!=0xfff7) mark_16b(cluster,0,&buff);
  }
  else
  {
   vdata=prossimo_12b(cluster,&buff);
   if(vdata!=0xff7) mark_12b(cluster,0,&buff);
  }
 }
 vt_gotoxy(wi[0].x1+5,wi[0].y1+6);
 vt_printf("Updating FAT");
 abswrite(driveinfo,ss0->secxFAT,1,buff);
 if(ss0->FAT_num>1) abswrite(driveinfo,ss0->secxFAT,ss0->secxFAT+ss0->boot_sec_num,buff);
 vt_gotoxy(wi[0].x1+5,wi[0].y1+6);
 vt_printf("Updating Root Dir.....");
 absread(driveinfo,ss0->data_off-ss0->root_off,ss0->root_off,buff);
 for(n=0;n<=(ss0->data_off-ss0->root_off)*512;n++) buff[n]=0;
 abswrite(driveinfo,ss0->data_off-ss0->root_off,ss0->root_off,buff);
 kd=27;
}
int esci(void)
{
 mouse(2);

 putmem(0,wi[0].x1,wi[0].y1,wi[0].x2,wi[0].y2);
 poke(0,0x60*4,i60off);
 poke(0,0x60*4+2,i60seg);
 exit(0);
}
main(argc,argv)
int argc;
char *argv[];
{
 inizializza();
 if(argc==1) driveinfo=getdisk();
 else
 if(argc!=2)
 {
  printf("Errore nei parametri... sintassi : tf <drive:>\n");
  exit(1);
 }
 else
 {
  strupr(argv[1]);
  driveinfo=argv[1][0]-'A';
 }
 i60off=peek(0,0x60*4);
 i60seg=peek(0,0x60*4+2);
 poke(0,0x60*4,peek(0,0x21*4));
 poke(0,0x60*4+2,peek(0,0x21*4+2));
 i61off=peek(0,0x61*4);
 i61seg=peek(0,0x61*4+2);
 poke(0,0x61*4,peek(0,0x13*4));
 poke(0,0x61*4+2,peek(0,0x13*4+2));

 printf("Turbo Formatter v 4.0 ");
 p_author();
 printf(" 1991(c)\n");
 menutype(0,0x10,0x03,0x04,0x20);
 setmenuP(0," Yes ",1,formatta);
 setmenuP(0," No ",1,esci);
 getmem(0,5,5,60,15);
 vt_wind(5,5,60,15,1," Turbo Formatter ",0x0e,0x0e,' ',0x30,1,0);
 vt_color=0x1e;
 vt_gotoxy(wi[0].x1+5,wi[0].y1+8);
 for(n=0;n<=30;n++) vt_putch('°');
 vt_color=0x30;
 r.h.ah=0x32;
 r.x.dx=driveinfo+1;
 int86x(0x60,&r,&r,&sr);
 if(r.h.al!=0) {vt_printf("Drive non valido\n");exit(1);}
 ss0=MK_FP(sr.ds,r.x.bx);
 vt_gotoxy(wi[0].x1+28,wi[0].y1+2);
 vt_printf("Drive.........%c:",driveinfo+'A');
 vt_gotoxy(wi[0].x1+28,wi[0].y1+3);
 if(ss0->drive!=ss0->unit)
 vt_printf("Drive Type....Device Driven");
 else if(ss0->media_byte==0xf8)
 vt_printf("Drive Type....Hard Disk");
 else
 {
  r.h.ah=8;
  r.h.dl=driveinfo;
  int86(0x61,&r,&r);
  if((r.h.bl==1) || (r.h.bl==2))
  vt_printf("Drive Type....5¬\"");
  if((r.h.bl==3) || (r.h.bl==4))
  vt_printf("Drive Type....3«\"");
 }
 vt_gotoxy(wi[0].x1+28,wi[0].y1+4);
 if(ss0->cluster_num>4080)
 vt_printf("FAT type.........16-bit");
 else
 vt_printf("FAT type.........12-bit");
 vt_gotoxy(wi[0].x1+28,wi[0].y1+5);
 vt_printf("Media byte.......%X",ss0->media_byte);
 n=absread(driveinfo,1,0,bugg);
 if(n==0)
 {
  vt_gotoxy(wi[0].x1+28,wi[0].y1+6);
  sss0=bugg;
  vt_printf("Signature........%s",sss0->sign);
 }
 vt_gotoxy(wi[0].x1+1,wi[0].y1+3);
 vt_puts("Attenzione !!!  Tutti i");
 vt_gotoxy(wi[0].x1+1,wi[0].y1+4);
 vt_puts("dati andranno persi.");
 vt_gotoxy(wi[0].x1+1,wi[0].y1+5);
 vt_puts("Vuoi Formattare il disco ?");
 sound(800);
 delay(400);
 nosound();
 mouse(0);
 mouse(1);
 do {
 while((kd=ikey())==0){}
 if(kd==-1){
 if(k_y==wi[0].y1)
  if((k_x>wi[0].x1) && (k_x<wi[0].x2)) movewind2(0);
 if (k_y==wi[0].y1+1)
  if((k_x>wi[0].x1+1) && (k_x<wi[0].x2-1)) menuto(0,1);
 }
 if((kd=='y') || (kd=='Y')) formatta();
 if((kd=='n') || (kd=='N')) esci();
 }while(kd!=27);
 mouse(2);

 putmem(0,wi[0].x1,wi[0].y1,wi[0].x2,wi[0].y2);
 poke(0,0x61*4,i61off);
 poke(0,0x61*4+2,i61seg);
 poke(0,0x60*4,i60off);
 poke(0,0x60*4+2,i60seg);

}
