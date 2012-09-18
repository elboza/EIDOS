#include<iaza.h>
FILE *fpin,*fpout;
unsigned char ch;
char filein[255],fileout[255],kkey[255];
int xx,punt,len;
main()
{
 printf("Crypt v 1.0  by Iaza Soft 1990(c)\n");
 printf("\nnome del file:->");
 gets(filein);
 printf("nome del file di uscita:->");
 gets(fileout);
 printf("chiave di codifica:->");
 gets(kkey);
 len=strlen(kkey);
 punt=0;
 fpin=fopen(filein,"rb+");
 if(fpin==NULL) {printf("ERRORE, non riesco ad aprire il file sorgente...\n");exit(1);}
 fpout=fopen(fileout,"wb+");
 if(fpout==NULL) {printf("ERRORE, non riesco ad aprire il file destinazione...\n");exit(1);}
 ch=getc(fpin);
 while(!feof(fpin))
 {
  printf("%c",ch);
  xx=ch^kkey[punt];
  putc(xx,fpout);
  ch=getc(fpin);
  punt++;
  if(punt==len) punt=0;
 }
 fclose(fpin);
 fclose(fpout);
 printf("Fatto.\n");
}
