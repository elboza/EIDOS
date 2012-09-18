#include<iaza.h>
#include<gwin.c>
#include<rft5.c>
#include<liste.c>
int kd=0,dato,x,n,cdir,ncount=0,primof=0,curr=0,m;
unsigned char num,*dsk_buff,*fat_buff,*wisfo,root_yn,w_chdir=0,w_men=0;
unsigned int *dpb_seg,*dpb_off,dsk_entr,size,inizclus;
void scrivi_attr(int kk)
{
 int n;
 char aa,num,nn;
 num=status.active_window;
 nn=dsk_buff[kk+11];
 aa=nn;
 aa= aa & 1;
 if(aa==1) {moveto(wi[num].x1+5+(14*8),gety());gprintf(" R/O ");}
 aa=nn & 2;
 if(aa==2) {moveto(wi[num].x1+5+(18*8),gety());gprintf(" HID ");}
 aa=nn & 4;
 if(aa==4) {moveto(wi[num].x1+5+(22*8),gety());gprintf(" SYS");}
 aa=nn & 8;
 if(aa==8) {moveto(wi[num].x1+5+(26*8),gety());gprintf(" VOL ");}
 aa=nn & 0x10;
 if(aa==0x10) {moveto(wi[num].x1+5+(30*8),gety());gprintf(" DIR ");}
 aa=nn & 0x20;
 if(aa==0x20) {moveto(wi[num].x1+5+(34*8),gety());gprintf(" ARC ");}
 if(dsk_buff[kk]==0) {moveto(wi[num].x1+5+(38*8),gety());gprintf(" Unused ");}
 else{
 if(dsk_buff[kk]==0xe5) {moveto(wi[num].x1+5+(38*8),gety());gprintf(" Erased ");}
 if(dsk_buff[kk+7]==0) {moveto(wi[num].x1+5+(38*8),gety());gprintf(" Protected ");}
 for(n=0;n<=10;n++) if(islower(dsk_buff[kk+n])) {moveto(wi[num].x1+5+(38*8),gety());gprintf(" Protected ");}}
}
void scrivi_files(int in)
{
 int n,m;
 for(n=0;n<=10;n++)
 {
  if(searchd(in*32)==0) setcolor(10); else setcolor(15);
  moveto(wi[num].x1+10,wi[num].y1+48+(n*8));
  for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m+(in*32)]);
  gprintf(" ");
  for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m+(in*32)]);
  scrivi_attr(in*32);
  in++;
 }
 setcolor(15);
}
int do_pt1()
{
 char num;
 unsigned int g;
 mouse(2);
 gwindow(130,130,320,190," 1st-method ",15,8,11,7);
 gprintf("Executing...");
 ptr=primo;
 while(ptr)
 {
  ptr=primo;
  if(ptr==NULL) break;
  g=ptr->lenth;
  for(n=0;n<=10;n++) dsk_buff[g+n]=tolower(dsk_buff[g+n]);
  subd(g);
 }
 nogwin();
 mouse(1);
 w_men=1;
 return(0);
}
int do_pt2()
{
 char num;
 unsigned int g,kd;
 mouse(2);
 gwindow(130,130,320,190," 2nd-method ",15,8,11,7);
 gprintf("Executing...");
 ptr=primo;
 while(ptr)
 {
  ptr=primo;
  if(ptr==NULL) break;
  g=ptr->lenth;
  if(dsk_buff[g+7]==0x20) dsk_buff[g+7]=0;
  else
  {
   gwindow(60,60,290,150," Error ! ",14,12,1,4);
   num=status.active_window;
   gprintf("This file can't be");
   moveto(wi[num].x1+5,gety()+10);
   gprintf("protected whith that method");
   sound(500);
   delay(300);
   nosound();
   while((kd=ikey())==0) {}
   nogwin();
  }
  subd(g);
 }
 nogwin();
 mouse(1);
 w_men=1;
 return(0);
}
int do_pt()
{
 int kd=0;
 char num;
 setmenuP(1," 1st-method ",1,do_pt1);
 setmenuP(1," 2nd-method ",1,do_pt2);
 mouse(2);
 gwindow(120,120,320,180," Protect ",15,8,11,7);
 setcolor(15);
 gprintf("Select method...");
 mouse(1);
 while(kd!=27)
 {
  while((kd=ikey())==0) {}
  controlla(kd);
  if(w_men==1) kd=27;
 }
 w_men=0;
 mouse(2);
 nogwin();
 num=status.active_window;
 putimage(wi[num].x1+4,wi[num].y1+46,wisfo,COPY_PUT);
 scrivi_files(primof);
 setcolor(14);
 moveto(wi[num].x1+10,wi[num].y1+48+(curr*8));
 for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
 gprintf(" ");
 for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
 scrivi_attr((primof+curr)*32);
 setcolor(15);
 mouse(1);
 return(0);
}
int do_spt()
{
 char num;
 unsigned int g;
 mouse(2);
 gwindow(130,130,320,190," Unprotect ",15,8,11,7);
 gprintf("Executing...");
 ptr=primo;
 while(ptr)
 {
  ptr=primo;
  if(ptr==NULL) break;
  g=ptr->lenth;
  if(dsk_buff[g+7]==0) dsk_buff[g+7]=0x20;
  for(n=0;n<=10;n++)
  {
   if(islower(dsk_buff[g+n])) dsk_buff[g+n]=toupper(dsk_buff[g+n]);
  }
  subd(g);
 }
 nogwin();
 num=status.active_window;
 putimage(wi[num].x1+4,wi[num].y1+46,wisfo,COPY_PUT);
 scrivi_files(primof);
 setcolor(14);
 moveto(wi[num].x1+10,wi[num].y1+48+(curr*8));
 for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
 gprintf(" ");
 for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
 scrivi_attr((primof+curr)*32);
 setcolor(15);
 mouse(1);
 return(0);
}
int do_info()
{
 unsigned char n1,n2,n3,n4;
 char num;
 unsigned long ss,l1,l2,l3,l4;
 unsigned int bc,uxclus;
 double xclus,xss,xbs,xsc;
 mouse(2);
 gwindow(120,120,320,190," Info ",15,8,11,7);
 num=status.active_window;
 n1=dsk_buff[((primof+curr)*32)+26];
 n2=dsk_buff[((primof+curr)*32)+27];
 bc=n2*256+n1;
 n1=dsk_buff[((primof+curr)*32)+28];
 n2=dsk_buff[((primof+curr)*32)+29];
 n3=dsk_buff[((primof+curr)*32)+30];
 n4=dsk_buff[((primof+curr)*32)+31];
 l1=(long)n1;
 l2=(long)n2;
 l3=(long)n3;
 l4=(long)n4;
 ss=((l4*0x1000000)+(l3*0x10000)+(l2*0x100)+l1);
 gprintf("size : %lu",ss);
 moveto(wi[num].x1+5,gety()+10);
 gprintf("bc : %u",bc);
 xss=(double)ss;
 xbs=(double) s0->bytexsec;
 xsc=(double) s0->secxclus+1;
 xclus=xss/(xsc*xbs);
 moveto(wi[num].x1+5,gety()+10);
 gprintf("xclus : %f",xclus);
 moveto(wi[num].x1+5,gety()+10);
 uxclus=(unsigned int)ceil(xclus);
 gprintf("xclus (): %u",uxclus);
 getch();
 nogwin();
 mouse(1);
 return(0);
}
int esci()
{
 mouse(2);
 nogwin();
 finisci();
 exit(0);
 return(0);
}
void read_root(void)
{
 int n,m;
 ncount=0;
 if((dsk_buff=(char *)malloc(32*s0->root_entries_num))==NULL) {gprintf("Errore nell'allocare dsk_buff");exit(1);}
 absread(s0->drive,s0->data_off-s0->root_off,s0->root_off,dsk_buff);
 dsk_entr=s0->root_entries_num;
 scrivi_files(0);
 root_yn=1;
}
void save_root(void)
{
 abswrite(s0->drive,s0->data_off-s0->root_off,s0->root_off,dsk_buff);

}
void read_subdir(void)
{
 unsigned int nclus,pclus=0;
 int n,m,numclus=0;
 unsigned char n1,n2;
 long lsec;
 ncount=0;
 n2=f.ff_reserved[16];
 n1=f.ff_reserved[15];
 nclus=n2*256+n1;
 pclus=nclus;
 inizclus=nclus;
 while(pclus!=0xffff)
 {
  if(s0->cluster_num>0x1000) pclus=prossimo_16b(pclus,fat_buff);
  else pclus=prossimo_12b(pclus,fat_buff);
  numclus++;
 }
 if((dsk_buff=(char *)malloc(numclus*(s0->secxclus+1)*512))==NULL) {gprintf("Errore nell'allocare dsk_buff");exit(1);}
 dsk_entr=(numclus*(s0->secxclus+1)*512)/32;
 pclus=nclus;
 numclus=0;
 while(pclus!=0xffff)
 {
  lsec=pclus*(s0->secxclus+1)+s0->data_off-(2*(s0->secxclus+1));
  absread(s0->drive,s0->secxclus+1,lsec,dsk_buff+(numclus*512));
  if(s0->cluster_num>0x1000) pclus=prossimo_16b(pclus,fat_buff);
  else pclus=prossimo_12b(pclus,fat_buff);
  numclus++;
 }
 scrivi_files(0);
 root_yn=0;
}
void save_subdir(void)
{
 unsigned int pclus,numclus=0;
 long lsec;
 pclus=inizclus;
 while(pclus!=0xffff)
 {
  lsec=pclus*(s0->secxclus+1)+s0->data_off-(2*(s0->secxclus+1));
  abswrite(s0->drive,s0->secxclus+1,lsec,dsk_buff+(numclus*512));
  if(s0->cluster_num>0x1000) pclus=prossimo_16b(pclus,fat_buff);
  else pclus=prossimo_12b(pclus,fat_buff);
  numclus++;
 }
}
int do_mem()
{
 char num;
 int kd=0;
 mouse(2);
 gwindow(120,75,290,150," Memory ",15,8,11,7);
 num=status.active_window;
 gprintf("Memoria rimanente :");
 moveto(wi[num].x1+5,gety()+10);
 gprintf("%lu",coreleft());
 mouse(1);
 while(kd!=27)
 {
  while((kd=ikey())==0) {}
  controlla(kd);
 }
 mouse(2);
 nogwin();
 num--;
 mouse(1);
 return(0);
}
int ndo_sav()
{
 return(0);
}
int do_sav()
{
 mouse(2);
 gwindow(120,120,200,180," Save ",15,8,11,7);
 gprintf("Saving data.....");
 if(root_yn==1) save_root(); else save_subdir();
 nogwin();
 mouse(1);
 return(0);
}
int do_ro()
{
 unsigned char aa;
 aa=dsk_buff[((primof+curr)*32)+11];
 dsk_buff[((primof+curr)*32)+11]=aa ^ 1;
 setfillstyle(SOLID_FILL,wi[num].riemp);
 bar(wi[num].x1+(14*8),wi[num].y1+48+(curr*8),wi[num].x2-21,wi[num].y1+48+(curr*8)+8);
 setcolor(14);
 moveto(wi[num].x1+10,wi[num].y1+48+(curr*8));
 for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
 gprintf(" ");
 for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
 scrivi_attr((primof+curr)*32);
 setcolor(15);
 return(0);
}
int do_sys()
{
 unsigned char aa;
 aa=dsk_buff[((primof+curr)*32)+11];
 dsk_buff[((primof+curr)*32)+11]=aa ^ 4;
 setfillstyle(SOLID_FILL,wi[num].riemp);
 bar(wi[num].x1+(14*8),wi[num].y1+48+(curr*8),wi[num].x2-21,wi[num].y1+48+(curr*8)+8);

 setcolor(14);
 moveto(wi[num].x1+10,wi[num].y1+48+(curr*8));
 for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
 gprintf(" ");
 for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
 scrivi_attr((primof+curr)*32);
 setcolor(15);
 return(0);
}

int do_hid()
{
 unsigned char aa;
 aa=dsk_buff[((primof+curr)*32)+11];
 dsk_buff[((primof+curr)*32)+11]=aa ^ 2;
 setfillstyle(SOLID_FILL,wi[num].riemp);
 bar(wi[num].x1+(14*8),wi[num].y1+48+(curr*8),wi[num].x2-21,wi[num].y1+48+(curr*8)+8);

 setcolor(14);
 moveto(wi[num].x1+10,wi[num].y1+48+(curr*8));
 for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
 gprintf(" ");
 for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
 scrivi_attr((primof+curr)*32);
 setcolor(15);
 return(0);
}

int do_vol()
{
 unsigned char aa;
 aa=dsk_buff[((primof+curr)*32)+11];
 dsk_buff[((primof+curr)*32)+11]=aa ^ 8;
 setfillstyle(SOLID_FILL,wi[num].riemp);
 bar(wi[num].x1+(14*8),wi[num].y1+48+(curr*8),wi[num].x2-21,wi[num].y1+48+(curr*8)+8);

 setcolor(14);
 moveto(wi[num].x1+10,wi[num].y1+48+(curr*8));
 for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
 gprintf(" ");
 for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
 scrivi_attr((primof+curr)*32);
 setcolor(15);
 return(0);
}

int do_dir()
{
 unsigned char aa;
 aa=dsk_buff[((primof+curr)*32)+11];
 dsk_buff[((primof+curr)*32)+11]=aa ^ 0x10;
 setfillstyle(SOLID_FILL,wi[num].riemp);
 bar(wi[num].x1+(14*8),wi[num].y1+48+(curr*8),wi[num].x2-21,wi[num].y1+48+(curr*8)+8);

 setcolor(14);
 moveto(wi[num].x1+10,wi[num].y1+48+(curr*8));
 for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
 gprintf(" ");
 for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
 scrivi_attr((primof+curr)*32);
 setcolor(15);
 return(0);
}

int do_arc()
{
 unsigned
 char aa;
 aa=dsk_buff[((primof+curr)*32)+11];
 dsk_buff[((primof+curr)*32)+11]=aa ^ 0x20;
 setfillstyle(SOLID_FILL,wi[num].riemp);
 bar(wi[num].x1+(14*8),wi[num].y1+48+(curr*8),wi[num].x2-21,wi[num].y1+48+(curr*8)+8);

 setcolor(14);
 moveto(wi[num].x1+10,wi[num].y1+48+(curr*8));
 for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
 gprintf(" ");
 for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
 scrivi_attr((primof+curr)*32);
 setcolor(15);
 return(0);
}

int do_undel()
{
 char num;
 unsigned int n,g;
 unsigned char n1,n2,n3,n4;
 unsigned long ss,l1,l2,l3,l4;
 unsigned int bc,xclus;
 double uxclus,xbs,xsc,xss;
 ptr=primo;
 while(ptr)
 {
  ptr=primo;
  if(ptr==NULL) break;
  mouse(2);
  gwindow(120,120,320,180," Protect ",15,8,11,7);
  num=status.active_window;
  gprintf("Input 1st letter :");
  g=ptr->lenth;
  moveto(wi[num].x1+5,wi[num].y1+35);
  for(n=0;n<=10;n++) gprintf("%c",dsk_buff[g+n]);
  mouse(1);
  while(kd!=27)
  {
   while((kd=ikey())==0) {}
   controlla(kd);
   if(kd==13)
   {
    dsk_buff[g]=toupper(kd);
    sound(300);
    delay(300);
    nosound();
    n1=dsk_buff[((primof+curr)*32)+26];
    n2=dsk_buff[((primof+curr)*32)+27];
    bc=n2*256+n1;
    n1=dsk_buff[((primof+curr)*32)+28];
    n2=dsk_buff[((primof+curr)*32)+29];
    n3=dsk_buff[((primof+curr)*32)+30];
    n4=dsk_buff[((primof+curr)*32)+31];
    l1=(long)n1;
    l2=(long)n2;
    l3=(long)n3;
    l4=(long)n4;
    ss=((l4*0x1000000)+(l3*0x10000)+(l2*0x100)+l1);
    xss=(double)ss;
    xbs=(double) s0->bytexsec;
    xsc=(double) s0->secxclus+1;
    uxclus=xss/(xsc*xbs);
    xclus=(unsigned int)ceil(uxclus);

    kd=27;
   }
   else
   {
    moveto(wi[num].x1+5,wi[num].y1+35);
    setfillstyle(SOLID_FILL,wi[num].riemp);
    bar(wi[num].x1+5,wi[num].y1+35,wi[num].x1+5+8,wi[num].y1+35+8);
    gprintf("%c",kd);
   }
  }
  mouse(2);
  nogwin();
  mouse(1);
 }
 mouse(2);
 num=status.active_window;
 putimage(wi[num].x1+4,wi[num].y1+46,wisfo,COPY_PUT);
 scrivi_files(primof);
 setcolor(14);
 moveto(wi[num].x1+10,wi[num].y1+48+(curr*8));
 for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
 gprintf(" ");
 for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
 scrivi_attr((primof+curr)*32);
 setcolor(15);
 mouse(1);
 return(0);
}
int do_chdir()
{
 selp(0x10);
 w_chdir=1;
 return(0);
}
main()
{
 strcpy(status.nomefile,"base.idl");
 inizializza();
 setmenuP(0," Files ",1,menuto2);
 setmenuP(0," Memory ",1,do_mem);
 setmenuP(0," Quit! ",1,esci);
 setmenuP(0," Save ",1,menuto2);
 setmenuP(0," Attr. ",1,menuto2);
 setmenuP(0," ChDir. ",1,do_chdir);

 setmenuS(0,0," Protect ",1,do_pt);
 setmenuS(0,0," Unprotect ",1,do_spt);
 setmenuS(0,0," Info ",1,do_info);
 setmenuS(0,0," Undelete ",2,do_undel);

 setmenuS(0,3," Yes ",1,do_sav);
 setmenuS(0,3," No ",1,ndo_sav);

 setmenuS(0,4," R/O ",1,do_ro);
 setmenuS(0,4," HID ",1,do_hid);
 setmenuS(0,4," SYS ",1,do_sys);
 setmenuS(0,4," VOL ",1,do_vol);
 setmenuS(0,4," DIR ",1,do_dir);
 setmenuS(0,4," ARC ",1,do_arc);

 gwindow(60,60,520,200," Main Win ",15,8,11,7);
 num=status.active_window;
 mouse(1);
lab1:
 mouse(2);
 setcolor(14);
 line(wi[num].x1+4,wi[num].y1+46,wi[num].x2-4,wi[num].y1+46);
 line(wi[num].x1+4+(13*8),wi[num].y1+46,wi[num].x1+4+(13*8),wi[num].y2-4);
 line(wi[num].x2-20,wi[num].y1+46,wi[num].x2-20,wi[num].y2-4);
 line(wi[num].x2-20,wi[num].y1+100,wi[num].x2-4,wi[num].y1+100);
 moveto(wi[num].x2-15,wi[num].y1+56);gprintf("%c",24);
 moveto(wi[num].x2-15,wi[num].y2-25);gprintf("%c",25);
 moveto(wi[num].x1+5,wi[num].y1+37);
 gprintf(" Name                   Attributes  ");
 size=imagesize(wi[num].x1+4,wi[num].y1+46,wi[num].x2-21,wi[num].y2-4);
 if((wisfo=(char *)malloc(size))==NULL) {gprintf("Errore nell'allocare wisfo");exit(1);}
 getimage(wi[num].x1+4,wi[num].y1+46,wi[num].x2-21,wi[num].y2-4,wisfo);
 setcolor(15);
 r.h.ah=0x32;
 r.h.dl=0;
 int86x(0x60,&r,&r,&sr);
 dpb_off=MK_FP(sr.ds,r.x.bx);
 dpb_seg=MK_FP(sr.ds,r.x.bx+2);
 s0=MK_FP(dpb_seg,dpb_off);
 if((fat_buff=(char *)malloc(512*s0->secxFAT))==NULL) {gprintf("Errore nell'allocarefat_buff");exit(1);}
 absread(s0->drive,s0->secxFAT,1,fat_buff);
 x=findfirst("*.*",&f,0x3f);
 if(f.ff_reserved[15]==0) read_root();
 else read_subdir();
 setcolor(14);
 moveto(wi[num].x1+10,wi[num].y1+48);
 for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m]);
 gprintf(" ");
 for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m]);
 scrivi_attr(0);
 setcolor(15);

 mouse(1);
 while(kd!=27)
 {
  while((kd=ikey())==0) {}
  controlla(kd);
  dato=contr_drives();
  if(dato!=-1) {setdisk(dato);kd=0;dato=-1;primof=0;curr=0;free(dsk_buff);free(fat_buff);putimage(wi[num].x1+4,wi[num].y1+46,wisfo,COPY_PUT);free(wisfo);goto lab1;}
  if(w_chdir!=0) {w_chdir=0;primof=0;curr=0;free(dsk_buff);free(fat_buff);putimage(wi[num].x1+4,wi[num].y1+46,wisfo,COPY_PUT);free(wisfo);goto lab1;}
  if(kd==-1)
  {

  }
  if(kd==DOWN_KEY)
  {
   if(dsk_buff[((primof+curr)*32)+32]==0) {}else{
   if(curr==10)
   {
    putimage(wi[num].x1+4,wi[num].y1+46,wisfo,COPY_PUT);primof++;scrivi_files(primof);
    setcolor(14);
    moveto(wi[num].x1+10,wi[num].y1+48+(curr*8));
    for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
    gprintf(" ");
    for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
    scrivi_attr((primof+curr)*32);
    setcolor(15);
   }
   else
   {
    if(searchd((primof+curr)*32)==0) setcolor(10);else setcolor(15);
    moveto(wi[num].x1+10,wi[num].y1+48+(curr*8));
    for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
    gprintf(" ");
    for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
    scrivi_attr((primof+curr)*32);
    setcolor(14);curr++;
    moveto(wi[num].x1+10,wi[num].y1+48+(curr*8));
    for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
    gprintf(" ");
    for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
    scrivi_attr((primof+curr)*32);

   }}
  }
  if(kd==UP_KEY)
  {
   if((primof==0) && (curr==0)) {}
   else
   {
    if(curr==0)
    {
    putimage(wi[num].x1+4,wi[num].y1+46,wisfo,COPY_PUT);primof--;scrivi_files(primof);
    setcolor(14);
    moveto(wi[num].x1+10,wi[num].y1+48+(curr*8));
    for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
    gprintf(" ");
    for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
    scrivi_attr((primof+curr)*32);
    setcolor(15);

    }
    else
    {
    if(searchd((primof+curr)*32)==0) setcolor(10);else setcolor(15);
    moveto(wi[num].x1+10,wi[num].y1+48+(curr*8));
    for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
    gprintf(" ");
    for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
    scrivi_attr((primof+curr)*32);
    setcolor(14);curr--;
    moveto(wi[num].x1+10,wi[num].y1+48+(curr*8));
    for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
    gprintf(" ");
    for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
    scrivi_attr((primof+curr)*32);
    }
   }
  }
  if(kd==13)
  {
   if(searchd((primof+curr)*32)==0)
   {
    setcolor(15);
    moveto(wi[num].x1+10,wi[num].y1+48+(curr*8));
    for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
    gprintf(" ");
    for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
    scrivi_attr((primof+curr)*32);
    setcolor(15);
    subd((primof+curr)*32);
   }
   else
   {
    setcolor(10);
    moveto(wi[num].x1+10,wi[num].y1+48+(curr*8));
    for(m=0;m<=7;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
    gprintf(" ");
    for(m=8;m<=10;m++) gprintf("%c",dsk_buff[m+((primof+curr)*32)]);
    scrivi_attr((primof+curr)*32);
    setcolor(15);
    add("boh",(primof+curr)*32);
   }
  }
 }
 mouse(2);
 nogwin();
 finisci();
 return(0);
}
