#include<iaza.h>
#include<gwin.c>
int kd=0,dato,x,curx;
unsigned int ddd,size;
char num,*sfo,nome[15],nome2[15];
char buff[512];
struct ffblk f;
int hh()
{
 sound(300);
 delay(300);
 nosound();
 return(0);
}
int gg()
{
 findfirst("*.*",&f,0x3f);
 gprintf("%s",f.ff_name);
 moveto(wi[status.active_window].x1+5,gety()+10);
 return(0);
}
int esci()
{
 mouse(2);
 nogwin();
 finisci();
 exit(0);
 return(0);
}
main()
{
 strcpy(status.nomefile,"base.idl");
 inizializza();
 setmenuP(0," Files ",1,hh);
 setmenuP(0," Compile ",1,menuto2);
 setmenuP(0," Quit! ",1,esci);
 setmenuS(0,1," Ciao ",1,hh);
 setmenuS(0,1," Addio ",1,gg);
 gwindow(60,60,300,200," Main Win ",12,1,14,3);
 num=status.active_window;
 perc_init();
 for(x=0;x<=37;x++)
 {
  percent(x,37);
 }
 perc_end();
 mouse(1);
 while(kd!=27)
 {
  while((kd=ikey())==0) {}
  controlla(kd);
  x=contr_drives();
  if(x!=-1) {setdisk(x);dato=x;}
 }
 mouse(2);
 nogwin();
 finisci();
 return(0);
}
