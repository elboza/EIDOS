#include<iaza.h>
#include<rft4.c>
char *fat;
main()
{
 read_boot(2);
 fat=(char *)malloc(s0->secperfat*512);
 absread(2,s0->secperfat,1,fat);
 mark_16b(10373,0xfff7,fat);
 abswrite(2,s0->secperfat,1,fat);
}
