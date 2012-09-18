#include<iaza.h>
#define ipoke(n,s,o) poke(0,n*4,0);poke(0,n*4+2,s)
#define ipeek(n,s,o) o=peek(0,n*4);s=peek(0,n*4+2)
typedef  unsigned char byte;
typedef  unsigned int  word;
union REGS r;
byte drive,track,secpertrack,side,curtrack,curside;
byte ses,sbx;
struct DiskParameterTable
{
 byte pspec;
 byte sspec;
 byte motor_off;
 byte bytepersec;
 byte secpertrack;
 byte spaceintertrack;
 byte lunghdati;
 byte sptr;
 byte fillcar;
 byte temp_test;
 byte go_motor;
}dtp;
struct dtp far * dtpp;
struct FormatTable
{
 byte numtrack;
 byte numside;
 byte numsec;
 byte dim;
}*FT;
void setdtp(byte idrive,byte itrack,byte isecpertrack)
{
 byte type;
 if((itrack==0) || (isecpertrack==0)) type =0;else type =1;
 switch(type)
 {
  case 0: r.h.ah=8;
	  r.h.dl=drive;
	  int86(0x13,&r,&r);
	  track=r.h.ch;
	  secpertrack=r.h.cl;
	  side=r.h.dh;
  break;
  case 1: r.h.ah=0x18;
	  r.h.ch=track;
	  r.h.cl=secpertrack;
	  r.h.dl=drive;
	  int86(0x13,&r,&r);
  break;
 }
 dtpp=(struct dtp far *)MK_FP(_ES,r.x.di);
 memcpy(&dtp,dtpp,11);
 FT=(struct FormatTable *)malloc(sizeof(struct FormatTable)*secpertrack);
 ipeek(0x1e,sbx,ses);
 ipoke(0x1e,FP_OFF(&dtp),FP_SEG(&dtp));
}
char format(track,side)
{
 int sect;
 for(sect=0;sect<secpertrack;sect++)
 {
  FT[sect].numtrack=track;
  FT[sect].numside=side;
  FT[sect].numsec=secpertrack+1;
  FT[sect].dim=2;
 }
 _ES=FP_SEG(&dtp);
 r.h.ah=5;
 r.h.ch=track;
 r.h.dh=side;
 r.h.dl=drive;
 r.h.cl=1;
 r.h.al=secpertrack;
 r.x.bx=FP_OFF(&dtp);
 int86(0x13,&r,&r);
 return(0);
}
main(argc,argv)
int argc;
char *argv[];
{
 printf(" Iaza Formetter v 1.00á by Iaza Soft 1991(c)\n");
 if(argv[1]==NULL){printf("Errore nei parametri:sintassi..Format <drive> track nsec\n");exit(1);}
 drive=toupper(argv[1][0])-'A';
 track=(byte)atoi(argv[2]);
 secpertrack=(byte)atoi(argv[3]);
 setdtp(drive,track,secpertrack);
 dtp.fillcar=0;
 for(curtrack=0;curtrack<=track;curtrack++)
 for(curside=0;curside<=side;curside++)
 {
  format(curtrack,curside);
  printf("Formatting Track: %d Side: &d\r",curtrack,curside);
 }
 ipoke(0x1e,sbx,ses);
}
