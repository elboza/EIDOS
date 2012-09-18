#include"dos.h"
struct
{
 char barcol,scripcol,selcol,hilicol;
 struct
 {
  char str[13];
  int ncar;
  int(*x)();
  struct
  {
   char str[13];
   int ncar;
   int (*x)();
  }m[20];
 }M[9];
}n_menu[6];
int process(int(*p)());
int M_count=0,MP_count[6],MS_count[9],MAP_count[6][9];
void menutype(char num,char barcol,char sricol,char hihicol,char selcol);
struct
{
 int x1,x2,y1,y2;
 unsigned char omb,bord,scol,bcol,riemp,rcol;
 char title;
}wi[6];
void make_menu(char num);
void setmenuP(char num,char *item,int lett,int (*p)());
void ombra(char num);
void vt_wind(int x1,int y1,int x2,int y2,char bord,char *s,unsigned char scol,unsigned char bcol,unsigned char riemp,unsigned char rcol,char ombr,char num);
void vt_box(int x1,int y1,int x2,int y2,char m);
void movewind(char num);
int k_x,k_y;
union REGS r;
int mouse(int ax);
int ikey(void);
int vt_x=0,vt_y=0;
unsigned char vt_color=0x07;
char *getmm[6];
unsigned char vt_mixcol(char back,char fore);
int vt_wherey(void);
int vt_wherex(void);
void vt_gotoxy(int x,int y);
void inizializza(void);
void vt_putch(char hy);
char vt_getchar(void);
void vt_font8x8(void);
void vt_fontn(void);
void vt_cls(int x1,int y1,int x2,int y2);
char vt_getatt(void);
void vt_dos_putch(char cc);
void vt_setmode(char nn);
void vt_puts(char *ss);
void vt_printf(char *fmt,...);
void getmem(char num,int x1,int y1,int x2,int y2);
void putmem(char num,int x1,int y1,int x2,int y2);
void hilix(int x1,int y,int sp,unsigned char c);
void hiliy(int x1,int y1,int sp,unsigned char c);
void mlinex(int x1,int y,int sp,unsigned char type);
void mliney(int x1,int y1,int sp,unsigned char type);
void setmwin(int x1,int y1,int x2,int y2);
char getrow(void);
char* putnorton(double d);
void cmenu(int x1,int y1,char *s,char scol,char bcol);
void vt_putchat(int x,int y,char car);
void menutype(char num,char barcol,char scripcol,char hilicol,char selcol);
void setmenuP(char num,char *item,int lett,int (*p)());
int menuto(char num,char mode);
int menusec(char num,char num2,char mode);
void vt_p_author(void);
