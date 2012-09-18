#include<graphics.h>
void gprintf(char *fmt,...);
int t,gd=DETECT,gm;
main()
{
 t=5;
 initgraph(&gd,&gm,"c:\\tc\\bgi");
 gprintf("T= %d\n",t);
 getch();
 closegraph();
}
