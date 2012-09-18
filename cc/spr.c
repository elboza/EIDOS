#include<iaza.h>
int gd=DETECT,gm,size;
char *buff;
FILE *nome;
main()
{
 initgraph(&gd,&gm,"c:\\tc\\bgi");
 size=imagesize(0,0,50,50);
 buff=(char*)malloc(size);
 nome=fopen("b:\\sprites\\inkdx5.","r");
 fread(buff,size+1,1,nome);
 putimage(0,0,buff,COPY_PUT);
 getch();
}
