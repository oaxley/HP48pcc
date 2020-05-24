/* filtres.c - Fichier contenant tous les filtres
   LEGRAND Sebastien - Le 21/02/1996 */

#include "header.h"

void filtre_rem(FILE *in)
{
FILE *tmp;
char chaine[80],dest[80];
int i;

tmp=fopen("$$hp48$$.tmp","wt");
if (tmp == NULL)
 erreur(-5,NULL,0);

while(fgets(chaine,80,in) != NULL)
{
 memset(dest,0,80);
 strcpy(chaine,filtre_espace(chaine));

 if (chaine[0] != '%')
 {
  i=0;
  while ( (chaine[i] != '%') && (i < strlen(chaine)) )
  {
   dest[i]=chaine[i];
   i++;
  }
 }
 else
  strcpy(dest,"\n");

 if ( (strlen(dest) > 1) && (dest[i-1] != 0x0A) )
  strcat(dest,"\n");
 else
  dest[i]='\0';

 strcpy(dest,filtre_espfin(dest));

 fputs(dest,tmp);
 if (dest[0] == '*')
  ajoute_label(dest);
}

ferme_fichier(in);
ferme_fichier(tmp);
in=ouvre_fichier("$$hp48$$.tmp","rt");

}

/* Enleve les espaces, les tabulations superflus et convertit en majuscules */
char *filtre_espace(char *ch)
{
int len,i,j;
char fmt[80];

memset(fmt,'\0',80);

len=strlen(ch);
i=0;
while( (ch[i] == ' ' || ch[i] == 0x09) && (i < len))
 i++;

if (i < len)
{
 for (j=i;j<len;++j)
  fmt[j-i]=ch[j];
}
strcpy(fmt,strupr(fmt));
return ( (char *)fmt );
}

char *filtre_espfin(char *ch)
{
char fmt[40];
int len,i;

len=strlen(ch);
strcpy(fmt,ch);
i=len-2;
if (i > 2)
{
 while (fmt[i] == ' ')
 {
  fmt[i]='\n';
  fmt[i+1]='\0';
  i--;
 }
}
return (char *)fmt;
}