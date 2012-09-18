#include <dos.h>
#include <key0.c>
#include <stdio.h>
#include <dir.h>
#include <vtext0.c>
#include <string.h>
#include <ctype.h>
#include <conio.h>
struct ffblk f[7];
int da,yy=2;
int ys[7];
int n[7]={0,0,0,0,0,0,0};
char lxp[7];
char videomem[100][81];
char far *sdta[7];
char ipd[30];
char ipa[30];
void viewtree(void)
{int p=0,j,i;
 int fatto=0;
 int cc;
 textmode(3);
 window(1,1,80,25);
 clrscr();
 if (yy>23){
 do{
 clrscr();
 for (j=1+p*20;j<p*20+25;j++) for (i=1;i<81;i++) wc(i,j-p*20,videomem[j][i]);
 cc=getkey();
 switch (cc)
 { case PGUPKEY : if (p>0) p--;break;
   case PGDNKEY : if ((p+1<5)&&(p+1<((int)(yy/20)))) p++;break;
   case ESC     : fatto=1;break;
  }
 }
  while(fatto==0);
}
else
for (j=1;j<=yy;j++) for (i=1;i<81;i++) wc(i,j,videomem[j][i]);
  }


void tline(int lv,int yup,int ydn)
{ int x,i;
  unsigned char c;
  x=lxp[lv];
  c=videomem[yup][x];
  if (c==0xC4) videomem[yup][x]=0xC2;
  else if (c==0xC0) videomem[yup][x]=0xC3;
  for (i=yup+1;i<ydn;i++) videomem[i][x]=0xB3;
  videomem[ydn][x]=0xC0;
}
void tree(char *path,int level)
{int done;
 int ln,i;
 chdir(path);
 ys[level]=yy;
 n[level]=0;
 sdta[level]=getdta();
 done=findfirst("*.*",&f[level],0x10);
 while (!done)
 {if( (f[level].ff_attrib==16)&&
  (strcmp(f[level].ff_name,".")!=0)&&
  (strcmp(f[level].ff_name,"..")!=0))
      {if (n[level]==0) { if (level==1) {sprintf(&videomem[2][lxp[level]-1],"ÄÄÄ%s",f[level].ff_name);}
			  else {ln=strlen(f[level-1].ff_name);
			   for (i=0;i<8-ln+2;i++) sprintf(&videomem[yy][lxp[level]+ln-8+i],"Ä");
			   sprintf(&videomem[yy][lxp[level]+ln-8+i],"%s",f[level].ff_name);}
			}
	  else          { yy++;tline(level,ys[level+1],yy);
			  sprintf(&videomem[yy][lxp[level]+1],"Ä%s",f[level].ff_name);}
	  tree(f[level].ff_name,level+1);n[level]++;
	  }
  done=findnext(&f[level]);
 }
 setdta(sdta[level-1]);chdir("..");

}

main(argc,argv)
int argc;
char *argv[];
{
 int lni,i,d;
 da=getdisk();
 clrscr();
 getcwd(ipd,30);
 if (argc==1) getcwd(ipa,30);
 if (argc==2) {strcpy(ipa,argv[1]);d=toupper(*argv[1])-65;}
 strcpy(ipa,strupr(ipa));
 sprintf(&videomem[1][1],"ICD Iaza Change Directory by Iaza Soft 1990(c).\n\r");
 sprintf(&videomem[2][1],"%s",ipa);
 lni=strlen(ipa);
 lxp[0]=1;
 lxp[1]=lni+2;
 for (i=2;i<=7;i++) lxp[i]=lxp[i-1]+10;
 strcpy(f[0].ff_name,ipa);
 setdisk(d);
 tree(ipa,1);
 viewtree();
 setdisk(da);
 chdir(ipd);

}

