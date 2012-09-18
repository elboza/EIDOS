#include<iaza.h>
int gd=DETECT,gm;
int x1=30,y1=30,x2=200,y2=100,dir1=0,dir2=0,kd,st;
void chioppo(void)
{
 sound(600);
 delay(400);
 nosound();
 exit(1);
}
int ikey(void)
{
 int cc,ch2;
char he;
char ch;
 if((ch=kbhit())!=0) { ch=bioskey(1); ch2=bioskey(0);
 if(ch==0) return((((ch2-256)/256)+1)+256);
 return(ch);
 }
}

main()
{
 initgraph(&gd,&gm,"c:\\tc\\bgi");
 randomize();
 x1=random(639);
 y1=random(349);
 x2=random(639);
 y2=random(349);
 st=random(3);
 if(st==0) dir1=0;
 if(st==1) dir1=90;
 if(st==2) dir1=180;
 if(st==3) dir1=270;
 st=rand();
 if(st==0) dir2=0;
 if(st==1) dir2=90;
 if(st==2) dir2=180;
 if(st==3) dir2=270;
 while(1)
 {
  if(dir1==0) {x1++;if(x1==640) x1=0;st=getpixel(x1,y1);if(st!=0) chioppo();putpixel(x1,y1,4);}
  if(dir1==90) {y1--;if(y1==0) y1=349;st=getpixel(x1,y1);if(st!=0) chioppo();putpixel(x1,y1,4);}
  if(dir1==180) {x1--;if(x1==0) x1=639;st=getpixel(x1,y1);if(st!=0) chioppo();putpixel(x1,y1,4);}
  if(dir1==270) {y1++;if(y1==349) y1=0;st=getpixel(x1,y1);if(st!=0) chioppo();putpixel(x1,y1,4);}
  if(dir2==0) {x2++;if(x2==640) x2=0;st=getpixel(x2,y2);if(st!=0) chioppo();putpixel(x2,y2,7);}
  if(dir2==90) {y2--;if(y2==0) y2=349;st=getpixel(x2,y2);if(st!=0) chioppo();putpixel(x2,y2,7);}
  if(dir2==180) {x2--;if(x2==0) x2=639;st=getpixel(x2,y2);if(st!=0) chioppo();putpixel(x2,y2,7);}
  if(dir2==270) {y2++;if(y2==349) y2=0;st=getpixel(x2,y2);if(st!=0) chioppo();putpixel(x2,y2,7);}
  delay(5);
  kd=ikey();
  if(kd==27) exit(1);
  if((kd=='a') || (kd=='A')) {dir1+=90;if(dir1==360) dir1=0;}
  if((kd=='d') || (kd=='D')) {dir1-=90;if(dir1==-90) dir1=270;}
  if(kd=='4') {dir2-=90;if(dir2==-90) dir2=270;}
  if(kd=='6') {dir2+=90;if(dir2==360) dir2=0;}
 }
}

