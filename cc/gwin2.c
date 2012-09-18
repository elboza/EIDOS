#include<stdarg.h>
#include<stdio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
#include<gwin.h>
void vt_p_author(void)
{
 int n=1,cc=3;
 char str[14]="";
 str[0]=0x16c;
 str[1]=0x144;
 str[2]=0x15f;
 str[3]=0x144;
 str[4]=0x105;
 str[5]=0x176;
 str[6]=0x14a;
 str[7]=0x143;
 str[8]=0x151;
 str[9]=0;
 while(n!=0x125)
 {
  n=str[cc];
  n=n^0x125;
  str[cc]=n;
  cc++;
 }
 outtext(str);
}
void mouse(int ax)
{
 r.x.ax=ax;
 int86(0x33,&r,&r);
}
int ikey(void)
{
 int cc,ch2;
char he;
char ch;
 mouse(3);
 if((ch=kbhit())!=0) { ch=bioskey(1); ch2=bioskey(0);
 if(ch==0) return((((ch2-256)/256)+1)+256);
 return(ch);
 }
  if(r.x.bx==1) {ch2=0;k_x=r.x.cx;k_y=r.x.dx;return(-1);}
  if(r.x.bx==2) {ch2=0;k_x=r.x.cx;k_y=r.x.dx;return(-2);}
}
void vt_setmode(char nn)
{
 r.h.ah=0;
 r.h.al=nn;
 int86(0x10,&r,&r);
}
void setmwin(int x1,int y1,int x2,int y2)
{
 r.x.cx=x1;
 r.x.dx=x2;
 mouse(7);
 r.x.cx=y1;
 r.x.dx=y2;
 mouse(8);
}
char getrow(void)
{
 char xx;
 xx=peekb(0,0x484);
 return(xx);
}
char* putnorton(double d)
{
 char s[20],s2[30];
 int x,n,m,p=0;
 gcvt(d,20,s);
 x=strlen(s);
 m=x+(int)(x/3);
 p=0;
 for(n=x;n>=0;n--)
 {
  s2[m]=s[n];
  if((p==3) && (n==0)) {s2[m-1]=' ';p=0;m--;strcpy(s,s2+1);strcpy(s2,s);}
  if(p==3) {s2[m-1]='.';p=0;m--;}
  p++;
  m--;
 }
 return(s2);
}
process(int(*p)())
{
 (*p)();
 return(0);
}
void gprintf(char *fmt,...)
{
 int len;
 char str[160];
 va_list argptr;
 va_start (argptr,fmt);
 len=vsprintf(str,fmt,argptr);
 va_end(argptr);
 outtext(str);
}
void gwindow(int x1,int y1,int x2,int y2,char *s,char scol,char scolb,char bcol,char rcol)
{
 int len,x,size;
 mandir=5;
 putimage(manx,many,manf,COPY_PUT);
 if(status.active_window!=-1) {wi[status.active_window].gx=getx();wi[status.active_window].gy=gety();wi[status.active_window].gc=getcolor();}
 status.active_window++;
 size=status.active_window;
 wi[size].bcol=bcol;
 wi[size].scol=scol;
 wi[size].scolb=scolb;
 wi[size].riemp=rcol;
 size=imagesize(x1-1,y1-1,x2+3+4,y2+3+4);
 wi[status.active_window].size=size;
 if((getmm[status.active_window]=(char *)malloc(size))==0) {outtext("Errore di allocazione");exit(1);}
 getimage(x1-1,y1-1,x2+3+4,y2+3+4,getmm[status.active_window]);
 bar(x1,y1,x2,y2);
 setlinestyle(SOLID_LINE,0,3);
 setcolor(bcol);
 rectangle(x1,y1,x2,y2);
 setlinestyle(SOLID_LINE,0,1);
 line(x1,y1+20,x2,y1+20);
 setfillstyle(SOLID_FILL,scolb);
 floodfill(x1+5,y1+5,bcol);
 setfillstyle(SOLID_FILL,rcol);
 floodfill(x1+5,y1+25,bcol);
 setcolor(scol);
 x=(x2+x1)/2;
 len=strlen(s)*8/2;
 outtextxy(x-len,y1+10,s);
 wi[status.active_window].x1=x1;
 wi[status.active_window].y1=y1;
 wi[status.active_window].x2=x2;
 wi[status.active_window].y2=y2;
 setfillstyle(SOLID_FILL,0);
 bar(x2+3,y1+5,x2+3+4,y2+3+4);
 bar(x1+5,y2+3,x2+3+4,y2+3+4);
 moveto(x1+5,y1+21);
 if(wi[status.active_window].MP_count>0) {make_menu();moveto(x1+5,y1+37);}
}
void nogwin(void)
{
 int n,m;
 mandir=5;
 putimage(manx,many,manf,COPY_PUT);
 putimage(wi[status.active_window].x1-1,wi[status.active_window].y1-1,getmm[status.active_window],COPY_PUT);
 for(n=0;n<=9;n++) wi[status.active_window].mp[n].MS_count=0;
 wi[status.active_window].MP_count=0;
 free(getmm[status.active_window]);
 status.active_window--;
 moveto(wi[status.active_window].gx,wi[status.active_window].gy);
 setcolor(wi[status.active_window].gc);
}
void inizializza(char *nomefile)
{
 int n,m,*point,numdrives;
 char *nd;
 unsigned int dpb_off,dpb_seg;
 FILE *fp;
 status.active_window=-1;
 status.active_p_menu=-1;
 status.drv_light=0;
 for(n=0;n<=9;n++)
 {
  status.drs[n]=0;
 }
 for(n=0;n<=4;n++)
 {
  wi[n].MP_count=0;
  for(m=0;m<=9;m++) wi[n].mp[m].MS_count=0;
 }
 setcolor(14);
 for(n=0;n<=7000;n++)
 {
  putpixel(random(100)+535,random(25)+300,4);
 }
 for(n=0;n<=1000;n++)
 {
  putpixel(random(100)+535,random(25)+300,8);
  outtextxy(550,310,"Iaza Soft");
 }
 i60off=peek(0,0x60*4);
 i60seg=peek(0,0x60*4+2);
 poke(0,0x60*4,peek(0,0x21*4));
 poke(0,0x60*4+2,peek(0,0x21*4+2));
 i61off=peek(0,0x61*4);
 i61seg=peek(0,0x61*4+2);
 poke(0,0x61*4,peek(0,0x13*4));
 poke(0,0x61*4+2,peek(0,0x13*4+2));
 r.h.ah=0x52;
 int86x(0x60,&r,&r,&sr);
 point=MK_FP(sr.es,r.x.bx);
 nd=MK_FP(sr.es,r.x.bx+32);;
 numdrives=*nd;
 status.numdrives=numdrives;
 dpb_off=*point;
 point=MK_FP(sr.es,r.x.bx+2);
 dpb_seg=*point;
 s0=MK_FP(dpb_seg,dpb_off);
 if(s0->drive!=s0->unit) {draw_ram(570,10,s0->drive+'A');status.drs_type[0]='R';}
 else if(s0->media_byte==248) {draw_hd(570,10,s0->drive+'A');status.drs_type[0]='H';}
 else {r.h.ah=8; r.h.dl=s0->drive; int86(0x61,&r,&r); if((r.h.bl==1) || (r.h.bl==2)) {draw_5(570,10,s0->drive+'A');status.drs_type[0]=5;}
 else if((r.h.bl==3) || (r.h.bl==4)) {draw_3(570,10,s0->drive+'A');status.drs_type[0]=3;} else {gprintf("UNKNOWN DRIVE");status.drs_type[0]='U';}}
 status.drs[0]=s0->drive;
 for(n=1;n<=numdrives-1;n++)
 {
  s0=MK_FP(s0->next_seg,s0->next_off);
  if(s0->drive!=s0->unit) {draw_ram(570,10+(n*40),s0->drive+'A');status.drs_type[n]='R';}
  else if(s0->media_byte==248) {draw_hd(570,10+(n*40),s0->drive+'A');status.drs_type[n]='H';}
  else {r.h.ah=8; r.h.dl=s0->drive; int86(0x61,&r,&r); if((r.h.bl==1) || (r.h.bl==2)) {draw_5(570,10+(n*40),s0->drive+'A');status.drs_type[n]=5;}
  else if((r.h.bl==3) || (r.h.bl==4)) {draw_3(570,10+(n*40),s0->drive+'A');status.drs_type[n]=3;} else {gprintf("UNKNOWN DRIVE");status.drs_type[n]='U';}}
  status.drs[n]=s0->drive;
 }
 i1coff=peek(0,0x1c*4);
 i1cseg=peek(0,0x1c*4+2);
 r.h.ah=0x25;
 r.h.al=0x1c;
 sr.ds=FP_SEG(int1c);
 r.x.dx=FP_OFF(int1c);
 int86x(0x60,&r,&r,&sr);
 if((mansfo=(char *)malloc(118))==NULL) {gprintf("Errore di allocazione mansfo");exit(1);}
 if((mansx1=(char *)malloc(118))==NULL) {gprintf("Errore di allocazione mansx1");exit(1);}
 if((mansx2=(char *)malloc(118))==NULL) {gprintf("Errore di allocazione mansx2");exit(1);}
 if((mansx3=(char *)malloc(118))==NULL) {gprintf("Errore di allocazione mansx3");exit(1);}
 if((mandx1=(char *)malloc(118))==NULL) {gprintf("Errore di allocazione mandx1");exit(1);}
 if((mandx2=(char *)malloc(118))==NULL) {gprintf("Errore di allocazione mandx2");exit(1);}
 if((mandx3=(char *)malloc(118))==NULL) {gprintf("Errore di allocazione mandx3");exit(1);}
 if((mans1=(char *)malloc(118))==NULL) {gprintf("Errore di allocazione mans1");exit(1);}
 if((mans2=(char *)malloc(118))==NULL) {gprintf("Errore di allocazione mans2");exit(1);}
 if((mans3=(char *)malloc(118))==NULL) {gprintf("Errore di allocazione mans3");exit(1);}
 if((mand1=(char *)malloc(118))==NULL) {gprintf("Errore di allocazione mand1");exit(1);}
 if((mand2=(char *)malloc(118))==NULL) {gprintf("Errore di allocazione mand2");exit(1);}
 if((mand3=(char *)malloc(118))==NULL) {gprintf("Errore di allocazione mand3");exit(1);}
 if((manf=(char *)malloc(118))==NULL) {gprintf("Errore di allocazione manf");exit(1);}
 if((fp=fopen(nomefile,"rb+"))==0) {gprintf("Errore nell'aprire %s.idl",nomefile);exit(1);}
 fseek(fp,0L,SEEK_SET);
 n=search_idl("mansx1",fp);
 if(n!=0) fread(mansx1,1,n,fp);

 fseek(fp,0L,SEEK_SET);
 n=search_idl("mansx2",fp);
 if(n!=0) fread(mansx2,1,n,fp);

 fseek(fp,0L,SEEK_SET);
 n=search_idl("mansx3",fp);
 if(n!=0) fread(mansx3,1,n,fp);

 fseek(fp,0L,SEEK_SET);
 n=search_idl("mandx1",fp);
 if(n!=0) fread(mandx1,1,n,fp);

 fseek(fp,0L,SEEK_SET);
 n=search_idl("mandx2",fp);
 if(n!=0) fread(mandx2,1,n,fp);

 fseek(fp,0L,SEEK_SET);
 n=search_idl("mandx3",fp);
 if(n!=0) fread(mandx3,1,n,fp);

 fseek(fp,0L,SEEK_SET);
 n=search_idl("mans1",fp);
 if(n!=0) fread(mans1,1,n,fp);

 fseek(fp,0L,SEEK_SET);
 n=search_idl("mans2",fp);
 if(n!=0) fread(mans2,1,n,fp);

 fseek(fp,0L,SEEK_SET);
 n=search_idl("mans3",fp);
 if(n!=0) fread(mans3,1,n,fp);

 fseek(fp,0L,SEEK_SET);
 n=search_idl("mand1",fp);
 if(n!=0) fread(mand1,1,n,fp);

 fseek(fp,0L,SEEK_SET);
 n=search_idl("mand2",fp);
 if(n!=0) fread(mand2,1,n,fp);

 fseek(fp,0L,SEEK_SET);
 n=search_idl("mand3",fp);
 if(n!=0) fread(mand3,1,n,fp);

 fseek(fp,0L,SEEK_SET);
 n=search_idl("manf",fp);
 if(n!=0) fread(manf,1,n,fp);

 fclose(fp);
 manx=500;many=260;
 getimage(500,260,500+9,260+13,mansfo);
 putimage(500,260,manf,COPY_PUT);
}
int search_idl(char *item,FILE *fp)
{
 int xl,n,size;
 char nome[20];
 while(feof(fp)==0)
 {
  fscanf(fp,"%s %u",nome,&size);
  xl=strlen(nome);
  for(n=0;n<=xl-1;n++) nome[n]=nome[n]-1;
  if(strcmp(nome,item)==0) return(size);
  else fseek(fp,size,SEEK_CUR);
 }
 return(0);
}
void finisci(void)
{
 r.h.ah=0x25;
 r.h.al=0x1c;
 sr.ds=i1cseg;
 r.x.dx=i1coff;
 int86x(0x60,&r,&r,&sr);
 poke(0,0x60*4,i60off);
 poke(0,0x60*4+2,i60seg);
 poke(0,0x61*4,i61off);
 poke(0,0x61*4+2,i61seg);
}
void movewindow(void)
{
 int num,spx,spy,sp1,sp2,varx1,varx2,vary1,vary2,sx1,sx2,sy1,sy2,px,py,gc;
 char *latox1,*latox2,*latoy1,*latoy2;
 mandir=5;
 putimage(manx,many,manf,COPY_PUT);
 num=status.active_window;
 px=k_x;
 py=k_y;
 gc=getcolor();
 if((spost[num]=(char *)malloc(wi[num].size))==0) {outtext("Errore di allocazione win..."); exit(1);}
 sx1=imagesize(wi[num].x1,wi[num].y1,wi[num].x2,wi[num].y1);
 sx2=imagesize(wi[num].x1,wi[num].y2,wi[num].x2,wi[num].y2);
 sy1=imagesize(wi[num].x1,wi[num].y1,wi[num].x1,wi[num].y2);
 sy2=imagesize(wi[num].x2,wi[num].y1,wi[num].x2,wi[num].y2);
 if((latox1=(char *)malloc(sx1+20))==0) {outtext("Errore di allocazione x1..."); exit(1);}
 if((latox2=(char *)malloc(sx2+20))==0) {outtext("Errore di allocazione x2..."); exit(1);}
 if((latoy1=(char *)malloc(sy1+20))==0) {outtext("Errore di allocazione y1..."); exit(1);}
 if((latoy2=(char *)malloc(sy2+20))==0) {outtext("Errore di allocazione y2..."); exit(1);}
 spx=k_x-wi[num].x1;
 spy=k_y-wi[num].y1;
 mouse(2);
 getimage(wi[num].x1-1,wi[num].y1-1,wi[num].x2+2+4,wi[num].y2+2+4,spost[status.active_window]);
 sp1=wi[num].x2-wi[num].x1;
 sp2=wi[num].y2-wi[num].y1;
 setmwin(spx+5,spy+5,639-(wi[num].x2-wi[num].x1)+spx-10,349-(wi[num].y2-wi[num].y1)-10);
 getimage(k_x-spx,k_y-spy,k_x-spx+sp1,k_y-spy,latox1);
 getimage(k_x-spx,k_y-spy,k_x-spx,k_y-spy+sp2,latoy1);
 getimage(k_x-spx+sp1,k_y-spy,k_x-spx+sp1,k_y-spy+sp2,latoy2);
 getimage(k_x-spx,k_y-spy+sp2,k_x-spx+sp1,k_y-spy+sp2,latox2);
 setcolor(0);
 rectangle(k_x-spx,k_y-spy,k_x-spx+sp1,k_y-spy+sp2);
 varx1=k_x;
 varx2=varx1;
 vary1=k_y;
 vary2=vary1;
 while(r.x.bx==1)
 {
  if((varx2!=varx1) || (vary2!=vary1))
  {
   putimage(varx2-spx,vary2-spy,latox1,COPY_PUT);
   putimage(varx2-spx,vary2-spy,latoy1,COPY_PUT);
   putimage(varx2-spx+sp1,vary2-spy,latoy2,COPY_PUT);
   putimage(varx2-spx,vary2-spy+sp2,latox2,COPY_PUT);
   varx2=varx1;
   vary2=vary1;
   getimage(varx2-spx,vary2-spy,varx2-spx+sp1,vary2-spy,latox1);
   getimage(varx2-spx,vary2-spy,varx2-spx,vary2-spy+sp2,latoy1);
   getimage(varx2-spx+sp1,vary2-spy,varx2-spx+sp1,vary2-spy+sp2,latoy2);
   getimage(varx2-spx,vary2-spy+sp2,varx2-spx+sp1,vary2-spy+sp2,latox2);
   rectangle(varx2-spx,vary2-spy,varx2-spx+sp1,vary2-spy+sp2);
  }
  mouse(3);
  varx1=r.x.cx;
  vary1=r.x.dx;
 }
 putimage(varx2-spx,vary2-spy,latox1,COPY_PUT);
 putimage(varx2-spx,vary2-spy,latoy1,COPY_PUT);
 putimage(varx2-spx+sp1,vary2-spy,latoy2,COPY_PUT);
 putimage(varx2-spx,vary2-spy+sp2,latox2,COPY_PUT);
 putimage(wi[num].x1-1,wi[num].y1-1,getmm[num],COPY_PUT);
 getimage(varx2-spx-1,vary2-spy-1,varx2-spx+sp1+2+4,vary2-spy+sp2+2+4,getmm[num]);
 putimage(varx2-spx-1,vary2-spy-1,spost[num],COPY_PUT);
 mouse(1);
 free(spost[num]);
 free(latox1);
 free(latox2);
 free(latoy1);
 free(latoy2);
 moverel(-(px-varx2),-(py-vary2));
 setcolor(gc);
 wi[num].x1=varx2-spx;
 wi[num].y1=vary2-spy;
 wi[num].x2=varx2-spx+sp1;
 wi[num].y2=vary2-spy+sp2;
 k_x=0;
 k_y=0;
 setmwin(0,0,639,349);
}
void setmenuP(char num,char *s,int lett,int (*p)())
{
 wi[num].mp[wi[num].MP_count].lett=lett;
 wi[num].mp[wi[num].MP_count].p=p;
 strcpy(wi[num].mp[wi[num].MP_count].nome,s);
 wi[num].MP_count++;
}
void make_menu(void)
{
 char num,n,m=0;
 int xx;
 num=status.active_window;
 setlinestyle(SOLID_LINE,0,1);
 setcolor(wi[num].bcol);
 line(wi[num].x1,wi[num].y1+35,wi[num].x2,wi[num].y1+35);
 setfillstyle(SLASH_FILL,1);
 floodfill(wi[num].x1+3,wi[num].y1+30,wi[num].bcol);
 moveto(wi[num].x1+3,wi[num].y1+25);
 for(n=0;n<=wi[num].MP_count-1;n++)
 {
  xx=strlen(wi[num].mp[n].nome);
  for(m=0;m<=xx;m++)
  {
   if(wi[num].mp[n].lett==m) setcolor(wi[num].scol);
   else setcolor(wi[num].bcol);
   gprintf("%c",wi[num].mp[n].nome[m]);
  }
 }
}
void menuto(void)
{
 int n,off=2,x,gx,gy,gc;
 char num;
 mandir=5;
 putimage(manx,many,manf,COPY_PUT);
 gx=getx();
 gy=gety();
 gc=getcolor();
 openmenu=0;
 num=status.active_window;
 moveto(wi[num].x1+3,wi[num].y1+20);
 for(n=0;n<=wi[num].MP_count-1;n++)
 {
  x=strlen(wi[num].mp[n].nome)*8;
  if((k_x>wi[num].x1+off) && (k_x<wi[num].x1+off+x)) {while(r.x.bx!=0){mouse(3);}setcolor(gc);moveto(gx,gy);(*wi[num].mp[n].p)();break;}
  off+=x;
  off+=2;
  openmenu++;
 }
 moveto(gx,gy);
 setcolor(gc);
}
void setmenuS(char numwin,char menp,char *s,int lett,int (*p)())
{
 strcpy(wi[numwin].mp[menp].ms[wi[numwin].mp[menp].MS_count].nome,s);
 wi[numwin].mp[menp].ms[wi[numwin].mp[menp].MS_count].lett=lett;
 wi[numwin].mp[menp].ms[wi[numwin].mp[menp].MS_count].p=p;
 wi[numwin].mp[menp].MS_count++;
}
int menuto2()
{
 int n,xx,m,kdd=0,(*proc)(),gx,gy,gc;
 char num;
 mandir=5;
 putimage(manx,many,manf,COPY_PUT);
 num=status.active_window;
 gx=getx();
 gy=gety();
 gc=getcolor();
 while(r.x.bx!=0){mouse(3);}
 mouse(2);
 gwindow(k_x-5*8,k_y-5,k_x-5*8+15*8,k_y-5+40+(wi[num].mp[openmenu].MS_count*8),wi[num].mp[openmenu].nome,wi[num].scol,wi[num].scolb,wi[num].bcol,wi[num].riemp);
 num++;
 moveto(wi[num].x1+5,wi[num].y1+20+3);
 for(n=0;n<=wi[num-1].mp[openmenu].MS_count;n++)
 {
  xx=strlen(wi[num-1].mp[openmenu].ms[n].nome);
  for(m=0;m<=xx;m++)
  {
   if(wi[num-1].mp[openmenu].ms[n].lett==m) setcolor(wi[num].scol);else setcolor(wi[num].bcol);
   gprintf("%c",wi[num-1].mp[openmenu].ms[n].nome[m]);
  }
  moveto(wi[num].x1+5,wi[num].y1+20+3+(n+1)*10);
 }
 mouse(1);
 while((kdd=ikey())==0) {}
 while(r.x.bx!=0){mouse(3);}
 mouse(2);
 nogwin();
 mouse(1);
 if(kdd==-1)
 {
  if((k_x>wi[num].x1) && (k_x<wi[num].x2))
  {for(n=0;n<=wi[num-1].mp[openmenu].MS_count;n++)
   {
    if((k_y>wi[num].y1+20+(n*10)) && (k_y<wi[num].y1+20+(n*10)+10))
    {
     proc=wi[num-1].mp[openmenu].ms[n].p;
     setcolor(gc);
     moveto(gx,gy);
     (*proc)();
    }
   }}
 }
 return(0);
}
void controlla(int kd)
{
 unsigned char *loc,lloc;
 if(kd==-1)
  {
   if((k_x>wi[status.active_window].x1) && (k_x<wi[status.active_window].x2))
    if((k_y>wi[status.active_window].y1) && (k_y<wi[status.active_window].y1+20))
     movewindow();
   if((k_y>wi[status.active_window].y1+20) && (k_y<wi[status.active_window].y1+35))
    if((k_x>wi[status.active_window].x1+3) && (k_x<wi[status.active_window].x2-3))
     menuto();
  }
 loc=MK_FP(0,0x417);
 lloc=*loc;
 if(lloc==lloc)
 {
  if(kd==UP_KEY)
  {
   mandir=90;
   if(mandir==oldmandir)
   {
    mandir=5;
    putimage(manx,many,manf,COPY_PUT);
   }
  else oldmandir=mandir;
  }
  if(kd==DOWN_KEY)
  {
   mandir=270;
   if(mandir==oldmandir)
   {
    mandir=5;
    putimage(manx,many,manf,COPY_PUT);
   }
   else oldmandir=mandir;
  }
  if(kd==SIN_KEY)
  {
   mandir=0;
   if(mandir==oldmandir)
   {
    mandir=5;
    putimage(manx,many,manf,COPY_PUT);
   }
   else oldmandir=mandir;
  }
  if(kd==DEX_KEY)
  {
   mandir=180;
   if(mandir==oldmandir)
   {
    mandir=5;
    putimage(manx,many,manf,COPY_PUT);
   }
   else oldmandir=mandir;
  }
 }
}
void draw_5(int x,int y,char lett)
{
 setcolor(15);
 rectangle(x,y,x+60,y+30);
 setfillstyle(SOLID_FILL,15);
 floodfill(x+1,y+1,15);
 setcolor(7);
 line(x+2,y+28,x+60,y+28);
 line(x+1,y+29,x+60,y+29);
 line(x,y+30,x+60,y+30);
 line(x+60,y,x+60,y+30);
 line(x+59,y+1,x+59,y+30);
 line(x+58,y+2,x+58,y+30);
 setcolor(0);
 line(x+15,y+20,x+45,y+20);
 line(x+15,y+19,x+45,y+19);
 line(x+23,y+17,x+29,y+17);
 line(x+24,y+18,x+26,y+18);
 circle(x+45,y+8,5);
 setfillstyle(SOLID_FILL,7);
 floodfill(x+45,y+8,0);
 moveto(x+4,y+5);
 gprintf("%c",lett);
}
void draw_3(int x,int y,char lett)
{
 setcolor(15);
 rectangle(x,y,x+60,y+30);
 setfillstyle(SOLID_FILL,15);
 floodfill(x+1,y+1,15);
 setcolor(7);
 line(x+2,y+28,x+60,y+28);
 line(x+1,y+29,x+60,y+29);
 line(x,y+30,x+60,y+30);
 line(x+60,y,x+60,y+30);
 line(x+59,y+1,x+59,y+30);
 line(x+58,y+2,x+58,y+30);
 setcolor(0);
 line(x+15,y+20,x+45,y+20);
 line(x+15,y+19,x+45,y+19);
 line(x+23,y+17,x+37,y+17);
 line(x+23,y+18,x+37,y+18);
 line(x+23,y+21,x+37,y+21);
 line(x+23,y+22,x+37,y+22);
 rectangle(x+40,y+3,x+52,y+9);
 setfillstyle(SOLID_FILL,7);
 floodfill(x+45,y+8,0);
 moveto(x+4,y+5);
 gprintf("%c",lett);
}
void draw_hd(int x,int y,char lett)
{
 setcolor(15);
 rectangle(x,y,x+60,y+30);
 setfillstyle(SOLID_FILL,15);
 floodfill(x+1,y+1,15);
 setcolor(7);
 line(x+2,y+28,x+60,y+28);
 line(x+1,y+29,x+60,y+29);
 line(x,y+30,x+60,y+30);
 line(x+60,y,x+60,y+30);
 line(x+59,y+1,x+59,y+30);
 line(x+58,y+2,x+58,y+30);
 setcolor(0);
 line(x+15,y+11,x+45,y+11);
 line(x+15,y+12,x+45,y+12);
 line(x+15,y+15,x+45,y+15);
 line(x+15,y+16,x+45,y+16);
 rectangle(x+10,y+19,x+22,y+25);
 setfillstyle(SOLID_FILL,7);
 floodfill(x+11,y+20,0);
 moveto(x+4,y+5);
 gprintf("%c",lett);
}
void draw_ram(int x,int y,char lett)
{
 int n;
 setcolor(15);
 rectangle(x,y,x+60,y+30);
 setfillstyle(SOLID_FILL,15);
 floodfill(x+1,y+1,15);
 setcolor(7);
 line(x+2,y+28,x+60,y+28);
 line(x+1,y+29,x+60,y+29);
 line(x,y+30,x+60,y+30);
 line(x+60,y,x+60,y+30);
 line(x+59,y+1,x+59,y+30);
 line(x+58,y+2,x+58,y+30);
 setcolor(0);
 rectangle(x+14,y+10,x+49,y+20);
 setfillstyle(SOLID_FILL,8);
 floodfill(x+20,y+12,0);
 setcolor(14);
 outtextxy(x+20,y+12,"RAM");
 setcolor(0);
 rectangle(x+13,y+9,x+50,y+21);
 line(x+15,y+10,x+15,y+20);
 line(x+16,y+10,x+16,y+20);
 line(x+48,y+10,x+48,y+20);
 line(x+47,y+10,x+47,y+20);
 for(n=0;n<=5;n++)
 {
  line(x+18+(n*5),y+8,x+18+(n*5)+3,y+8);
  line(x+18+(n*5),y+22,x+18+(n*5)+3,y+22);
 }
 moveto(x+4,y+5);
 gprintf("%c",lett);
}
int contr_drives(void)
{
 int n;
 if((k_x>570) && (k_x<570+60))
  for(n=0;n<=status.numdrives-1;n++)
  {
   if((k_y>10+(n*40)) && (k_y<10+(n*40)+30)) {while(r.x.bx!=0){mouse(3);}return(n);}
  }
 return(-1);
}
void interrupt int1c(void)
{
 unsigned char *loc,val,lloc,num;
 int count,n;
 disable();
 loc=MK_FP(0,0x43f);
 lloc=*loc;
 val=*loc;
 if(val!=status.drv_light)
 {
  status.drv_light=val;
  count=0;
  mouse(2);
  for(n=1;n<=8;n=n*2)
  {
   val=lloc;
   val=val & n;
   if(val!=status.drs[count])
   {
    status.drs[count]=val;
    if(status.drs_type[count]==5)
    {
     if(val==0) setfillstyle(SOLID_FILL,7); else setfillstyle(SOLID_FILL,14);
     floodfill(570+45,10+8+(count*40),0);
    }
    if(status.drs_type[count]==3)
    {
     if(val==0) setfillstyle(SOLID_FILL,7); else setfillstyle(SOLID_FILL,12);
     floodfill(570+45,10+8+(count*40),0);
    }
    if(status.drs_type[count]=='H')
    {
     if(val==0) setfillstyle(SOLID_FILL,7); else setfillstyle(SOLID_FILL,2);
     floodfill(570+11,10+20+(count*40),0);
    }
    if(status.drs_type[count]=='U')
    {
     if(val==0) setfillstyle(SOLID_FILL,7); else setfillstyle(SOLID_FILL,4);
     floodfill(570+45,10+8+(count*40),0);
    }
   }
   count++;
  }
  mouse(1);
 }
 if(mandir!=5)
 {
  mancount++;
  if(mancount==3)
  {
   mancount=0;
   num=status.active_window;
   for(n=0;n<=num;n++)
   {
    if((manx>wi[num].x1) && (manx<wi[num].x2))
    {
     if((many>wi[num].y1) && (many<wi[num].y2))
      mansotto=1;
      else
      mansotto=0;
    }
    else mansotto=0;
   }
   mouse(2);
   if(mandir==0)
   {
    if(mansotto==1) manx-=2; else
    if(manx>5){
    putimage(manx,many,mansfo,COPY_PUT);
    manx-=2;
    getimage(manx,many,manx+9,many+13,mansfo);
    if(manspr==0) {putimage(manx,many,mansx1,COPY_PUT);manspr++;}
    else
    if(manspr==1) {putimage(manx,many,mansx2,COPY_PUT);manspr++;}
    else
    if(manspr==2) {putimage(manx,many,mansx3,COPY_PUT);manspr++;}
    else
    if(manspr==3) {putimage(manx,many,mansx2,COPY_PUT);manspr++;}
    else
    if(manspr==4) {putimage(manx,many,mansx1,COPY_PUT);manspr=1;}}
   }
   if(mandir==180)
   {
    if(mansotto==1) manx+=2; else
    if(manx<620){
    putimage(manx,many,mansfo,COPY_PUT);
    manx+=2;
    getimage(manx,many,manx+9,many+13,mansfo);
    if(manspr==0) {putimage(manx,many,mandx1,COPY_PUT);manspr++;}
    else
    if(manspr==1) {putimage(manx,many,mandx2,COPY_PUT);manspr++;}
    else
    if(manspr==2) {putimage(manx,many,mandx3,COPY_PUT);manspr++;}
    else
    if(manspr==3) {putimage(manx,many,mandx2,COPY_PUT);manspr++;}
    else
    if(manspr==4) {putimage(manx,many,mandx1,COPY_PUT);manspr=1;}}

   }
   if(mandir==90)
   {
    if(mansotto==1) many-=2; else
    if(many>5){
    putimage(manx,many,mansfo,COPY_PUT);
    many-=2;
    getimage(manx,many,manx+9,many+13,mansfo);
    if(manspr==0) {putimage(manx,many,mans1,COPY_PUT);manspr++;}
    else
    if(manspr==1) {putimage(manx,many,mans2,COPY_PUT);manspr++;}
    else
    if(manspr==2) {putimage(manx,many,mans3,COPY_PUT);manspr++;}
    else
    if(manspr==3) {putimage(manx,many,mans2,COPY_PUT);manspr++;}
    else
    if(manspr==4) {putimage(manx,many,mans1,COPY_PUT);manspr=1;}}

   }
   if(mandir==270)
   {
    if(mansotto==1) many+=2; else
    if(many<330){
    putimage(manx,many,mansfo,COPY_PUT);
    many+=2;
    getimage(manx,many,manx+9,many+13,mansfo);
    if(manspr==0) {putimage(manx,many,mand1,COPY_PUT);manspr++;}
    else
    if(manspr==1) {putimage(manx,many,mand2,COPY_PUT);manspr++;}
    else
    if(manspr==2) {putimage(manx,many,mand3,COPY_PUT);manspr++;}
    else
    if(manspr==3) {putimage(manx,many,mand2,COPY_PUT);manspr++;}
    else
    if(manspr==4) {putimage(manx,many,mand1,COPY_PUT);manspr=1;}}

   }
   mouse(1);
  }

 }
 enable();
}
void draw_man_front(int x,int y)
{
 setcolor(0);
 circle(x+20,y+20,15);
 setfillstyle(SOLID_FILL,14);
 floodfill(x+20,y+20,0);
 circle(x+15,y+15,2);
 circle(x+28,y+15,2);
}
struct ffblk selp(void)
{
 int kd=0,cdir=0,n,x,primo=0,currp=0,boh=0;
 char num,*sfo;
 mouse(2);
 gwindow(250,130,370,220," Open ",12,1,14,3);
 num=status.active_window;
 x=imagesize(wi[num].x1+5,wi[num].y1+30,wi[num].x1+100,wi[num].y1+90);
 sfo=(char *)malloc(x);
 getimage(wi[num].x1+5,wi[num].y1+30,wi[num].x1+100,wi[num].y1+90,sfo);
 mouse(1);
lab:
 mouse(2);
 x=findfirst("*.*",&f,0x3f);
 while(!x)
 {
  if(f.ff_attrib==0x10) { file[cdir]=f;cdir++;x=findnext(&f);continue;}
  if((f.ff_attrib==0x22) || (f.ff_attrib==0x23)|| (f.ff_attrib==0x27)) { strcpy(f.ff_name,strlwr(f.ff_name));file[cdir]=f;cdir++;x=findnext(&f);continue; }
  strcpy(f.ff_name,strlwr(f.ff_name));file[cdir]=f;
  cdir++;
  x=findnext(&f);
 }
 setcolor(4);
 for(n=0;n<=5;n++)
 {
  if(n==cdir) break;
  moveto(wi[num].x1+5,wi[num].y1+30+(n*10));
  gprintf("%s",file[n].ff_name);
 }
 moveto(wi[num].x1+110,wi[num].y1+30);gprintf("%c",24);
 moveto(wi[num].x1+110,wi[num].y1+80);gprintf("%c",25);
 moveto(wi[num].x1+5,wi[num].y1+30+(currp*10));setcolor(14);gprintf("%s",file[primo+currp].ff_name);setcolor(4);
 line(wi[num].x1+101,wi[num].y1+21,wi[num].x1+101,wi[num].y1+88);
 line(wi[num].x1+101,wi[num].y1+60,wi[num].x1+118,wi[num].y1+60);
 mouse(1);
 while(kd!=27)
 {
  while((kd=ikey())==0) {}
  controlla(kd);
  x=contr_drives();
  if(x!=-1)
  {
   setdisk(x);
   chdir(file[primo+currp].ff_name);
   cdir=0;currp=0;primo=0;boh=0;kd=0;
   mouse(2);putimage(wi[num].x1+5,wi[num].y1+30,sfo,COPY_PUT);mouse(1);
   goto lab;
  }
  if(kd==-1)
  {
   if((k_x>wi[num].x1+101) && (k_x<wi[num].x1+120))
   { if((k_y>wi[num].y1+21) && (k_y<wi[num].y1+60)) kd=UP_KEY;
    if((k_y>wi[num].y1+60) && (k_y<wi[num].y1+90)) kd=DOWN_KEY;}
   if((k_x>wi[num].x1+5) && (k_x<wi[num].x1+100))
    if((k_y>wi[num].y1+30) && (k_y<wi[num].y1+90))
    {
     mouse(2);
     while(r.x.bx!=0) {mouse(3);}
     moveto(wi[num].x1+5,wi[num].y1+30+(currp*10));setcolor(4);gprintf("%s",file[primo+currp].ff_name);setcolor(4);
     boh=currp;
     currp=(k_y-wi[num].y1-30)/10;
     if(boh==currp) kd=13;
     moveto(wi[num].x1+5,wi[num].y1+30+(currp*10));setcolor(14);gprintf("%s",file[primo+currp].ff_name);setcolor(4);
     mouse(1);
     k_x=0;k_y=0;
    }
  }
  if(kd==13)
  {
   if(file[primo+currp].ff_attrib==0x10)
   {
    chdir(file[primo+currp].ff_name);
    cdir=0;currp=0;primo=0;boh=0;kd=0;
    mouse(2);putimage(wi[num].x1+5,wi[num].y1+30,sfo,COPY_PUT);mouse(1);
    goto lab;
   }
   mouse(2);
   free(sfo);
   nogwin();
   mouse(1);
   return(file[primo+currp]);
  }
  if(kd==DOWN_KEY)
  {
   mouse(2);
   if((primo==cdir-6) && (currp==5)){}
   else if(currp==cdir-1) {}
   else {
   if(currp==5)
   {putimage(wi[num].x1+5,wi[num].y1+30,sfo,COPY_PUT); primo++;for(n=primo;n<=primo+5;n++) {moveto(wi[num].x1+5,wi[num].y1+30+((n-primo)*10));gprintf("%s",file[n].ff_name);} moveto(wi[num].x1+5,wi[num].y1+30+(currp*10));setcolor(14);gprintf("%s",file[primo+currp].ff_name);setcolor(4);}
   else{
   moveto(wi[num].x1+5,wi[num].y1+30+(currp*10));setcolor(4);gprintf("%s",file[primo+currp].ff_name);setcolor(4);
   currp++;moveto(wi[num].x1+5,wi[num].y1+30+(currp*10));setcolor(14);gprintf("%s",file[primo+currp].ff_name);setcolor(4);}}
   mouse(1);
  }
  if(kd==UP_KEY)
  {
   mouse(2);
   if((primo==0) && (currp==0)){}
   else{
   if(currp==0)
   {
    putimage(wi[num].x1+5,wi[num].y1+30,sfo,COPY_PUT); primo--;for(n=primo;n<=primo+5;n++) {moveto(wi[num].x1+5,wi[num].y1+30+((n-primo)*10));gprintf("%s",file[n].ff_name);moveto(wi[num].x1+5,wi[num].y1+30+(currp*10));setcolor(14);gprintf("%s",file[primo+currp].ff_name);setcolor(4);}
   }
   else {
   moveto(wi[num].x1+5,wi[num].y1+30+(currp*10));setcolor(4);gprintf("%s",file[primo+currp].ff_name);setcolor(4);
   currp--;moveto(wi[num].x1+5,wi[num].y1+30+(currp*10));setcolor(14);gprintf("%s",file[primo+currp].ff_name);setcolor(4);}}
   mouse(1);
  }
 }
 mouse(2);
 free(sfo);
 nogwin();
 mouse(1);
 k_x=0;k_y=0;
 file[primo+currp].ff_fsize=-1;
 return(file[primo+currp]);
}
void ginput(char *s)
{
 char num,cc=0;
 int kd=0,x;
 while(kd!=27)
 {
  while((kd=ikey())==0) {}
  controlla(kd);
  x=contr_drives();
  if(x!=-1) {setdisk(x);}
  if(kd==27)
  {
   s[0]=-1;break;
  }
  if(kd==-1){}
  else
  {
   if(kd==13) {s[cc]=0;kd=27;}else{
   mouse(2);
   gprintf("%c",kd);
   s[cc]=kd;cc++;mouse(1);
   }
  }
 }
 kd=0;
}
