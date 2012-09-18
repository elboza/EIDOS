#include<iaza.h>
unsigned char x,g;
unsigned int loc=0,y,n,z,w;
double mi,x2;
main()
{
 printf("Memory MAP v 1.0, by Iaza Soft 1990(c).\n-\n");
 printf("   Addr      Bytes        Name\n");
 printf("----------- -------   --------------\n");
 while(loc!=65535){
 g=peekb(loc,0);
 y=peek(loc,16);
 z=peek(loc,1);
 w=peek(loc,3);
 n=8;
 if((g==0x4d) && (y==0x20cd) && (z!=0))
 {
  printf("%Xh-",loc);
  printf("%Xh %u       ",w+loc,w*16);
  gotoxy(24,wherey());
  while((x=peekb(loc,n))!=0)
  {
   printf("%c",x);
   n++;
  }
  printf("\n");
 }
 loc++;
}
fine:

 y=biosmemory();
 mi=(double)y*1024;
 printf("-|-\n");
 printf("Memoria Totale.....%8.0f bytes\n",mi);
 x2=(double)_psp*16;
 mi=mi-x2;
 printf("Memoria rimanente..%8.0f bytes\n",mi);
 sound(100);
 delay(300);
 nosound();
}
