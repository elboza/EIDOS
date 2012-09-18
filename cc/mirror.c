#include<iaza.h>
#include<rft.c>
unsigned char x,uno,due;
unsigned int l1;
int d,ff;
char *iaza,*oo;
FILE *fp;
void norm(void)
{
 unsigned int n;
 for(n=0;n<=x*512;n++) putc(oo[n],fp);
}
void enhanced(void)
{
 double n;
 for(n=(double)0;n<=(double)x*(double)512;n++) putc(oo[n],fp);
}
main(argc,argv)
int argc;
char *argv[];
{
 if(argc>2) { printf("ERRORE!!! di sintassi: ndi <drive>.\n"); exit(1); }
 if(strcmp(strlwr(argv[1]),"a:")==0) d=0;
 if(strcmp(strlwr(argv[1]),"b:")==0) d=1;
 if(strcmp(strlwr(argv[1]),"c:")==0) d=2;
 if(strcmp(strlwr(argv[1]),"d:")==0) d=3;
 if(strcmp(strlwr(argv[1]),"e:")==0) d=4;
 if(strcmp(argv[1],NULL)==0) d=getdisk();

 boot(d);
 x=data_off;
 printf("%d\n",x);
 oo=(char*)malloc(512*x);
 absread(d,x,0,oo);
 fp=fopen("mirror","w");
 if(fp==NULL) {printf("Errore nella creazione del file..\n");exit(1);}
 if(x<=115) norm();
 else enhanced();
 ff=fclose(fp);
}
