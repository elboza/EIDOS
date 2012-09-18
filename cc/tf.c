#include<iaza.h>
double disk;
unsigned char uno,due,off,kk,dr;
unsigned int l;
int d,n,x,num;
char pass[5],dir[80],fdir[80]="\\";
char *iaza,*boot;
main(argc,argv)
int argc;
char *argv[];
{
 if(argc!=2) { printf("ERRORE! di sintassi:specificare il drive."); exit(1); }
 if((strcmp(argv[1],"a:")==0) || (strcmp(argv[1],"A:")==0)) d=0;
 if((strcmp(argv[1],"b:")==0) || (strcmp(argv[1],"B:")==0)) d=1;
 if((strcmp(argv[1],"c:")==0) || (strcmp(argv[1],"C:")==0)) d=2;
 if((strcmp(argv[1],"d:")==0) || (strcmp(argv[1],"D:")==0)) d=3;
 if((strcmp(argv[1],"e:")==0) || (strcmp(argv[1],"E:")==0)) d=4;
 boot=(char*)malloc(512);
 absread(d,1,0,boot);
 textcolor(14);
 textbackground(1);
 cputs("Turbo-Formatter v 3.0: by Iaza Soft 1990(c)");
 textbackground(0);
 textcolor(12);
 putchar(13);
 cprintf("\n\nDrive %s:\n",argv[1]);
 putchar(13);
 printf("system id  :");
 for(n=3;n<=10;n++) printf("%c",boot[n]);
 printf("\n");
 dr=boot[21];
 printf("byte id    :%X\n",dr);
 textcolor(14);
 cputs("Tutti i dati andranno persi: Vuoi proseguire ?(yes/no)\n");
 putchar(13);
 gets(pass);
 if(strcmp(strlwr(pass),"yes")!=0) exit(1);
 dr=boot[21];
 if(dr==0xf8) { cprintf("Non Formattare l'Hard Disk.\n"); exit(1); }
 num=boot[23]*256+boot[22];
 iaza=(char*)malloc(num*512);
 absread(d,num,1,iaza);
 for(n=3;n<=num*512;n++) iaza[n]=0;
 abswrite(d,num,1,iaza);
 absread(d,num,num+1,iaza);
 for(n=3;n<=num*512;n++) iaza[n]=0;
 abswrite(d,num,num+1,iaza);
 uno=boot[18];
 due=boot[17];
 l=uno*256+due;
 off=boot[16]*(boot[23]*256+boot[22])+1;
 kk=(32*l/512);
 absread(d,kk,off,iaza);
 for(n=0;n<=kk*512;n++) iaza[n]=0;
 abswrite(d,kk,off,iaza);
 absread(d,1,0,iaza);
 strcpy(pass,"IazaSoft");
 for(n=3;n<=10;n++) iaza[n]=pass[n-3];
 abswrite(d,1,0,iaza);
}
