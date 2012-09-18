#include<iaza.h>
#include<ikey2.c>
#include<rft.c>
#include<vt_bios2.c>
#include<elfab2.c>
void err(void)
{
 printf("Map funziona solo con Floppy disk A e B ...\n");
 exit(1);
}
main(argc,argv)
int argc;
char *argv[];
{
 struct dfree d;
 int n,x,tot,dr,wx,kd=0;
 char scl[8],stot[10],slib[10];
 double tota,lib;
 fat=(unsigned int*)malloc(512*41);
 if(strcmp(strupr(argv[1]),"A:")==0) dr=0;
 if(strcmp(strupr(argv[1]),"B:")==0) dr=1;
 if(dr>1) err();
 mouse(0);
 mouse(1);
 mouse(2);
 setmwin(0,0,79,42);
 vt_font8x8();
 getmem(0,0,0,79,42);
 vt_wind(0,0,79,42,1," Map Disk ",0x0e,0x4e,' ',0x1e,0,0);
 getmem(1,25,20,55,24);
 vt_wind(25,20,55,24,1,"",0,0x2a,' ',0x2f,1,1);
 vt_gotoxy(wi_x1[1]+2,wi_y1[1]+2);
 vt_puts("Reading Disk Information...");
 x=boot(dr);
 getdfree(dr+1,&d);
 tot=d.df_total;
 tota=(double)d.df_bsec*(double)d.df_sclus*(double)d.df_total;
 lib=(double)d.df_bsec*(double)d.df_sclus*(double)d.df_avail;
 x=read_12b_fat(dr,secperfat,1);
 if(x!=0) {cprintf("error"); exit(1);}
 x=0;
 putmem(1,wi_x1[1],wi_y1[1],wi_x2[1],wi_y2[1]);
 vt_color=0x1e;
 vt_gotoxy(1,1);
 for(n=2;n<=tot;n++)
 {
  if((fat[n]==0xff7) || (fat[n]==0xfff7)) vt_putch('B');else
  if(fat[n]!=0) vt_putch(8);
  else vt_putch('ú');
  if((wx=vt_wherex())==79){vt_gotoxy(1,vt_wherey()+1);}

 }
 getmem(1,37,27,75,36);
 vt_wind(37,27,75,36,1," Information ",0x47,0x4c,' ',0x40,1,1);
 mouse(1);
 vt_gotoxy(wi_x1[1]+1,wi_y1[1]+1);
 vt_printf("Map Disk v 1.0 by Iaza Soft 1990(c).");
 vt_gotoxy(wi_x1[1]+1,vt_wherey()+2);
 vt_printf("Mapping drive %s...",argv[1]);
 vt_gotoxy(wi_x1[1]+1,vt_wherey()+1);
 vt_printf("Sectors per FAT: %d",secperfat);
 putnorton(n,&scl);
 vt_gotoxy(wi_x1[1]+1,vt_wherey()+1);
 vt_printf("Number of Clusters: %s",scl);
 vt_gotoxy(wi_x1[1]+1,vt_wherey()+1);
 putnorton(tota,&stot);
 vt_printf("Bytes totali: %s",stot);
 vt_gotoxy(wi_x1[1]+1,vt_wherey()+1);
 putnorton(lib,&slib);
 vt_printf("Bytes liberi: %s",slib);
 while(kd!=13)
 {
  while((kd=ikey())==0){}
  if(kd==-1)
  {
   if(k_y/8==wi_y1[1])
   {
    if((k_x/8>wi_x1[1]) && (k_x/8<wi_x2[1])) movewind(1);
   kd=0;
   }
  if((k_y/8==0) && (k_x/8==3)) kd=13;
  }
 }
 mouse(2);
 putmem(1,wi_x1[1],wi_y1[1],wi_x2[1],wi_y2[1]);
 putmem(0,0,0,79,42);
 vt_fontn();
 r.h.ah=1;
 r.h.ch=7;
 r.h.cl=6;
 int86(0x10,&r,&r);
}
