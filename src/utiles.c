/* utiles.c - Fichier contenant les fonctions utilitaires
   LEGRAND Sebastien - le 21/02/1996 */

/* Librairie */
#include "header.h"

FILE *in,*out;

/* change la version de la HP */
int change_version(char version)
{
FILE *safe;
char *tmp="0";

tmp[0]=version;

safe=fopen(searchpath("HP48PCC.EXE"),"r+b");
if (safe == NULL)
 erreur(-10,NULL,0);

fseek(safe,-1L,SEEK_END);

if (fputc(version,safe) == EOF)
 erreur(-11,tmp,0);

fclose(safe);
return 0;
}

/* renvoit le numero de version */
int donne_version(void)
{
int version;
FILE *safe;

safe=fopen(searchpath("HP48PCC.EXE"),"rb");
if (safe == NULL)
 erreur(-10,NULL,0);

fseek(safe,-1L,SEEK_END);

if ((version=fgetc(safe)) == EOF)
 erreur(-12,NULL,0);

return version;
}


/* recherche un motif dans une chaine, renvoit TRUE si trouv‚ */
int str_cherche(char *chaine,char *motif)
{
int len_motif,len_chaine,i,k;

len_chaine=strlen(chaine);
len_motif =strlen(motif);

for (i=0,k=0;i < len_chaine;++i)
{
 if (chaine[i] == motif[k])
 {
  do
  {
   i++;
   k++;
  } while (chaine[i] == motif[k]);

  if (k >= len_motif)
   return TRUE;

  if (i >= len_chaine)
   return FALSE;

  k=0;
 }
}

return FALSE;
}

/* cette fonction analyse les parametres passes … main */
void analyse(int nb_arg,char *arg[])
{
int i;
char *tmp;

if (nb_arg == 1 || nb_arg > 3)
 erreur(-3,NULL,0);

if (nb_arg == 2)
{
 strcpy(arg[1],strupr(arg[1]));

 if (strcmp(arg[1],"/?") == 0)
  help();
 else
  if (strncmp(arg[1],"/V:",2) == 0)
  {
   strcpy(tmp,arg[1]);
   change_version(tmp[3]);
   printf("\nNouvelle version: HP48-%c\n",tmp[3]);
   exit(0);
  }
  else
   erreur(-4,arg[1],0);
}

strcpy(arg[1],strupr(arg[1]));
strcpy(arg[2],strupr(arg[2]));

in=ouvre_fichier(arg[1],"rt");
out=ouvre_fichier(arg[2],"wb");
fputs("HPHP48-",out);
fputc(donne_version(),out);

}

FILE *get_in_file( void )
{
return (in);
}

FILE *get_out_file( void )
{
return (out);
}

char convert2hexa(int nb)
{
char retour;

if (nb >= 0 && nb <= 9)
 retour=nb+'0';
else
 if (nb >= 10 && nb <= 15)
  retour=nb+55;

return retour;
}

int  hexa2nombre(char ch[])
{
int i,d,somme;

somme=0;
for (i=0;i<=1;++i)
{
 if (ch[i] >= 'A' && ch[i] <= 'F')
  d=ch[i]-55;
 else
  if (ch[i] >= '0' && ch[i] <= '9')
   d=ch[i]-48;

 if (i==0)
  d=d*16;

 somme=somme+d;
}
return somme;
}

void efface_trace(void)
{
unlink("$$hp48$$.tmp");
unlink("$$code$$.tmp");
}

void compose(void)
{
FILE *safe;
long taille;
char chaine[5],prologue[]="CCD20",total[10];
int i,imp;

safe=ouvre_fichier("$$code$$.tmp","rt");

strcpy(total,prologue);
taille=taille_fichier(safe);
taille+=5; /* Longueur de l'objet */
sprintf(chaine,"%00005X",taille);
strcpy(chaine,strrev(chaine));
strcat(total,chaine);

for (i=0;i < 10;i+=2)
{
 chaine[1]=total[i];
 chaine[0]=total[i+1];
 fputc(hexa2nombre(chaine),out);
}

taille-=5;
/* taille du fichier impaire / paire */
if (taille % 2 == 0)
 imp=FALSE;
else
 imp=TRUE;

if (imp == TRUE)
 taille--;

for (i=0;i < taille;i+=2)
{
 chaine[1]=fgetc(safe);
 chaine[0]=fgetc(safe);
 fputc(hexa2nombre(chaine),out);
}

if (imp == TRUE)
{
 chaine[1]=fgetc(safe);
 chaine[0]='0';
 fputc(hexa2nombre(chaine),out);
}
fcloseall();
}