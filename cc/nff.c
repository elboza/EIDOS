#include<iaza.h>
char targ[15],ssdf[15];
int dr;
char ndr[3],nname[15],next[4],ndir[80],cdir[80],hh[80],ssiizzee[10];
struct ffblk fil,f[10];
int ff(char num,char path[80])
{
 int x;
 static int kf=0;
 chdir(path);
 x=findfirst(targ,&fil,0x3f);
 while(!x)
 {
  getcurdir(0,hh);
  printf("%s\\%s",ndr,hh);gotoxy(40,wherey());
  if(fil.ff_attrib==0x10) printf("%s",fil.ff_name);
  else printf("%s",strlwr(fil.ff_name));
  gotoxy(55,wherey());
  printf("%9.0ld ",fil.ff_fsize);
  gotoxy(64,wherey());
  printf(" bytes\n");
  kf++;
  x=findnext(&fil);
 }
 x=findfirst("*.*",&f[num],0x10);
 while(!x)
 {
  if(strcmp(f[num].ff_name,".")==0) {x=findnext(&f[num]);continue;}
  if(strcmp(f[num].ff_name,"..")==0) {x=findnext(&f[num]);continue;}
  if(f[num].ff_attrib!=0x10) {x=findnext(&f[num]);continue;}
  ff(num+1,f[num].ff_name);
  x=findnext(&f[num]);
 }
 chdir("..");
 return(kf);
}
main(argc,argv)
int argc;
char *argv[];
{
 int sdf;
 if(argc!=2) {printf(" Errore di parametri. Sintassi corretta: NFF <drive:>name\n");exit(1);}
 printf("NFF v 3.5 Find File by Iaza Soft 1990(c).\n");
 dr=getdisk();
 strcpy(targ,argv[1]);
 fnsplit(targ,ndr,ndir,nname,next);
 if(strcmp(next,"")==0) strcat(targ,".*");
 if(strcmp(ndr,"")==0) {ndr[0]=(char)dr+65;ndr[1]=':';}
 setdisk((toupper(ndr[0])-'A'));
 getcurdir(0,cdir);
 sdf=ff(0,"\\");
 printf("%ld files trovati.\n",sdf);
 chdir(cdir);
 setdisk(dr);
}
