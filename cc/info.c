#include<iaza.h>
union REGS r;
double tota,lib;
struct SREGS sr;
struct dfree df;
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
}far *s0;
unsigned int i60seg;
unsigned int i60off;
unsigned int i61seg;
unsigned int i61off;
char bugg[512];
int driveinfo,biosdrive,n;
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

main(argc,argv)
int argc;
char *argv[];
{
 i60off=peek(0,0x60*4);
 i60seg=peek(0,0x60*4+2);
 poke(0,0x60*4,peek(0,0x21*4));
 poke(0,0x60*4+2,peek(0,0x21*4+2));
 i61off=peek(0,0x61*4);
 i61seg=peek(0,0x61*4+2);
 poke(0,0x61*4,peek(0,0x13*4));
 poke(0,0x61*4+2,peek(0,0x13*4+2));
 if(argc==1) driveinfo=getdisk();
 else
 if(argc!=2)
 {
  printf("Errore nei parametri... sintassi : ndi <drive:>\n");
  exit(1);
 }
 else
 {
  strupr(argv[1]);
  driveinfo=argv[1][0]-'A';
 }
 driveinfo++;
 r.h.ah=0x32;
 r.x.dx=driveinfo;
 int86x(0x60,&r,&r,&sr);
 if(r.h.al!=0) {printf("Drive non valido\n");exit(1);}
 s0=MK_FP(sr.ds,r.x.bx);
 for(n=0;n<=79;n++) printf("-");
 printf("Drive...................%c:\n",driveinfo-1+'A');
 if(s0->drive!=s0->unit)
 printf("Drive Type..............Device Driven \n");
 else if(s0->media_byte==0xf8)
 printf("Drive Type..............Hard Disk\n");
 else
 {
  r.h.ah=8;
  r.h.dl=driveinfo-1;
  int86(0x61,&r,&r);
  if((r.h.bl==1) || (r.h.bl==2))
  printf("Drive Type..............5¬\"\n");
  if((r.h.bl==3) || (r.h.bl==4))
  printf("Drive Type..............3«\"\n");
 }
 if(s0->cluster_num>4080)
 printf("FAT type................16-bit\n");
 else
 printf("FAT type................12-bit\n");
 n=absread(driveinfo-1,1,0,bugg);
 if(n==0)
 {
 printf("Signature...............");{
  for(n=3;n<=11;n++) putch(bugg[n]);
 }
 printf("\n");}
 printf("bytes per sector........%s\n",putnorton(s0->bytexsec));
 printf("sector per cluster......0-%d  [%d sectors]\n",s0->secxclus,s0->secxclus+1);
 printf("Reserved boot sectors...%d\n",s0->boot_sec_num);
 printf("Number of FAT...........%d\n",s0->FAT_num);
 printf("1st FAT.................%d-%d  [%d sectors]\n",s0->boot_sec_num,s0->secxFAT,s0->secxFAT);
 if(s0->FAT_num>1)
 printf("2nd FAT.................%d-%d  [%d sectors]\n",s0->boot_sec_num+s0->secxFAT,s0->secxFAT+s0->secxFAT,s0->secxFAT);
 printf("Root directory entries..%d\n",s0->root_entries_num);
 printf("offset to root..........%d\n",s0->root_off);
 printf("offset to data..........%d\n",s0->data_off);
 printf("Total clusters..........%s\n",putnorton(s0->cluster_num));
 printf("Media...................%X\n",s0->media_byte);
 if(s0->status==0)
 printf("status..................Ok\n");
 else
 printf("status..................Skipped\n");
 getdfree(driveinfo,&df);
 tota=(double)df.df_total*(double)df.df_bsec*(double)df.df_sclus;
 lib=(double)df.df_avail*(double)df.df_bsec*(double)df.df_sclus;
 printf("Total disk space........%s\n",putnorton(tota));
 printf("Free disk space.........%s\n",putnorton(lib));
 for(n=0;n<=79;n++) printf("-");
 printf("\t\tDrive Info v 4.0 ");
 /*p_author();*/
 printf(" 1991(c)\n");
 for(n=0;n<=79;n++) printf("-");
 poke(0,0x61*4,i61off);
 poke(0,0x61*4+2,i61seg);
 poke(0,0x60*4,i60off);
 poke(0,0x60*4+2,i60seg);
}
