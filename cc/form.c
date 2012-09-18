#include<iaza.h>
#define ipoke(n,s,o) poke(0,n*4,0);poke(0,n*4+2,s)
#define ipeek(n,s,o) o=peek(0,n*4);s=peek(0,n*4+2)

typedef  unsigned char byte;
typedef  unsigned int  word;
word ses,sbx;

struct FormatTable
{ byte track;
  byte side;
  byte sect;
  byte dim;
} *FP;


struct ContParam
{
 struct
  {
   word step_rate:4;
   word unload   :4;
   word load     :7;
   word dma      :1;
  } pr;
  byte delay;
  byte nsbyte;
  byte nsect;
  byte ds;
  byte ndati;
  byte dls;
  byte sfill;
  byte tpostest;
  byte tmotstart;
} C;


int D,N,T,P;
void    init(void);
void    ol_table(void);
int     format(int track,int side);
void    setdtab(void);
void    resetdtab(void);
void    disktable(void);
void    diskreset(void);


void    main(int argc,char *argv[])
{
 printf("Formatter Version 1.0á by Iaza Soft 1991 (c)\n");
 if (argc<2)  D=getdisk();
 else if (argc==2) D=toupper(argv[1][0])-'A';
 else if (argc==4)
 {
  sscanf(argv[2],"%d",&T);
  sscanf(argv[3],"%d",&N);
  P=1;
 }
 FP=(struct FormatTable *) calloc(sizeof(struct FormatTable),N+1);
 disktable();
 init();
}
/*
void    write_sector(int numsect)
{
 segregs.ds = FP_SEG(sct);
 inregs.x.bx= FP_OFF(sct);
 inregs.x.cx= 0x01;
 inregs.x.dx= numsect;
 inregs.h.al= drive;
 int86x(0x26,&inregs,&outregs,&segregs);
 status=outregs.x.cflag;
}

void    clrsector(void)
{
 register key;
 for(key=0;key!=512;key++)
 sector[key] = 0;
}
void    setupboot(void)
{
 register        key;
 clrsector();
 strcpy(bootmsg,"\007\n\rNo boot disk.\n\nReplace and press any key ....\n\n");
 for(key = 0;key != strlen(bootmsg)+1;key++)
 sector[0x80+key] = bootmsg[key];
 sector[0] = 0xEB;
 sector[1] = 0x29;
 strcpy(bootmsg,"FASTFORMAT 2.0");
 for(key = 0;key != strlen(bootmsg)+1;key++)
 sector[0x03+key] = bootmsg[key];
 sector[11] = 0x00;
 sector[12] = 0x02;
 sector[13] = 0x02;
 sector[14] = 0x01;
 sector[15] = 0x00;
 sector[16] = 0x02;
 sector[17] = 0x70;
 sector[18] = 0x00;
 sector[19] = 0xD0;
 sector[20] = 0x02;
 sector[21] = 0xFD;
 sector[22] = 0x02;
 sector[23] = 0x00;
 sector[24] = 0x09;
 sector[25] = 0x00;
 sector[26] = 0x02;
 sector[27] = 0x00;
 sector[28] = 0x00;
 sector[29] = 0x00;
 sector[43] = 0xFA;
 sector[44] = 0x33;
 sector[45] = 0xC0;
 sector[46] = 0x8E;
 sector[47] = 0xD0;
 sector[48] = 0xBC;
 sector[49] = 0x00;
 sector[50] = 0x7C;
 sector[51] = 0x16;
 sector[52] = 0x1F;
 sector[53] = 0xBE;
 sector[54] = 0x80;
 sector[55] = 0x7C;
 sector[56] = 0xAC;
 sector[57] = 0x0A;
 sector[58] = 0xC0;
 sector[59] = 0x74;
 sector[60] = 0x09;
 sector[61] = 0xB4;
 sector[62] = 0x0E;
 sector[63] = 0xBB;
 sector[64] = 0x07;
 sector[65] = 0x00;
 sector[66] = 0xCD;
 sector[67] = 0x10;
 sector[68] = 0xEB;
 sector[69] = 0xF2;
 sector[70] = 0x32;
 sector[71] = 0xE4;
 sector[72] = 0xCD;
 sector[73] = 0x16;
 sector[74] = 0xCD;
 sector[75] = 0x19;
 sector[510]= 0x55;
 sector[511]= 0xAA;
 write_sector(0);
}
void    setupfat(void)
{
 clrsector();
 sector[0] = 0xFD;
 sector[1] = 0xFF;
 sector[2] = 0xFF;
 write_sector(1);
 write_sector(3);
}
void    writesysblock(void)
{
 setupfat();
 if(status==0)
 setupboot();
}
*/
void mk_table(int track,int side)
{
 register sect;
 for(sect=0;sect<N;sect++)
 {
  FP[sect].track=track;
  FP[sect].side =side;
  FP[sect].sect =sect+1;
  FP[sect].dim  =0x02;
 }
}
void    init(void)
{
 register track, side;
 diskreset();
 setdtab();
 for(track=0;track<=T;track++)
  for(side=0;side<2;side++)
  {
   printf("Track :%02d Head:%1d\r",track,side);
   mk_table(track,side);
   if (format(track,side)) printf("Error Track %02d",track);
/*
   if (track==0)
   {
    writesysblock();
    if(status==1) {
    puts("\n\nUnable to write boot");
    resetdtab();
    abort();
   }
*/
  }
 }
/*
void resetdtab()
{
 printf("\n<FORMAT COMPLETE>");
}
*/
void disktable(void)
{
 struct ContParam far *p;
 if (P)
 {
  _AH=0x18;
  _CH=T;
  _CL=N;
 }
 else _AH=0x8;

 _DL=D;
 __int__(0x13);
 N=_CL;
 T=_CH;
 p=(struct ContParam far *)MK_FP(_ES,_DI);
 memcpy(&C,p,11);
 C.sfill=0;
}
int format(int track,int side)
{
 int retry=3;
 int st;
 do
 {
  int f;
  _AH=0x05;
  _DL=D;
  _DH=side;
  _CH=track;
  _CL=0x01;
  _AL=N;
  _ES=FP_SEG(FP);
  _BX=FP_OFF(FP);
  __int__(0x13);
  f=_FLAGS;
  if (f&0x01)
  {
   st=1;
   diskreset();
   retry--;
  }
  else  {retry = 0;st=0;}
 }
 while(retry != 0);
 return st;
}
void setdtab(void)
{
 ipeek(0x1E,ses,sbx);
 ipoke(0x1E,FP_OFF(&C),FP_SEG(&C));
}
void resetdtab(void)
{
 ipoke(0x1E,ses,sbx);
}
void diskreset()
{
 _AH=0;
 __int__(0x13);
}
