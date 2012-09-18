#include<iaza.h>
#include<iazawin.h>
main()
{
 getmem(0,5,5,60,18);
 vt_wind(5,5,60,18,1," Ciao ",0x2e,0x4e,'²',0x4e,1,0);
 getch();
 putmem(0,5,5,60,18);
}
