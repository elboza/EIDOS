#include<iaza.h>
FILE *fp;
char name[80],ret,x,y;
unsigned int xx,yy;
unsigned int get(void)
{
 x=getc(fp);
 y=getc(fp);
 xx=y+256+x;
 return(xx);
}
main()
{
 printf("Nome del File da osservare->");
 gets(name);
 fp=fopen(name,"r");
 x=getc(fp);
 printf("Sigle di .EXE...%c",x);
 x=getc(fp);printf("%c\n",x);
 printf("%d\n",get());
 printf("Number of 512 byte pages: %d\n",get());
 printf("Number of Total bytes: %d\n",get()*512);
 printf("Number of relocation items: %d|n",get());
 printf("Size of heather %d paragraphs...%d bytes\n",get(),get()*16);
 printf("Minimum number of paragraphs : %d...of bytes: %d\n",get(),get()*16);
 printf("Maximum number of paragraphs : %d...of bytes : %d\n",get(),get()*16);
 printf("SS value : %d\n",get());
 printf("SP value : %d\n",get());
 printf("Word cecksum : %d\n",get());
 printf("IP value : %d\n",get());
 printf("CS value : %d\n",get());
 printf("Displacement of the first relocation item : %d\n",get());
 printf("Overlay number : %d\n",get());
}
