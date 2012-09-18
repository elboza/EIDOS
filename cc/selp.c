#include<iaza.h>
#include<ikey2.c>
#include<vt_bios2.c>
#include<elfab3.c>
unsigned _stklen=65535;
struct ftime *fdt;
struct ffblk file[400];
struct lista
{
 struct lista *prev,*next;
 char name[15];
 int lenth;
}*ptr,*primo=NULL,*ultimo=NULL;
int gname(struct ffblk *a,struct ffblk *b)
{
 return(strcmp(a->ff_name,b->ff_name));
}
int gsize(struct ffblk *a,struct ffblk *b)
{ return(a->ff_fsize-b->ff_fsize); }

void scrivi_fil(int eliaz)
{
 if((file[eliaz].ff_attrib==0x8) || (file[eliaz].ff_attrib==0x28)) vt_puts(" <Label> ");
 else if(file[eliaz].ff_attrib==0x10) vt_puts(" < Dir > ");else
 vt_printf("%9.0ld",file[eliaz].ff_fsize);
 fdt=&file[eliaz].ff_ftime;
 vt_gotoxy(vt_wherex()+1,vt_wherey());vt_printf("%02u:%02u",fdt->ft_hour,fdt->ft_min);
 vt_gotoxy(vt_wherex()+1,vt_wherey());vt_printf("%02u/%02u/%02u",fdt->ft_day,fdt->ft_month,fdt->ft_year+80);
}
void redir()
{
struct ffblk f;
int n,x,v,cdir=0,cnas=0,nor=0,count=0;
int q1,q2;

struct ffblk a[200],nas[100],dir[100];

 x=findfirst("*.*",&f,0x3f);
 while(!x)
 {
  if(f.ff_attrib==0x10) { dir[cdir]=f;cdir++;x=findnext(&f);continue;}
  if((f.ff_attrib==0x22) || (f.ff_attrib==0x23)|| (f.ff_attrib==0x27)) { strcpy(f.ff_name,strlwr(f.ff_name));nas[cnas]=f;cnas++;x=findnext(&f);continue; }
  strcpy(f.ff_name,strlwr(f.ff_name));a[nor]=f;
  nor++;
  x=findnext(&f);
 }
 qsort(dir,cdir,sizeof(dir[0]),gname);
 qsort(nas,cnas,sizeof(nas[0]),gname);
 qsort(a,nor,sizeof(a[0]),gname);
 for (v=0;v<cdir;v++) { file[v]=dir[v];count++;}
 for (v=cdir;v<cdir+cnas;v++) { file[v]=nas[v-cdir];count++;}
 for (v=cdir+cnas;v<cdir+cnas+nor;v++) { file[v]=a[v-cdir-cnas];count++;}
}
void scrlup(char num)
{
 r.h.ah=7;
 r.h.al=1;
 r.h.ch=wi_y1[num]+4;
 r.h.cl=wi_x1[num]+1;
 r.h.dh=wi_y1[num]+8;
 r.h.dl=wi_x1[num]+47;
 r.h.bh=0x1e;
 int86(0x10,&r,&r);
 mliney(wi_x1[num]+15,wi_y1[num]+4,5,'³');
 mliney(wi_x1[num]+25,wi_y1[num]+4,5,179);
 mliney(wi_x1[num]+31,wi_y1[num]+4,5,179);
 mliney(wi_x1[num]+40,wi_y1[num]+4,5,179);
}

void scrldwn(char num)
{
 r.h.ah=6;
 r.h.al=1;
 r.h.ch=wi_y1[num]+4;
 r.h.cl=wi_x1[num]+1;
 r.h.dh=wi_y1[num]+8;
 r.h.dl=wi_x1[num]+47;
 r.h.bh=0x1e;
 int86(0x10,&r,&r);
 mliney(wi_x1[num]+15,wi_y1[num]+4,5,'³');
 mliney(wi_x1[num]+25,wi_y1[num]+4,5,179);
 mliney(wi_x1[num]+31,wi_y1[num]+4,5,179);
 mliney(wi_x1[num]+40,wi_y1[num]+4,5,179);
}

void add(char *s,int d)
{
 ptr=(struct lista*)malloc(sizeof(struct lista));
 if(ultimo==NULL) primo=ptr;
 if(ultimo) ultimo->next=ptr;
 ptr->prev=ultimo;
 ptr->next=NULL;
 ultimo=ptr;
 strcpy(ptr->name,s);
 ptr->lenth=d;
}
int search(char *nem)
{
 for(ptr=primo;ptr;ptr=ptr->next)
 {
  if(strcmp(nem,ptr->name)==0) return(0);
 }
 return(-1);
}
void sub(char *s)
{
 for(ptr=primo;ptr;ptr=ptr->next)
 {
  if(strcmp(ptr->name,s)==0)
  {
   if (ptr->prev) ptr->prev->next=ptr->next;
   else primo=ptr->next;
   if (ptr->next) ptr->next->prev=ptr->prev;
   else ultimo=ptr->prev;
   free(ptr);
   break;
  }
 }
}
int selp(char *s,char scol,char bor,char bcol,char riemp,char rcol,char omb,char num)
{
 int n,kd=0,o,iaz=0,locy=0,col1,col2,intsp,self=0;
 mouse(2);
 getmem(num,21,9,59,11);
 vt_wind(21,9,59,11,1,"",0x00,0x21,' ',0x20,1,num);
 vt_gotoxy(wi_x1[num]+3,wi_y1[num]+1);vt_puts(" Reading Disk Informations... ");
 redir();
 putmem(num,wi_x1[num],wi_y1[num],wi_x2[num],wi_y2[num]);
 getmem(num,10,7,58,19);
 vt_wind(10,7,58,19,bor,s,scol,bcol,riemp,rcol,omb,num);
 vt_gotoxy(wi_x1[num]+2,wi_y1[num]+1);
 vt_puts("A: B: C: D: E:");
 vt_gotoxy(wi_x1[num]+27,wi_y1[num]+1);
 vt_puts("Selected files:");
 vt_gotoxy(wi_x1[num]+42,wi_y1[num]+1);
 vt_printf("%5.0d",self);
 vt_gotoxy(wi_x1[num]+2,wi_y1[num]+3);
 vt_puts("Name          Size      Time  Date    Attr.");
 mliney(wi_x1[num]+15,wi_y1[num]+4,5,'³');
 mliney(wi_x1[num]+25,wi_y1[num]+4,5,179);
 mliney(wi_x1[num]+31,wi_y1[num]+4,5,179);
 mliney(wi_x1[num]+40,wi_y1[num]+4,5,179);
 mlinex(wi_x1[num]+1,wi_y1[num]+9,47,196);
 vt_gotoxy(wi_x1[num]+15,wi_y1[num]+9);
 vt_putch(193);
 vt_gotoxy(wi_x1[num]+25,wi_y1[num]+9);
 vt_putch(193);
 vt_gotoxy(wi_x1[num]+31,wi_y1[num]+9);vt_putch(193);
 vt_gotoxy(wi_x1[num]+40,wi_y1[num]+9);vt_putch(193);
 cmenu(wi_x1[num]+15,wi_y1[num]+10," Ok ",0x2e,0x1e);
 cmenu(wi_x1[num]+26,wi_y1[num]+10," Cancel ",0x2e,0x1e);
 vt_color=0x1e;
 for(n=0;n<=4;n++)
 {
  if((o=search(file[n].ff_name))==0) vt_color=0x1f;else vt_color=0x1e;
  if(strcmp(file[n].ff_name,"")==0) break;
  vt_gotoxy(wi_x1[num]+2,wi_y1[num]+n+4);vt_puts(file[n].ff_name);
  vt_gotoxy(wi_x1[num]+16,wi_y1[num]+n+4);
  scrivi_fil(n);
 }
 hilix(wi_x1[num]+1,wi_y1[num]+locy+4,47,0x70);
 mouse(1);
 while(kd!=13)
 {
  while((kd=ikey())==0){}
  mouse(2);
  if(kd==-1)
  {
   if(k_y/8==wi_y1[num]) {if((k_x/8<wi_x2[num]) && (k_x/8>wi_x1[num])) movewind(num);}
   if(k_y/8==wi_y1[num]+10) {if((k_x/8<wi_x1[num]+19) && (k_x/8>=wi_x1[num]+15)) {mouse(2);putmem(num,wi_x1[num],wi_y1[num],wi_x2[num],wi_y2[num]);mouse(1);return(0);}}
   if(k_y/8==wi_y1[num]+10) {if((k_x/8<=wi_x1[num]+33) && (k_x/8>=wi_x1[num]+26)) {mouse(2);putmem(num,wi_x1[num],wi_y1[num],wi_x2[num],wi_y2[num]);mouse(1);return(-1);}}
   if(k_y/8==wi_y1[num]+9) if((k_x/8>wi_x1[num]) && (k_x/8<wi_x1[num]+48))kd=80+256;
   if(k_y/8==wi_y1[num]+3) if((k_x/8>wi_x1[num]) && (k_x/8<wi_x1[num]+48))kd=72+256;
   if((k_y/8>wi_y1[num]+3) && (k_y/8<wi_y1[num]+9)) if((k_x/8>wi_x1[num]) && (k_x/8<wi_x1[num]+48))
   {
    if(locy+4<((k_y/8)-(wi_y1[num])))
    {
     if((o=search(file[iaz].ff_name))==0) col1=0x1f;else col1=0x1e;
     hilix(wi_x1[num]+1,wi_y1[num]+locy+4,47,col1);
     intsp=((k_y/8)-(wi_y1[num]+locy+4));
     iaz+=intsp;
     if((o=search(file[iaz].ff_name))==0) col1=0x7f;else col1=0x70;
     hilix(wi_x1[num]+1,k_y/8,47,col1);
     locy+=intsp;
    }
    if(locy+4>((k_y/8)-(wi_y1[num])))
    {
     if((o=search(file[iaz].ff_name))==0) col1=0x1f;else col1=0x1e;
     hilix(wi_x1[num]+1,wi_y1[num]+locy+4,47,col1);
     intsp=((wi_y1[num]+locy+4)-(k_y/8));
     iaz-=intsp;
     if((o=search(file[iaz].ff_name))==0) col1=0x7f;else col1=0x70;
     hilix(wi_x1[num]+1,k_y/8,47,col1);
     locy-=intsp;
    }

   }
  }
  if(kd==-2)
  {
   if((k_y/8>wi_y1[num]+3) && (k_y/8<wi_y1[num]+9)) if((k_x/8>wi_x1[num]) && (k_x/8<wi_x1[num]+48))
   {
    kd=82+256;
    if(locy+4<((k_y/8)-(wi_y1[num])))
    {
     if((o=search(file[iaz].ff_name))==0) col1=0x1f;else col1=0x1e;
     hilix(wi_x1[num]+1,wi_y1[num]+locy+4,47,col1);
     intsp=((k_y/8)-(wi_y1[num]+locy+4));
     iaz+=intsp;
     if((o=search(file[iaz].ff_name))==0) col1=0x7f;else col1=0x70;
     hilix(wi_x1[num]+1,k_y/8,47,col1);
     locy+=intsp;
    }
    if(locy+4>((k_y/8)-(wi_y1[num])))
    {
     if((o=search(file[iaz].ff_name))==0) col1=0x1f;else col1=0x1e;
     hilix(wi_x1[num]+1,wi_y1[num]+locy+4,47,col1);
     intsp=((wi_y1[num]+locy+4)-(k_y/8));
     iaz-=intsp;
     if((o=search(file[iaz].ff_name))==0) col1=0x7f;else col1=0x70;
     hilix(wi_x1[num]+1,k_y/8,47,col1);
     locy-=intsp;
    }

   }
  }
  if(kd==82+256)
  {
   if((o=search(file[iaz].ff_name))==0)
   {
    hilix(wi_x1[num]+1,wi_y1[num]+locy+4,47,0x70);
    sub(file[iaz].ff_name);
    self--;
   }
   else
   {
    hilix(wi_x1[num]+1,wi_y1[num]+locy+4,47,0x7f);
    add(file[iaz].ff_name,5);
    self++;
   }
   vt_gotoxy(wi_x1[num]+27,wi_y1[num]+1);
   vt_puts("Selected files:");
   vt_gotoxy(wi_x1[num]+42,wi_y1[num]+1);
   vt_printf("%5.0d",self);
  }
  if(kd==80+256)
  {
   if(strcmp(file[iaz+1].ff_name,"")==0) {iaz--;locy--;}
   if((o=search(file[iaz].ff_name))==0) {col1=0x1f;col2=0x7f;}else {col1=bcol;col2=0x70;}
   hilix(wi_x1[num]+1,wi_y1[num]+locy+4,47,col1);
   iaz++;
   if((o=search(file[iaz].ff_name))==0) {col1=0x1f;col2=0x7f;}else {col1=bcol;col2=0x70;}
   if(locy>=4) {scrldwn(num);vt_gotoxy(wi_x1[num]+2,wi_y1[num]+8);vt_puts(file[iaz].ff_name);vt_gotoxy(wi_x1[num]+16,wi_y1[num]+8);scrivi_fil(iaz);locy--;}
   locy++;
   hilix(wi_x1[num]+1,wi_y1[num]+locy+4,47,col2);

  }
  if(kd==72+256)
  {
   if(iaz==0) {iaz++;locy++;}
   if((o=search(file[iaz].ff_name))==0) {col1=0x1f;col2=0x7f;}else {col1=bcol;col2=0x70;}
   hilix(wi_x1[num]+1,wi_y1[num]+locy+4,47,col1);
   iaz--;
   if((o=search(file[iaz].ff_name))==0) {col1=0x1f;col2=0x7f;}else {col1=bcol;col2=0x70;}
   if(locy<=0) {scrlup(num);vt_gotoxy(wi_x1[num]+2,wi_y1[num]+4);vt_puts(file[iaz].ff_name);vt_gotoxy(wi_x1[num]+16,wi_y1[num]+4);scrivi_fil(iaz);locy++;}
   locy--;
   hilix(wi_x1[num]+1,wi_y1[num]+locy+4,47,col2);
  }
 mouse(1);
 }
 mouse(2);
 putmem(num,wi_x1[num],wi_y1[num],wi_x2[num],wi_y2[num]);
 mouse(1);
 return(2);
}

main()
{
 int f,o;
 mouse(0);
 setmwin(0,0,79,42);
 mouse(1);
 f=selp(" Ciao ",0x15,1,0x1e,' ',0x1e,1,0);
 mouse(2);
 printf("%d\n",f);
}
