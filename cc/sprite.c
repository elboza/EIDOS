#include<iaza.h>
#include<gwin.c>
int gd=DETECT,gm,kd=0,dato=0,x,curx=0,cury=0,barcol=4,bx1=0,by1=0,bx2=49,by2=49;
unsigned int size,buffsize;
char num,buff1[50][50],buff2[50][50],*buff3,*cursott;
FILE *fp;
void da_schermo_a_matrice(void)
{
 int n,m;
 char num;
 num=status.active_window;
 for(n=0;n<=49;n++)
  for(m=0;m<=49;m++)
   buff1[m][n]=getpixel(wi[num].x1+200+m,wi[num].y1+41+n);
}
void da_matrice_a_schermo(void)
{
 int n,m;
 char num;
 num=status.active_window;
 for(n=0;n<=49;n++)
  for(m=0;m<=49;m++)
   {putpixel(wi[num].x1+200+m,wi[num].y1+41+n,buff1[m][n]);setfillstyle(SOLID_FILL,buff1[m][n]); bar(wi[num].x1+5+(m*3)+1,wi[num].y1+40+(n*3)+1,wi[num].x1+5+(m*3)+2,wi[num].y1+40+(n*3)+2);}

}

int do_mem()
{
 char num;
 int kd=0;
 num=status.active_window;
 mouse(2);
 gwindow(200,100,360,140," Memory ",12,1,14,3);
 gprintf("Memoria rimanente :");
 num++;
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
 mouse(1);
 return(0);
}
int do_resize()
{
 int kd=0,volta=0;
 char num;
 num=status.active_window;
 setcolor(0);
 moveto(wi[num].x1+270,wi[num].y1+38+60);
 gprintf("Resize");
 while(kd!=27)
 {
  while((kd=ikey())==0) {}
  if(kd==UP_KEY)
  {
   if(cury!=0)
   {
    mouse(2);
    putimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,cursott,COPY_PUT);
    moveto(wi[num].x1+270,wi[num].y1+38+20); setcolor(3);gprintf("x:%d",curx);
    moveto(wi[num].x1+270,wi[num].y1+38+30);gprintf("y:%d",cury);
    cury--;
    getimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2,cursott);
    bar(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2);
    moveto(wi[num].x1+270,wi[num].y1+38+20); setcolor(0);gprintf("x:%d",curx);
    moveto(wi[num].x1+270,wi[num].y1+38+30);gprintf("y:%d",cury);
    mouse(1);
   }
  }
  if(kd==DOWN_KEY)
  {
   if(cury!=49)
   {
    mouse(2);
    putimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,cursott,COPY_PUT);
    moveto(wi[num].x1+270,wi[num].y1+38+20); setcolor(3);gprintf("x:%d",curx);
    moveto(wi[num].x1+270,wi[num].y1+38+30);gprintf("y:%d",cury);
    cury++;
    getimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2,cursott);
    bar(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2);
    moveto(wi[num].x1+270,wi[num].y1+38+20); setcolor(0);gprintf("x:%d",curx);
    moveto(wi[num].x1+270,wi[num].y1+38+30);gprintf("y:%d",cury);
    mouse(1);
   }
  }
  if(kd==DEX_KEY)
  {
   if(curx!=49)
   {
    mouse(2);
    putimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,cursott,COPY_PUT);
    moveto(wi[num].x1+270,wi[num].y1+38+20); setcolor(3);gprintf("x:%d",curx);
    moveto(wi[num].x1+270,wi[num].y1+38+30);gprintf("y:%d",cury);
    curx++;
    getimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2,cursott);
    bar(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2);
    moveto(wi[num].x1+270,wi[num].y1+38+20); setcolor(0);gprintf("x:%d",curx);
    moveto(wi[num].x1+270,wi[num].y1+38+30);gprintf("y:%d",cury);
    mouse(1);
   }
  }
  if(kd==SIN_KEY)
  {
   if(curx!=0)
   {
    mouse(2);
    putimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,cursott,COPY_PUT);
    moveto(wi[num].x1+270,wi[num].y1+38+20); setcolor(3);gprintf("x:%d",curx);
    moveto(wi[num].x1+270,wi[num].y1+38+30);gprintf("y:%d",cury);
    curx--;
    getimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2,cursott);
    bar(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2);
    moveto(wi[num].x1+270,wi[num].y1+38+20); setcolor(0);gprintf("x:%d",curx);
    moveto(wi[num].x1+270,wi[num].y1+38+30);gprintf("y:%d",cury);
    mouse(1);
   }
  }
  if(kd==13)
  {
   mouse(2);
   setfillstyle(SOLID_FILL,barcol);
   bar(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2);
   getimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2,cursott);
   setfillstyle(SOLID_FILL,0);
   volta++;
   if(volta==2) {kd=27;bx2=curx;by2=cury;} else{bx1=curx;by1=cury;}
   mouse(1);
  }
 }
 kd=0;
 setcolor(3);
 moveto(wi[num].x1+270,wi[num].y1+38+60); gprintf("Resize");
 setcolor(12);
 return(0);
}
int deflen()
{
 dato=0;
 mouse(2);
 nogwin();
 mouse(1);
 return(0);
}
int newlen()
{
 char num,s[15];
 num=status.active_window;
 mouse(2);
 gprintf("Nuovo valore ??");
 moveto(wi[num].x1+5,wi[num].y1+50);
 mouse(1);
 ginput(s);
 mouse(2);
 nogwin();
 num--;
 if(s[0]!=-1) {size=atoi(s);dato=1;}
 mouse(1);
 return(0);
}
int lungh()
{
 int kd=0;
 char s1[15];
 mouse(2);
 setmenuP(status.active_window+1," Input ",1,newlen);
 setmenuP(status.active_window+1," Default ",1,deflen);
 gwindow(140,90,380,150," Modify Buffer ",12,1,14,3);
 num=status.active_window;
 mouse(1);
 while((kd=ikey())==0) {}
 controlla(kd);
 return(0);
}
int fileopen()
{
 struct ffblk ik;
 char num;
 if(dato==0) {size=imagesize(bx1,by1,bx2,by2);}
 mouse(1);
 ik=selp();
 mouse(2);
 if((buff3=(char *)malloc(size))==NULL) {printf("Errore di allocazione buff3");exit(1);}
 if(ik.ff_fsize!=-1)
 {
  if((fp=fopen(ik.ff_name,"rb"))==NULL) {gprintf("Errore nell' aprire il file");exit(1);}
  fread(buff3,1,size,fp);
  fclose(fp);
  putimage(wi[status.active_window].x1+200,wi[status.active_window].y1+41,buff3,COPY_PUT);
  da_schermo_a_matrice();
  da_matrice_a_schermo();
 }
 free(buff3);
 mouse(1);
 return(0);
}
int filesave()
{
 char num,nome[15];
 mouse(2);
 gwindow(140,90,280,150," Save ",12,1,14,3);
 num=status.active_window;
 gprintf("Nome del file ??");
 moveto(wi[num].x1+5,wi[num].y1+31);
 mouse(1);
 ginput(nome);
 mouse(2);
 nogwin();
 num--;
 perc_init();
 if(nome[0]!=-1)
 {
  size=imagesize(bx1,by1,bx2,by2);
  if((buff3=(char *)malloc(size))==NULL) {printf("Errore di allocazione buff3");exit(1);}
  getimage(wi[num].x1+200+bx1,wi[num].y1+41+by1,wi[num].x1+200+bx2,wi[num].y1+41+by2,buff3);
  percent(1,4);
  fp=fopen(nome,"wb");
  percent(2,4);
  fwrite(buff3,1,size,fp);
  percent(3,4);
  fclose(fp);
  percent(4,4);
 }
 perc_end();
 free(buff3);
 mouse(1);
 return(0);
}
int concat()
{
 char num,nome1[15],nome2[15],jj;
 int n,xl;
 mouse(2);
 gwindow(140,90,320,150," Conatena ",12,1,14,3);
 num=status.active_window;
 gprintf("Nome del file ??");
 moveto(wi[num].x1+5,wi[num].y1+31);
 mouse(1);
 ginput(nome1);
 moveto(wi[num].x1+5,wi[num].y1+41);
 gprintf("Nome dell' oggetto ??");
 moveto(wi[num].x1+5,wi[num].y1+51);
 ginput(nome2);
 mouse(2);
 nogwin();
 num--;
 if((nome1[0]!=-1) && (nome2[0]!=-1))
 {
  size=imagesize(bx1,by1,bx2,by2);
  if((buff3=(char *)malloc(size))==NULL) {gprintf("Errore di allocazione buff3");exit(1);}
  getimage(wi[num].x1+200+bx1,wi[num].y1+41+by1,wi[num].x1+200+bx2,wi[num].y1+41+by2,buff3);
  fp=fopen(nome1,"ab+");
  fprintf(fp,"%s %u ",nome2,size);
  fwrite(buff3,1,size,fp);
  fclose(fp);
 }
 free(buff3);
 mouse(1);
 return(0);
}
int about()
{
 return(0);
}
int mirror()
{
 int m,n;
 mouse(2);
 da_schermo_a_matrice();
 for(n=0;n<=49;n++)
  for(m=0;m<=49;m++)
  {
   buff2[49-m][n]=buff1[m][n];
  }
 for(n=0;n<=49;n++)
  for(m=0;m<=49;m++)
  {
   buff1[m][n]=buff2[m][n];
  }
 da_matrice_a_schermo();
 mouse(1);
 return(0);
}
int undo()
{
 return(0);
}
int do_circle()
{
 return(0);
}
int do_paint()
{
 return(0);
}
int do_setcol()
{
 char num,nc[5];
 int nnc;
 mouse(2);
 gwindow(240,180,370,210," Setcolor ",12,1,14,3);
 gprintf("New color ??");
 mouse(1);
 ginput(nc);
 if(nc[0]!=-1)
 {
  nnc=atoi(nc);
  barcol=nnc;
 }
 mouse(2);
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
int do_replace()
{
 int n,m;
 char num,oldcol,newcol,ss[5];
 mouse(2);
 gwindow(200,140,540,210," Replace Color ",12,1,14,3);
 num=status.active_window;
 gprintf("colore da rimpiazzare ??");
 mouse(1);
 moveto(wi[num].x1+5,wi[num].y1+31);
 ginput(ss);
 if(ss[0]!=-1)
 {
  oldcol=atoi(ss);
  moveto(wi[num].x1+5,wi[num].y1+41);
  gprintf("Colore nuovo ??");
  moveto(wi[num].x1+5,wi[num].y1+51);
  ginput(ss);
  if(ss[0]!=-1)
  {
   newcol=atoi(ss);
   mouse(2);
   nogwin();
   num--;
   da_schermo_a_matrice();
   for(n=0;n<=49;n++)
    for(m=0;m<=49;m++)
    {
     if(buff1[m][n]==oldcol) buff1[m][n]=newcol;
    }
   da_matrice_a_schermo();
   mouse(1);
  }
 }
 return(0);
}
main()
{
 strcpy(status.nomefile,"sprite.idl");
 inizializza();
 setmenuP(0," Files ",1,menuto2);
 setmenuP(0," Edit ",1,menuto2);
 setmenuP(0," Memory ",1,do_mem);

 setmenuS(0,0," Open ",1,fileopen);
 setmenuS(0,0," Save ",1,filesave);
 setmenuS(0,0," Concatena ",1,concat);
 setmenuS(0,0," Force Len ",1,lungh);
 setmenuS(0,0," Quit ",1,esci);
 setmenuS(0,0," About... ",1,about);

 setmenuS(0,1," Mirror ",1,mirror);
 setmenuS(0,1," Undo ",1,undo);
 setmenuS(0,1," Circle ",1,do_circle);
 setmenuS(0,1," Paint ",1,do_paint);
 setmenuS(0,1," Setcolor ",1,do_setcol);
 setmenuS(0,1," Resize buff ",1,do_resize);
 setmenuS(0,1," Replace col ",2,do_replace);

 size=imagesize(0,0,55,55);
 buffsize=size;
 size=imagesize(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+3,wi[num].y1+40+(cury*3)+3);
 cursott=(char*)malloc(size);
 gwindow(50,50,400,250," Sprite Editor ",12,1,14,3);
 num=status.active_window;
 rectangle(wi[num].x1+5,wi[num].y1+40,wi[num].x1+5+(50*3),wi[num].y1+40+(50*3));
 rectangle(wi[num].x1+199,wi[num].y1+40,wi[num].x1+199+51,wi[num].y1+40+51);
 getimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2,cursott);
 setfillstyle(SOLID_FILL,0);
 bar(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2);

 mouse(1);
 while(kd!=27)
 {
  while((kd=ikey())==0) {}
  controlla(kd);
  x=contr_drives();
  if(x!=-1) {setdisk(x);}
  if(kd==UP_KEY)
  {
   if(cury!=0)
   {
    mouse(2);
    putimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,cursott,COPY_PUT);
    moveto(wi[num].x1+270,wi[num].y1+38+20); setcolor(3);gprintf("x:%d",curx);
    moveto(wi[num].x1+270,wi[num].y1+38+30);gprintf("y:%d",cury);
    cury--;
    getimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2,cursott);
    bar(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2);
    moveto(wi[num].x1+270,wi[num].y1+38+20); setcolor(0);gprintf("x:%d",curx);
    moveto(wi[num].x1+270,wi[num].y1+38+30);gprintf("y:%d",cury);
    mouse(1);
   }
  }
  if(kd==DOWN_KEY)
  {
   if(cury!=49)
   {
    mouse(2);
    putimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,cursott,COPY_PUT);
    moveto(wi[num].x1+270,wi[num].y1+38+20); setcolor(3);gprintf("x:%d",curx);
    moveto(wi[num].x1+270,wi[num].y1+38+30);gprintf("y:%d",cury);
    cury++;
    getimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2,cursott);
    bar(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2);
    moveto(wi[num].x1+270,wi[num].y1+38+20); setcolor(0);gprintf("x:%d",curx);
    moveto(wi[num].x1+270,wi[num].y1+38+30);gprintf("y:%d",cury);
    mouse(1);
   }
  }
  if(kd==DEX_KEY)
  {
   if(curx!=49)
   {
    mouse(2);
    putimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,cursott,COPY_PUT);
    moveto(wi[num].x1+270,wi[num].y1+38+20); setcolor(3);gprintf("x:%d",curx);
    moveto(wi[num].x1+270,wi[num].y1+38+30);gprintf("y:%d",cury);
    curx++;
    getimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2,cursott);
    bar(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2);
    moveto(wi[num].x1+270,wi[num].y1+38+20); setcolor(0);gprintf("x:%d",curx);
    moveto(wi[num].x1+270,wi[num].y1+38+30);gprintf("y:%d",cury);
    mouse(1);
   }
  }
  if(kd==SIN_KEY)
  {
   if(curx!=0)
   {
    mouse(2);
    putimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,cursott,COPY_PUT);
    moveto(wi[num].x1+270,wi[num].y1+38+20); setcolor(3);gprintf("x:%d",curx);
    moveto(wi[num].x1+270,wi[num].y1+38+30);gprintf("y:%d",cury);
    curx--;
    getimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2,cursott);
    bar(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2);
    moveto(wi[num].x1+270,wi[num].y1+38+20); setcolor(0);gprintf("x:%d",curx);
    moveto(wi[num].x1+270,wi[num].y1+38+30);gprintf("y:%d",cury);
    mouse(1);
   }
  }
  if(kd==13)
  {
   mouse(2);
   setfillstyle(SOLID_FILL,barcol);
   bar(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2);
   getimage(wi[num].x1+5+(curx*3)+1,wi[num].y1+40+(cury*3)+1,wi[num].x1+5+(curx*3)+2,wi[num].y1+40+(cury*3)+2,cursott);
   setfillstyle(SOLID_FILL,0);
   putpixel(wi[num].x1+200+curx,wi[num].y1+41+cury,barcol);
   mouse(1);
  }
 }
 mouse(2);
 nogwin();
 finisci();
 return(0);
}
