#include<iaza.h>
struct dfree dfr;
char *iaza,w[10],lati,unit[8];
unsigned char x,uno,due,dr,tralat,settra,unit1;
int d,n,ok;
unsigned int l1,l,l3;
unsigned int s;
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
 printf("	Drive info  %s\n",strupr(argv[1]));
 printf("--------------------------------------------------------\n");
 iaza=(char*)malloc(512);
 ok=absread(d,1,0,iaza);
 if(ok!=0) { printf("errore di lettura.\n"); exit(1); }
 getdfree(d+1,&dfr);
 for(n=3;n<=10;n++) w[n-3]=iaza[n];
 printf("System id              : %s\n",w);
 x=iaza[21];
 printf("Byte id                : %X\n",x);
 printf("Drive Number           : %d\n",d);
 printf("Bytes per sector       : %u\n",iaza[12]*256+iaza[11]);
 printf("Sector per cluster     : %d\n",iaza[13]);
 printf("Numbers of FAT         : %d\n",iaza[16]);
 uno=iaza[18];
 due=iaza[17];
 l1=uno*256+due;
 printf("Root Directory entries : %d\n",l1);
 printf("Sectors per FAT        : %d\n",iaza[23]*256+iaza[22]);
 uno=iaza[19];
 due=iaza[20];
 l=due*256+uno;
 printf("Number of sectors      : %u\n",l);
 printf("offset to FAT          : %d\n",iaza[15]*256+iaza[14]);
 printf("sectors per track      : %d\n",iaza[24]);
 printf("sides                  : %d\n",iaza[26]);
 printf("Hidden sectors         : %d\n",iaza[28]);
 printf("offset to directory    : %d\n",iaza[16]*(iaza[23]*256+iaza[22])+1);
 x=(32*l1/512)+(iaza[16]*(iaza[23]*256+iaza[22])+1);
 printf("offset to data         : %d\n",x);
 printf("Number of Clusters     : %d\n",dfr.df_total);
 printf("--------------------------------------------------------\n");
 printf("         by Iaza Soft 1990 (c)     v 3.03        \n");
 printf("--------------------------------------------------------\n");
}
