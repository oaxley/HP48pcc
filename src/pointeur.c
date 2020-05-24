/* POINTEUR.C - Fichier contenant les fonctions pour les labels
   LEGRAND Sebastien - le 21/02/96 */

#include <alloc.h>
#include "header.h"

label *etiquette=NULL,*ptr_courant=NULL;
gotopos *goto_one=NULL,*ptr_goto=NULL;

/* ajoute une etiquette … la liste */
void ajoute_label(char *nom)
{
label *tmp;
int len;

tmp=(label *)malloc(sizeof(label));
if (tmp == NULL)
 erreur(-6,NULL,0);

strncpy(tmp->name,&nom[1],40);

len=strlen(tmp->name);
if (tmp->name[len-1] == 0x0A)
 tmp->name[len-1]='\0';

tmp->position=0L;
tmp->next=NULL;

if (etiquette == NULL)
{
 etiquette=tmp;
 ptr_courant=tmp;
}
else
{
 ptr_courant->next=tmp;
 ptr_courant=tmp;
}

}

/* libere la memoire occup‚e par la liste */
void libere_label(void)
{
label *tmp;

tmp=etiquette;
if (tmp != NULL)
{
 do
 {
  ptr_courant=tmp->next;
  free(tmp);
  tmp=ptr_courant;
 } while (ptr_courant != NULL);
 etiquette=NULL;
 ptr_courant=NULL;
}
}

/* cherche un label dans la chaine des labels
   si trouve renvoit TRUE et un pointeur sur l'objet */
int cherche_label(char *nom,label **posit)
{
label *tmp;
int retour=FALSE;

tmp=etiquette;
do
{
 if (strncmp(nom,tmp->name,40) == 0)
  retour = TRUE;
 else
  tmp=tmp->next;
} while ( (tmp->next != NULL) && (retour==FALSE) );

if (retour == FALSE)
 if (strncmp(nom,tmp->name,40) == 0)
  retour=TRUE;

*posit=tmp;
return retour;
}

/* Insere au label nom la position passe en argument */
void insert_posi_label(char *nom,unsigned long pos)
{
label *tmp;

if (cherche_label(nom,&tmp) != FALSE)
 tmp->position=pos;
}

/* donne le debut de la chaine */
label *get_debut_label(void)
{
return (label *)etiquette;
}

/* ajoute un goto … la chaine des goto */
void ajoute_goto(label *pointeur,int type)
{
gotopos *tmp;

tmp=(gotopos *)malloc( sizeof(gotopos) );
if (!tmp)
 erreur(-6,NULL,0);

tmp->position=program_counter;
tmp->type_goto=type;
tmp->reference=pointeur;
tmp->next=NULL;

if (goto_one == NULL)
{
 goto_one=tmp;
 ptr_goto=tmp;
}
else
{
 ptr_goto->next=tmp;
 ptr_goto=tmp;
}

}

/* libere la chaine des goto */
void libere_goto(void)
{
gotopos *tmp;

tmp=goto_one;
if (tmp != NULL)
{
 do
 {
  ptr_goto=tmp->next;
  free(tmp);
  tmp=ptr_goto;
 } while (tmp != NULL);
 goto_one=NULL;
 ptr_goto=NULL;
}
}

