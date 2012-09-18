#include<iazawin2.h>
#include<stdarg.h>
#include<stdio.h>
void inizializza(void)
{
 int n,m;
 for(n=0;n<=6;n++)
 {
  if((getmm[n]=(char *)malloc(80*50*2))==NULL) {printf("Errore di allocazione...\n");exit(1);}
  MP_count[n]=0;
  MS_count[n]=0;
  for(m=0;m<=9;m++) MAP_count[n][m]=0;
 }

}
void vt_p_author(void)
{
 int n=1,cc=0;
 char str[14]="";
 str[0]=0x147;
 str[1]=0x15c;
 str[2]=0x105;
 str[3]=0x16c;
 str[4]=0x144;
 str[5]=0x15f;
 str[6]=0x144;
 str[7]=0x105;
 str[8]=0x176;
 str[9]=0x14a;
 str[10]=0x143;
 str[11]=0x151;
 str[12]=0;
 while(n!=0x125)
 {
  n=str[cc];
  n=n^0x125;
  cc++;
  vt_putch(n);
 }
}
void vt_wind(int x1,int y1,int x2,int y2,char bord,char *s,unsigned char scol,unsigned char bcol,unsigned char riemp,unsigned char rcol,char ombr,char num)
{
 int x,len,sp,m,n,ikx,iky;
 wi[num].omb=ombr;
 vt_color=bcol;
 vt_box(x1,y1,x2,y2,1);
 vt_gotoxy(x1+3,y1);
 vt_putch(7);
 x=(x2+x1)/2;
 len=strlen(s);
 sp=len/2;
 vt_color=scol;
 vt_gotoxy(x-sp,y1);
 vt_puts(s);
 vt_color=rcol;
 vt_gotoxy(x1+1,y1+1);
 for(m=y1+1;m<=y2-1;m++)
 {
  for(n=x1+1;n<=x2-1;n++) vt_putch(riemp);
  ikx=vt_wherex();
  iky=vt_wherey();
  vt_gotoxy(x1+1,iky+1);
 }
 wi[num].x1=x1;wi[num].y1=y1;wi[num].x2=x2;wi[num].y2=y2;
 if(ombr!=0) ombra(num);
 if(num<=M_count-1) make_menu(num);
 vt_gotoxy(wi[num].x1+1,wi[num].y1+2);
}
void make_menu(char num)
{
 int n,xx,m;
 char ss[13];
 mlinex(wi[num].x1+1,wi[num].y1+1,wi[num].x2-wi[num].x1-1,' ');
 hilix(wi[num].x1+1,wi[num].y1+1,wi[num].x2-wi[num].x1-1,n_menu[num].barcol);
 vt_gotoxy(wi[num].x1+3,wi[num].y1+1);
 vt_color=vt_mixcol(n_menu[num].barcol,n_menu[num].scripcol);
 for(n=0;n<=MP_count[num]-1;n++)
 {
  strcpy(ss,n_menu[num].M[n].str);
  xx=strlen(n_menu[num].M[n].str);
  MAP_count[num][n]=xx;
  for(m=0;m<=xx;m++)
  {
   if(m==n_menu[num].M[n].ncar)
   {
    vt_color=vt_mixcol(n_menu[num].barcol,n_menu[num].hilicol);
    vt_putch(ss[m]);
    vt_color=vt_mixcol(n_menu[num].barcol,n_menu[num].scripcol);
   }else{
   vt_putch(ss[m]);}
  }
  vt_x+=2;
 }
}
unsigned char vt_mixcol(char back,char fore)
{
 back=back & 0xf0;
 fore=fore & 0x0f;
 back+=fore;
 return(back);
}
void ombra(char num)
{
 hilix(wi[num].x1+2,wi[num].y2+1,wi[num].x2-wi[num].x1,0x08);
 hilix(wi[num].x1+2,wi[num].y2+2,wi[num].x2-wi[num].x1,0x08);
 hiliy(wi[num].x2+1,wi[num].y1+2,wi[num].y2-wi[num].y1,0x08);
 hiliy(wi[num].x2+2,wi[num].y1+2,wi[num].y2-wi[num].y1+1,0x08);
}
void vt_box(int x1,int y1,int x2,int y2,char m)
{
 int n;
 vt_gotoxy(x1,y1);
 for(n=x1;n<=x2;n++) { if(m==1) vt_putch('Í');else vt_putch('Ä'); }
 vt_gotoxy(x1,y2);
 for(n=x1;n<=x2;n++) { if(m==1) vt_putch('Í'); else vt_putch('Ä');}
 vt_gotoxy(x1,y1);
 for(n=y1;n<y2;n++) { if(m==1) {vt_putch('º');} else{vt_putch('³');}vt_gotoxy(vt_wherex()-1,vt_wherey()+1); }
 vt_gotoxy(x2,y1);
 for(n=y1;n<y2;n++) { if(m==1) {vt_putch('º');} else{vt_putch('³');}vt_gotoxy(vt_wherex()-1,vt_wherey()+1); }
 vt_gotoxy(x1,y1); vt_putch('É');
 vt_gotoxy(x2,y1); vt_putch('»');
 vt_gotoxy(x1,y2); vt_putch('È');
 vt_gotoxy(x2,y2); vt_putch('¼');

}
void movewind(char num)
{
 int offs,x,y;
 char *buff,*elfab;
 int nx,loc,sp1,sp2;
 unsigned int n,m;
 unsigned char xx;
 offs=k_x-wi[num].x1;
 elfab=(char*)malloc((wi[num].x2-wi[num].x1)*2);
 buff=(char*)malloc((((wi[num].x2-wi[num].x1)*(wi[num].y2-wi[num].y1))+4)*2);
 mouse(2);
 nx=0;xx=0;
 for(m=wi[num].y1;m<=wi[num].y2;m++)
  for(n=wi[num].x1;n<=wi[num].x2;n++)
  {
   loc=(m*80+n)*2;
   xx=peekb(0xb800,loc);
   buff[nx]=xx;
   nx++;
   loc=((m*80+n)*2)+1;
   xx=peekb(0xb800,loc);
   buff[nx]=xx;
   nx++;
  }
 sp1=wi[num].x2-wi[num].x1;
 sp2=wi[num].y2-wi[num].y1;
 while(r.x.bx==1){
 mouse(3);
 nx=0;
 for(n=r.x.cx/8-offs;n<=r.x.cx/8-offs+sp1;n++)
 {
  elfab[nx]=peekb(0xb800,(r.x.dx/8*80+n)*2);nx++;
  elfab[nx]=peekb(0xb800,(r.x.dx/8*80+n)*2+1);
  nx++;
 }
 for(n=r.x.cx/8-offs;n<=r.x.cx/8-offs+sp1;n++)
 {
  pokeb(0xb800,(r.x.dx/8*80+n)*2,'Í');
  pokeb(0xb800,(r.x.dx/8*80+n)*2+1,0x71);
 }
 nx=0;
 for(n=r.x.cx/8-offs;n<=r.x.cx/8-offs+sp1;n++)
 {
  pokeb(0xb800,(r.x.dx/8*80+n)*2,elfab[nx]);nx++;
  pokeb(0xb800,(r.x.dx/8*80+n)*2+1,elfab[nx]);nx++;
 }

 }
 x=r.x.cx/8;y=r.x.dx/8;
 putmem(num,wi[num].x1,wi[num].y1,wi[num].x2,wi[num].y2);
 wi[num].x1=x-offs;
 wi[num].y1=y;
 wi[num].x2=wi[num].x1+sp1;
 wi[num].y2=wi[num].y1+sp2;
 getmem(num,wi[num].x1,wi[num].y1,wi[num].x2,wi[num].y2);
 nx=0;xx=0;
 for(m=wi[num].y1;m<=wi[num].y2;m++)
  for(n=wi[num].x1;n<=wi[num].x2;n++)
  {
   loc=(m*80+n)*2;
   xx=buff[nx];
   pokeb(0xb800,loc,xx);
   nx++;
   loc=((m*80+n)*2)+1;
   xx=buff[nx];
   pokeb(0xb800,loc,xx);
   nx++;
  }
 if(wi[num].omb!=0) ombra(num);
 mouse(1);
 free(buff);
 free(elfab);
}

void movewind2(char num)
{
 int offs,x,y,varx1,vary1,varx2,vary2;
 char elfabx1[80*2],elfabx2[80*2],elfaby1[80*2],elfaby2[80*2];
 int nx,loc,sp1,sp2;
 unsigned int n,m;
 unsigned char xx;
 offs=k_x-wi[num].x1;
 mouse(2);
 nx=0;xx=0;
 for(m=wi[num].y1;m<=wi[num].y2;m++)
  for(n=wi[num].x1;n<=wi[num].x2;n++)
  {
   loc=(m*80+n)*2;
   xx=peekb(0xb800,loc);
   getmm[6][nx]=xx;
   nx++;
   loc=((m*80+n)*2)+1;
   xx=peekb(0xb800,loc);
   getmm[6][nx]=xx;
   nx++;
  }
 sp1=wi[num].x2-wi[num].x1;
 sp2=wi[num].y2-wi[num].y1;
 xx=getrow();
 n=79-(wi[num].x2-wi[num].x1)+offs;
 if(wi[num].omb==1) n-=2;
 setmwin(offs,0,n,xx-(wi[num].y2-wi[num].y1));
 varx1=k_x;
 varx2=varx1;
 vary1=k_y;
 vary2=vary1;
   nx=0;
  for(n=k_x-offs;n<=k_x-offs+sp1;n++)
  {
   elfabx1[nx]=peekb(0xb800,(k_y*80+n)*2);nx++;
   elfabx1[nx]=peekb(0xb800,((k_y*80+n)*2)+1);
   nx++;
  }
  nx=0;
  for(n=k_x-offs;n<=k_x-offs+sp1;n++)
  {
   elfabx2[nx]=peekb(0xb800,((k_y+sp2)*80+n)*2);nx++;
   elfabx2[nx]=peekb(0xb800,(((k_y+sp2)*80+n)*2)+1);
   nx++;
  }
  nx=0;
  for(n=k_y;n<=k_y+sp2;n++)
  {
   elfaby1[nx]=peekb(0xb800,(n*80+(k_x-offs))*2);nx++;
   elfaby1[nx]=peekb(0xb800,((n*80+(k_x-offs))*2)+1);nx++;
  }
  nx=0;
  for(n=k_y;n<=k_y+sp2;n++)
  {
   elfaby2[nx]=peekb(0xb800,(n*80+(k_x-offs+sp1))*2);nx++;
   elfaby2[nx]=peekb(0xb800,((n*80+(k_x-offs+sp1))*2)+1);nx++;
  }

  mlinex(k_x-offs,k_y,sp1,'Í');
  mlinex(k_x-offs,k_y+sp2,sp1,'Í');
  mliney(k_x-offs,k_y,sp2,'º');
  mliney(k_x-offs+sp1,k_y,sp2,'º');
  vt_putchat(k_x-offs,k_y,'É');
  vt_putchat(k_x-offs+sp1,k_y,'»');
  vt_putchat(k_x-offs,k_y+sp2,'È');
  vt_putchat(k_x-offs+sp1,k_y+sp2,'¼');
  hilix(k_x-offs,k_y,sp1,0x71);
  hilix(k_x-offs,k_y+sp2,sp1,0x71);
  hiliy(k_x-offs,k_y,sp2,0x71);
  hiliy(k_x-offs+sp1,k_y,sp2,0x71);
 while(r.x.bx==1){
 if((varx2!=varx1) || (vary2!=vary1))
 {
  nx=0;
  for(n=varx2-offs;n<=varx2-offs+sp1;n++)
  {
   pokeb(0xb800,(vary2*80+n)*2,elfabx1[nx]);nx++;
   pokeb(0xb800,((vary2*80+n)*2)+1,elfabx1[nx]);
   nx++;
  }
  nx=0;
  for(n=varx2-offs;n<=varx2-offs+sp1;n++)
  {
   pokeb(0xb800,((vary2+sp2)*80+n)*2,elfabx2[nx]);nx++;
   pokeb(0xb800,(((vary2+sp2)*80+n)*2)+1,elfabx2[nx]);
   nx++;
  }
  nx=0;
  for(n=vary2;n<=vary2+sp2;n++)
  {
   pokeb(0xb800,(n*80+(varx2-offs))*2,elfaby1[nx]);nx++;
   pokeb(0xb800,((n*80+(varx2-offs))*2)+1,elfaby1[nx]);nx++;
  }
  nx=0;
  for(n=vary2;n<=vary2+sp2;n++)
  {
   pokeb(0xb800,(n*80+(varx2-offs+sp1))*2,elfaby2[nx]);nx++;
   pokeb(0xb800,((n*80+(varx2-offs+sp1))*2)+1,elfaby2[nx]);nx++;
  }

  nx=0;
  for(n=r.x.cx/8-offs;n<=r.x.cx/8-offs+sp1;n++)
  {
   elfabx1[nx]=peekb(0xb800,(r.x.dx/8*80+n)*2);nx++;
   elfabx1[nx]=peekb(0xb800,((r.x.dx/8*80+n)*2)+1);
   nx++;
  }
  nx=0;
  for(n=r.x.cx/8-offs;n<=r.x.cx/8-offs+sp1;n++)
  {
   elfabx2[nx]=peekb(0xb800,(((r.x.dx/8)+sp2)*80+n)*2);nx++;
   elfabx2[nx]=peekb(0xb800,((((r.x.dx/8)+sp2)*80+n)*2)+1);
   nx++;
  }
  nx=0;
  for(n=r.x.dx/8;n<=r.x.dx/8+sp2;n++)
  {
   elfaby1[nx]=peekb(0xb800,(n*80+(r.x.cx/8-offs))*2);nx++;
   elfaby1[nx]=peekb(0xb800,((n*80+(r.x.cx/8-offs))*2)+1);nx++;
  }
  nx=0;
  for(n=r.x.dx/8;n<=r.x.dx/8+sp2;n++)
  {
   elfaby2[nx]=peekb(0xb800,(n*80+(r.x.cx/8-offs+sp1))*2);nx++;
   elfaby2[nx]=peekb(0xb800,((n*80+(r.x.cx/8-offs+sp1))*2)+1);nx++;
  }
  mlinex(r.x.cx/8-offs,r.x.dx/8,sp1,'Í');
  mlinex(r.x.cx/8-offs,r.x.dx/8+sp2,sp1,'Í');
  mliney(r.x.cx/8-offs,r.x.dx/8,sp2,'º');
  mliney(r.x.cx/8-offs+sp1,r.x.dx/8,sp2,'º');
  varx2=varx1;
  vary2=vary1;
  vt_putchat(varx1-offs,vary1,'É');
  vt_putchat(varx1-offs+sp1,vary1,'»');
  vt_putchat(varx1-offs,vary1+sp2,'È');
  hilix(r.x.cx/8-offs,r.x.dx/8,sp1,0x71);
  hilix(r.x.cx/8-offs,r.x.dx/8+sp2,sp1,0x71);
  hiliy(r.x.cx/8-offs,r.x.dx/8,sp2,0x71);
  hiliy(r.x.cx/8-offs+sp1,r.x.dx/8,sp2,0x71);
 }
 mouse(3);
 varx1=r.x.cx/8;
 vary1=r.x.dx/8;
 }
 x=r.x.cx/8;y=r.x.dx/8;
  nx=0;
  for(n=varx2-offs;n<=varx2-offs+sp1;n++)
  {
   pokeb(0xb800,(vary2*80+n)*2,elfabx1[nx]);nx++;
   pokeb(0xb800,((vary2*80+n)*2)+1,elfabx1[nx]);
   nx++;
  }
  nx=0;
  for(n=varx2-offs;n<=varx2-offs+sp1;n++)
  {
   pokeb(0xb800,((vary2+sp2)*80+n)*2,elfabx2[nx]);nx++;
   pokeb(0xb800,(((vary2+sp2)*80+n)*2)+1,elfabx2[nx]);
   nx++;
  }
  nx=0;
  for(n=vary2;n<=vary2+sp2;n++)
  {
   pokeb(0xb800,(n*80+(varx2-offs))*2,elfaby1[nx]);nx++;
   pokeb(0xb800,((n*80+(varx2-offs))*2)+1,elfaby1[nx]);nx++;
  }
  nx=0;
  for(n=vary2;n<=vary2+sp2;n++)
  {
   pokeb(0xb800,(n*80+(varx2-offs+sp1))*2,elfaby2[nx]);nx++;
   pokeb(0xb800,((n*80+(varx2-offs+sp1))*2)+1,elfaby2[nx]);nx++;
  }

 putmem(num,wi[num].x1,wi[num].y1,wi[num].x2,wi[num].y2);
 wi[num].x1=x-offs;
 wi[num].y1=y;
 wi[num].x2=wi[num].x1+sp1;
 wi[num].y2=wi[num].y1+sp2;
 getmem(num,wi[num].x1,wi[num].y1,wi[num].x2,wi[num].y2);
 nx=0;xx=0;
 for(m=wi[num].y1;m<=wi[num].y2;m++)
  for(n=wi[num].x1;n<=wi[num].x2;n++)
  {
   loc=(m*80+n)*2;
   xx=getmm[6][nx];
   pokeb(0xb800,loc,xx);
   nx++;
   loc=((m*80+n)*2)+1;
   xx=getmm[6][nx];
   pokeb(0xb800,loc,xx);
   nx++;
  }
 if(wi[num].omb!=0) ombra(num);
 xx=getrow();
 setmwin(0,0,79,xx);
 mouse(1);
}

int mouse(int ax)
{
 r.x.ax=ax;
 int86(0x33,&r,&r);
 return(0);
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
  if(r.x.bx==1) {ch2=0;k_x=r.x.cx/8;k_y=r.x.dx/8;return(-1);}
  if(r.x.bx==2) {ch2=0;k_x=r.x.cx/8;k_y=r.x.dx/8;return(-2);}
}
int vt_wherey(void)
{
 return(vt_y);
}
int vt_wherex(void)
{
 return(vt_x);
}
void vt_gotoxy(int x,int y)
{
 vt_x=x;
 vt_y=y;
}

void vt_putch(char hy)
{
  int lx,ly,loc;
  loc=(vt_y*80+vt_x)*2;
  pokeb(0xb800,loc,hy);
  loc++;
  pokeb(0xb800,loc,vt_color);
  vt_x++;
  if(vt_x==80) {vt_x=0;vt_y++;}
}
char vt_getchar(void)
{
 int loc;
 char xx;
 loc=(vt_y*80+vt_x)*2;
 xx=peekb(0xb800,loc);
 return(xx);
}
void vt_font8x8(void)
{
 r.h.ah=0x11;
 r.h.al=0x12;
 r.h.bl=0;
 int86(0x10,&r,&r);
}
void vt_fontn(void)
{
 r.h.ah=0x11;
 r.h.al=0x11;
 r.h.bl=0;
 int86(0x10,&r,&r);
}
void vt_cls(int x1,int y1,int x2,int y2)
{
 r.h.ah=0x6;
 r.h.al=0;
 r.h.bh=vt_color;
 r.h.ch=x1;
 r.h.cl=y1;
 r.h.dh=x2;
 r.h.dl=y2;
 int86(0x10,&r,&r);
}
char vt_getatt(void)
{
 int loc;
 char xx;
 loc=((vt_y*80+vt_x)*2)+1;
 xx=peekb(0xb800,loc);
 return(xx);
}
void vt_dos_putch(char cc)
{
 r.h.ah=2;
 r.h.dl=cc;
 int86(0x21,&r,&r);
}
void vt_setmode(char nn)
{
 r.h.ah=0;
 r.h.al=nn;
 int86(0x10,&r,&r);
}
void vt_puts(char *ss)
{
 int x,n;
 x=strlen(ss);
 for(n=0;n<x;n++) vt_putch(ss[n]);
}
void vt_printf(char *fmt,...)
{
 int len;
 char str[160];
 va_list argptr;
 va_start(argptr,fmt);
 len=vsprintf(str,fmt,argptr);
 va_end(argptr);
 vt_puts(str);
}
void getmem(char num,int x1,int y1,int x2,int y2)
{
 int nx,n,m,loc;
 unsigned char xx;
 nx=0;xx=0;
 for(m=y1;m<=y2+2;m++)
  for(n=x1;n<=x2+2;n++)
  {
   loc=(m*80+n)*2;
   xx=peekb(0xb800,loc);
   getmm[num][nx]=xx;
   nx++;
   loc=((m*80+n)*2)+1;
   xx=peekb(0xb800,loc);
   getmm[num][nx]=xx;
   nx++;
  }
}
void putmem(char num,int x1,int y1,int x2,int y2)
{
 int nx,n,m,loc;
 unsigned char xx;
 nx=0;xx=0;
 for(m=y1;m<=y2+2;m++)
  for(n=x1;n<=x2+2;n++)
  {
   loc=(m*80+n)*2;
   xx=getmm[num][nx];
   pokeb(0xb800,loc,xx);
   nx++;
   loc=((m*80+n)*2)+1;
   xx=getmm[num][nx];
   pokeb(0xb800,loc,xx);
   nx++;
  }
}
void hilix(int x1,int y,int sp,unsigned char c)
{
 int loc,n,count=0;
 loc=((y*80+x1)*2)+1;
 while(count!=sp)
 {
  pokeb(0xb800,loc,c);
  loc+=2;
  count++;
 }

}
void hiliy(int x1,int y1,int sp,unsigned char c)
{
 unsigned int loc,n,count=0;
 while(count!=sp)
 {
  loc=(((y1*80+x1)*2)+1);
  pokeb(0xb800,loc,c);
  y1++;
  count++;
 }
}

void mlinex(int x1,int y,int sp,unsigned char type)
{
 int loc,n=0,n2=0;
 loc=(y*80+x1)*2;
 while(n!=sp)
 {
  pokeb(0xb800,loc+n2,type);
  n2+=2;
  n++;
 }
}
void mliney(int x1,int y1,int sp,unsigned char type)
{
 int loc,n=0,n2=0;
 while(n!=sp)
 {
  loc=(y1*80+x1)*2;
  pokeb(0xb800,loc+n2,type);
  y1++;
  n++;
 }
}
void setmwin(int x1,int y1,int x2,int y2)
{
 r.x.cx=x1*8;
 r.x.dx=x2*8;
 mouse(7);
 r.x.cx=y1*8;
 r.x.dx=y2*8;
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
void cmenu(int x1,int y1,char *s,char scol,char bcol)
{
 int x,n;
 vt_gotoxy(x1,y1);
 vt_color=scol;
 vt_puts(s);
 vt_color=bcol;
 vt_color=vt_color & 0xf0;;
 vt_color+=8;
 vt_putch('Ü');
 vt_gotoxy(x1+1,y1+1);
 x=strlen(s);
 for(n=0;n<x;n++)
 {
  vt_gotoxy(x1+1+n,y1+1);
  vt_putch('ß');
 }
}
void vt_putchat(int x,int y,char car)
{
 vt_gotoxy(x,y);
 vt_putch(car);
}
void menutype(char num,char barcol,char scripcol,char hilicol,char selcol)
{
 n_menu[num].barcol=barcol;
 n_menu[num].scripcol=scripcol;
 n_menu[num].hilicol=hilicol;
 n_menu[num].selcol=selcol;
 M_count++;
}
void setmenuP(char num,char *item,int lett,int (*p)())
{
 n_menu[num].M[MP_count[num]].ncar=lett;
 strcpy(n_menu[num].M[MP_count[num]].str,item);
 n_menu[num].M[MP_count[num]].x=p;
 MP_count[num]++;
}
process(int(*p)())
{
 (*p)();
 return(0);
}
int menuto(char num,char mode)
{
 int vx,vy,n,off=2,x;
 vx=vt_wherex();
 vy=vt_wherey();
 vt_gotoxy(wi[num].x1+3,wi[num].y1+1);
 if(mode==1)
 {
  for(n=0;n<=MP_count[num];n++)
  {
   x=strlen(n_menu[num].M[n].str)+1;
   if((k_x>wi[num].x1+off) &&  (k_x<wi[num].x1+off+x)) {process(n_menu[num].M[n].x);break;}
   off+=x;
   off+=2;
  }
 }
 if(mode==2)
 {

 }
}
void setmenuS(char num,char num2,char *s,int ncar,int (*p)())
{
 n_menu[num].M[MP_count[num2]].m[MAP_count[num][num2]].ncar=ncar;
 strcpy(n_menu[num].M[MP_count[num2]].m[MAP_count[num][num2]].str,s);
 n_menu[num].M[MP_count[num2]].m[MAP_count[num][num2]].x=p;
 MAP_count[num][num2]++;
}
int menusec(char num,char num2,char mode)
{
 int n;
 num=0;num2=0;
 vt_wind(k_x-5,k_y,k_x-5+13,k_y+MAP_count[num][num2],1,n_menu[num].M[num2].str,0x12,0x34,' ',0x05,1,5);
}
