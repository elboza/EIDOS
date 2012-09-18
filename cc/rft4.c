unsigned int prossimo_12b(unsigned int a,char *bufat12)
{
 unsigned int *punit;
 if((a<2)||(a>0xfef)) return(0);
 punit=(unsigned int *) (bufat12+a+(a/2));
 if((a&0x0001)==0) *punit=(*punit & 0x0fff);
 else *punit=(*punit & 0xfff0)>>4;
 return(*punit);
}
unsigned int prossimo_16b(unsigned a,char *bufat16)
{
 unsigned int *punit;
 punit=(unsigned int *) (bufat16+(2*a));
 return(*punit);
}
void mark_12b(unsigned int nclus,unsigned int val,char *bufat12)
{
 unsigned int *punit,z;
 punit=(unsigned int *)(bufat12+nclus+(nclus/2));
 z=*punit;
 if((nclus & 0x0001)==0)
 {
  z=(z & 0xf000);
  z=z+val;
  *punit=z;
 }
 else
 {
  z=(z & 0x000f);
  *punit=val*16;
  *punit=(*punit+z);
 }
}
void mark_16b(unsigned int nclus,unsigned int val,char *bufat16)
{
 unsigned int *punit;
 punit=(unsigned int *)(bufat16+(2*nclus));
 *punit=val;
}
