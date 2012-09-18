int k_x,k_y,openmenu;
union REGS r;
char *getmm[4];
char *spost[4];
char *mansfo,manspr=0,oldmandir=5,mansotto=0;
int percx,manx,many,mancount=0,percount=0,mandir=5;
char *mansx1,*mansx2,*mansx3,*mandx1,*mandx2,*mandx3,*mand1,*mand2,*mand3,*mans1,*mans2,*mans3,*manf;
struct
{
 unsigned char drive;
 unsigned char unit;
 unsigned int bytexsec;
 unsigned char secxclus;
 unsigned char boh;
 unsigned int boot_sec_num;
 unsigned char FAT_num;
 unsigned int root_entries_num;
 unsigned int data_off;
 unsigned int cluster_num;
 unsigned int secxFAT;
 unsigned int root_off;
 unsigned int device_off;
 unsigned int device_seg;
 unsigned char media_byte;
 unsigned char status;
 unsigned int next_off;
 unsigned int next_seg;
 unsigned int boh2[30];
}far *s0;
unsigned int i60seg;
unsigned int i60off;
unsigned int i61seg;
unsigned int i61off;
unsigned int i1cseg;
unsigned int i1coff;
struct SREGS sr;
struct
{
 int x1,y1,x2,y2,gx,gy,gc;
 char title[13],bcol,scol,scolb,riemp;
 int size;
 struct
 {
  char nome[15];
  int lett;
  int (*p)();
  struct
  {
   char nome[15];
   int lett;
   int (*p)();
  }ms[20];
  int MS_count;
 }mp[9];
 int MP_count;
} wi[4];
struct
{
 int active_window;
 int active_p_menu;
 int numdrives;
 char drs[9];
 char drv_light;
 char drs_type[9];
} status;
struct ffblk f,file[400];
void vt_p_author(void);
void mouse(int ax);
int ikey(void);
void vt_setmode(char nn);
void setmwin(int x1,int y1,int x2,int y2);
char getrow(void);
char* putnorton(double d);
process(int(*p)());
void gprintf(char *fmt,...);
void gwindow(int x1,int y1,int x2,int y2,char *s,char scol,char scolb,char bcol,char rcol);
void nogwin(void);
void inizializza(char *nomefile);
int search_idl(char *item,FILE *fp);
void setmenuP(char num,char *s,int lett,int (*p)());
void make_menu(void);
void menuto(void);
int menuto2();
void setmenuS(char numwin,char menp,char *s,int lett,int (*p)());
void controlla (int kd);
void finisci(void);
void draw_5(int x,int y,char lett);
void draw_3(int x,int y,char lett);
void draw_hd(int x,int y,char lett);
void draw_ram(int x,int y,char lett);
void draw_boh(int x,int y,char lett);
void interrupt int1c(void);

#define UP_KEY 72+256
#define DOWN_KEY 80+256
#define SIN_KEY 75+256
#define DEX_KEY 77+256
#define HOME_KEY 71+256
#define PGUP_KEY 73+256
#define END_KEY 79+256
#define PGDWN_KEY 81+256
#define INS_KEY 82+256
#define DEL_KEY 83+256
#define F1_KEY 59+256
#define F2_KEY 60+256
#define F3_KEY 61+256
#define F4_KEY 62+256
#define F5_KEY 63+256
#define F6_KEY 64+256
#define F7_KEY 65+256
#define F8_KEY 66+256
#define F9_KEY 67+256
#define F10_KEY 68+256






