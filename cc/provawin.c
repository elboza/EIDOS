#include<iaza.h>
#include<iazawin2.h>
int kd;
int exit_prg()
{
 mouse(2);
 putmem(0,wi[0].x1,wi[0].y1,wi[0].x2,wi[0].y2);
 exit(0);
}
int hh()
{
 sound(800);
 delay(500);
 nosound();
 return(0);
}
int gg()
{
 sound(200);
 delay(500);
 nosound();
 return(0);
}
main()
{
 inizializza();
 menutype(0,0x70,0x01,0x04,0x20);
 setmenuP(0," Files ",1,menusec);
 setmenuP(0," Help ",1,gg);
 setmenuP(0," Quit! ",1,exit_prg);
 setmenuS(0,0," Haha ",1,hh);
 getmem(0,5,5,60,10);
 vt_wind(5,5,60,10,1," About... ",0x20,0x40,' ',0x1e,1,0);
 vt_color=0x1e;
 vt_gotoxy(wi[0].x1+1,wi[0].y1+2);
 vt_puts(" Fernando Iazeolla alle Tastiere....");
 vt_gotoxy(wi[0].x1+1,wi[0].y1+3);
 vt_puts(" Fernando Iazeolla ai Dischi...");
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
 }while(kd!=27);
 mouse(2);
 putmem(0,wi[0].x1,wi[0].y1,wi[0].x2,wi[0].y2);
}
