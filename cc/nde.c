#include<iaza.h>
#include<over.c>
int d,sec,n,m,x,s,pag,ch;
unsigned char by;
char *iaza,*boot;
unsigned char uno,due,fend,rin,ren;
void input(void);void pp(void);void getsec(void);void info(void);
void si(void);void gd(void);
void input(void)
{
 char pp[7];
 gets(pp);
 if(strcmp(pp,"")==0) sec=sec;else sec=atoi(pp);
}
void info(void)
{
 absread(d,1,0,boot);
 fend=boot[16]*(boot[23]*256+boot[22]);
 rin=fend+1;
 uno=boot[18];due=boot[17];
 ren=(32*(uno*256+due)/512)+fend+1;
}
void si(void)
{
 cprintf("0 Boot             1-%d  FAT\n\r",fend);
 cprintf("%d-%d Root Dir.    >%d Data\n\r",rin,ren,ren);
}
void getsec(void)
{
 absread(d,1,sec,iaza);
 gotoxy(72,1);cprintf("     ");
 gotoxy(65,1);cprintf("Sector:%d",sec);
 gotoxy(55,1);cprintf("Drive:%d",d);
 gotoxy(1,3);
 pp();
}
void pp(void)
{
 gotoxy(1,3);
 for(m=3;m<=18;m++)
 {
 if(m==3) x=0; else x+=16;
 for(n=x+pag;n<=x+15+pag;n++)
 {
  by=iaza[n];
  if(by<0x10) { cprintf("0");cprintf("%X ",by);} else cprintf("%X ",by);
 }
 s=0;
 for(n=x+pag;n<=x+15+pag;n++) {
  gotoxy(59+s,m);
  s++;
  if(isprint(iaza[n]))
  { cprintf("%c",iaza[n]);}
  else {cprintf(".");}
   if(n==x+15+pag)
   {
    putch(13);
    cprintf("\n");
   }
 }
}
 gotoxy(1,2); cprintf("                                                  ");
 gotoxy(1,2);
 if(sec==0)  cprintf("Boot Sector.");
 if((sec>=1) && (sec<=fend/2))  cprintf("1st copy of FAT.");
 if((sec>fend/2) && (sec<=fend))  cprintf("2nd copy of FAT.");
 if((sec>=rin) && (sec<=ren)) cprintf("Root Dir.");
 if(sec>ren) cprintf("Data Sectors.");
}
void gd(void)
{
 if((d==65) || (d==97)) d=0;
 if((d==66) || (d==98)) d=1;
 if((d==67) || (d==99)) d=2;
 if((d==68) || (d==100)) d=3;
 if((d==69) || (d==101)) d=4;
 if((d==13)||(d==0x27)) d=getdisk();
}
main(argc,argv)
int argc;
char *argv[];
{
 if(argc>2) { printf("ERRORE!! di sintassi.\n"); exit(1); }
 if(strcmp(strlwr(argv[1]),"a:")==0) d=0;
 if(strcmp(strlwr(argv[1]),"b:")==0) d=1;
 if(strcmp(strlwr(argv[1]),"c:")==0) d=2;
 if(strcmp(strlwr(argv[1]),"d:")==0) d=3;
 if(strcmp(strlwr(argv[1]),"e:")==0) d=4;
 if(strcmp(argv[1],"")==0) d=getdisk();
 finestra(1,1,78,23,15,1,1);
 iaza=(char*)malloc(512);
 textcolor(14);
 cprintf("Disk Edit: by Iaza Soft 1990(c) v 1.0.\n");
 putch(13);
 textcolor(15);
 boot=(char*)malloc(512);
 info();
 sec=0;
 pag=0;
 getsec();
 textcolor(14);
 gotoxy(1,19);cprintf("Alt F1=Drive   ,F2= Ch.Sector     ,PgUp,PgDn,+,-");
 textcolor(15);
 for(;;)
 {
  ch=getch();
  if(ch=='+') { pag=0;sec++;getsec();continue;}
  if(ch=='-') { pag=0;sec--;getsec();continue;}
  if(ch==0) ch=getch();
  if((ch==81) && (pag==0)) { pag=256; pp(); }
  if((ch==73) && (pag==256)) { pag=0; pp(); }
  if(ch==68) break;
  if(ch==60) { pag=0;info();finestra(10,10,60,20,15,10,2);si();cprintf("Sector?");input();nowin(10,10,60,20,2);textbackground(1);getsec();}
  if(ch==104) { pag=0;finestra(5,5,30,10,0,10,2);cprintf("Drive?");d=getch();gd();nowin(5,5,30,10,2);textbackground(1);getsec();}
 }
 nowin(1,1,78,23,1);
}
