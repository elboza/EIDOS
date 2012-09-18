#include<iaza.h>
#include<alloc.h>
#include<ikey2.c>
#include<vt_bios2.c>
#include<elfab2.c>
int kd=0;
long int x,x2;
char *nort[20];
unsigned int y;
main()
{
 getmm[0]=(char*)malloc(80*43*2);
 getmem(0,10,10,50,20);
 vt_wind(10,10,50,20,1," Memory ",0x0e,0x1e,' ',0x02,1,0);
 mouse(0);
 mouse(1);
 while(kd!=13)
 {
  while((kd=ikey())==0){}
  if(kd==-1)
  {
   if(k_y/8==wi_y1[0])
   {
    if((k_x/8>wi_x1[0]) && (k_x/8<wi_x2[0])) movewind(0);
   }
  }
 }
 mouse(2);
 putmem(0,wi_x1[0],wi_y1[0],wi_x2[0],wi_y2[0]);
 x=biosmemory();
 x=x*1024;
 printf("Iaza Memory Information v 1.00\n");
 putnorton(x,&nort);
 printf("Memoria Totale.....%s bytes\n",nort);
 x2=(long)_psp*16;
 x=x-x2;
 putnorton(x,&nort);
 printf("Memoria rimanente..%s bytes\n",nort);
 y=peek(0,0x415);
 putnorton((long)y*1024,&nort);
 printf("\nMemoria estesa Totale.....%s bytes\n",nort);
 r.h.ah=0x88;
 int86(0x15,&r,&r);
 y=r.x.ax;
 putnorton((long)y*1024,&nort);
 printf("Memoria estesa Rimanente...%s bytes\n",nort);
}
