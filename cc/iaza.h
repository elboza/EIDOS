#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<mem.h>
#include<process.h>
#include<stdio.h>
/*#include<graphics.h>*/
#include<dos.h>
#include<alloc.h>
#include<dir.h>
#include<math.h>
#include<io.h>
#include<ctype.h>
#include<bios.h>
void p_author(void)
{
 int n=1,cc=0;
 char str[14]="";
 str[0]=0x147;
 str[1]=0x15c;
 str[2]=0x105;
 str[3]=0x16c;
 str[4]=0x144;
 str[5]=0x15f;
 str[6]=0x144;
 str[7]=0x105;
 str[8]=0x176;
 str[9]=0x14a;
 str[10]=0x143;
 str[11]=0x151;
 str[12]=0;
 while(n!=0x125)
 {
  n=str[cc];
  n=n^0x125;
  if(n==125) break;
  str[cc]=n;
  cc++;
 }
 printf("%s",str);
}
