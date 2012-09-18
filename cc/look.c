#include<iaza.h>
struct ffblk f;
int x,n;
main()
{
 n=0;
 printf("EXE-Search v1.0 by Iaza Soft 1995(c).\n");
 x=findfirst("*.bat",&f,0);
 textcolor(14);
 while(!x)
 {
  gotoxy(n,wherey());
  cprintf("%s    ",f.ff_name);
  n+=15;
  if(n==75) {printf("\n"); n=0;}
  x=findnext(&f);
 }
 x=findfirst("*.exe",&f,0);
 textcolor(13);
 while(!x)
 {
   gotoxy(n,wherey());
   cprintf("%s    ",f.ff_name);
   n+=15;
   if(n==75) {printf("\n");n=0;}
   x=findnext(&f);
 }
 x=findfirst("*.com",&f,0);
 textcolor(11);
 while(!x)
 {
   gotoxy(n,wherey());
   cprintf("%s    ",f.ff_name);
   n+=15;
   if(n==75) { printf("\n");n=0;}
   x=findnext(&f);
 }


}
