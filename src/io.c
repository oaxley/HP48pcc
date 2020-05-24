/* io.c - Gestion des entr‚es / sorties sur les fichiers
   LEGRAND Sebastien - Le 21/02/1996 */

#include "header.h"

FILE *ouvre_fichier(char *name,char *mode)
{
FILE *t;

t=fopen(name,mode);
if (t == NULL)
 erreur(-1,name,0);

return t;
}

void ferme_fichier(FILE *safe)
{
if (fclose(safe))
 erreur(-2,NULL,0);
}

long taille_fichier(FILE *safe)
{
long pos_courant,taille;

pos_courant=ftell(safe);
fseek(safe,0L,SEEK_END);
taille=ftell(safe);
fseek(safe,pos_courant,SEEK_SET);

return taille;
}

int deplace_pointeur(unsigned position,FILE *safe)
{
return ( fseek(safe,position,SEEK_SET) );
}