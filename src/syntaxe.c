/* syntaxe.c - Analyseur de syntaxe
   LEGRAND Sebastien - Le 21/02/1996 */

#include "header.h"

char chaine_opcode[20];

/* operation speciale necessitant un traitement particulier */
char *special[22]={ "LA ",
		    "LAHEX ",
		    "LC ",
		    "LCHEX ",
		    "GOC ",
		    "GOLONG ",
		    "GONC ",
		    "GOSBVL ",
		    "GOSUB ",
		    "GOSUBL ",
		    "GOTO ",
		    "GOVLNG ",
		    "GOYES ",
		    "D0=(2) ",
		    "D0=(4) ",
		    "D0=(5) ",
		    "D0= ",
		    "D1=(2) ",
		    "D1=(4) ",
		    "D1=(5) ",
		    "D1= ",
		    "$ " };

/* retourne la chaine opcode */
char *give_opcode(void)
{
return (chaine_opcode);
}

/* analyse la syntaxe
   retour : =0 l'operation … reussie -> chaine_opcode contient la chaine
	    =1 la chaine etait un blanc de conservation de lignes
	    =<0 erreur directement expoitable / gestionnaire d'erreur */

void syntaxe(char *chaine,unsigned ligne)
{
int len_code,i,j,ret,occur;
unsigned long pos;
char left[20],right[20];
label *tmp;

memset(chaine_opcode,'\0',20);

i=0;
while (i < 22)
{
 if (str_cherche(chaine,special[i]) == TRUE)
  break;
 i++;
}

if (i < 22) /* on a trouv‚ un mot-clef … traitement special */
{
 //puts("commande speciale.");
 ret=separe(chaine,left,right);
 if (ret != 0)
  erreur(1,NULL,ligne);
 len_code=strlen(right);

 switch (i)
 {
  case 0 : /* LA */
  case 1 : /* LAHEX */
	   ret=convert2hexa(len_code);
	   strcpy(chaine_opcode,"8082");
	   chaine_opcode[4]=ret-1;
	   strcpy(right,strrev(right));
	   strcat(chaine_opcode,right);
	   return;
  case 2 : /* LC */
  case 3 : /* LCHEX */
	   ret=convert2hexa(len_code);
	   strcpy(chaine_opcode,"3");
	   chaine_opcode[1]=ret-1;
	   strcpy(right,strrev(right));
	   strcat(chaine_opcode,right);
	   return;
  case 4 : /* GOC */
	   if (cherche_label(right,&tmp) == FALSE)
	    erreur(4,right,ligne);
	   strcpy(chaine_opcode,"4**");
	   ajoute_goto(tmp,i);
	   return;
  case 5 : /* GOLONG */
	   if (cherche_label(right,&tmp) == FALSE)
	    erreur(4,right,ligne);
	   strcpy(chaine_opcode,"8C****");
	   ajoute_goto(tmp,i);
	   return;
  case 6 : /* GONC */
	   if (cherche_label(right,&tmp) == FALSE)
	    erreur(4,right,ligne);
	   strcpy(chaine_opcode,"5**");
	   ajoute_goto(tmp,i);
	   return;
  case 7 : /* GOSBVL */
	   if (len_code != 5)
	    erreur(3,NULL,ligne);

	   strcpy(chaine_opcode,"8F");
	   strcpy(right,strrev(right));
	   strcat(chaine_opcode,right);
	   return;
  case 8 : /* GOSUB */
	   if (cherche_label(right,&tmp) == FALSE)
	    erreur(4,right,ligne);
	   strcpy(chaine_opcode,"7***");
	   ajoute_goto(tmp,i);
	   return;
  case 9 : /* GOSUBL */
	   if (cherche_label(right,&tmp) == FALSE)
	    erreur(4,right,ligne);
	   strcpy(chaine_opcode,"8E****");
	   ajoute_goto(tmp,i);
	   return;
  case 10: /* GOTO */
	   if (cherche_label(right,&tmp) == FALSE)
	    erreur(4,right,ligne);
	   strcpy(chaine_opcode,"6***");
	   ajoute_goto(tmp,i);
	   return;
  case 11: /* GOVLNG */
	   if (len_code != 5)
	    erreur(3,NULL,ligne);

	   strcpy(chaine_opcode,"8D");
	   strcpy(right,strrev(right));
	   strcat(chaine_opcode,right);
	   return;
  case 12: /* GOYES */
	   if (cherche_label(right,&tmp) == FALSE)
	    erreur(4,right,ligne);
	   strcpy(chaine_opcode,"**");
	   ajoute_goto(tmp,i);
	   return;
  case 13: /* D0=(2) */
	   if (len_code != 2)
	    erreur(2,NULL,ligne);

	   strcpy(chaine_opcode,"19");
	   strcpy(right,strrev(right));
	   strcat(chaine_opcode,right);
	   return;
  case 14: /* D0=(4) */
	   if (len_code != 4)
	    erreur(2,NULL,ligne);

	   strcpy(chaine_opcode,"1A");
	   strcpy(right,strrev(right));
	   strcat(chaine_opcode,right);
	   return;
  case 15: /* D0=(5) */
	   if (len_code != 5)
	    erreur(2,NULL,ligne);

	   strcpy(chaine_opcode,"1B");
	   strcpy(right,strrev(right));
	   strcat(chaine_opcode,right);
	   return;
  case 16: /* D0= */
	   if ( (len_code != 2) && (len_code != 4) && (len_code != 5) )
	    erreur(2,NULL,ligne);

	   if (len_code == 2)
	    strcpy(chaine_opcode,"19");
	   if (len_code == 4)
	    strcpy(chaine_opcode,"1A");
	   if (len_code == 5)
	    strcpy(chaine_opcode,"1B");

	   strcpy(right,strrev(right));
	   strcat(chaine_opcode,right);
	   return;
  case 17: /* D1=(2) */
	   if (len_code != 2)
	    erreur(2,NULL,ligne);

	   strcpy(chaine_opcode,"1D");
	   strcpy(right,strrev(right));
	   strcat(chaine_opcode,right);
	   return;
  case 18: /* D1=(4) */
	   if (len_code != 4)
	    erreur(2,NULL,ligne);

	   strcpy(chaine_opcode,"1E");
	   strcpy(right,strrev(right));
	   strcat(chaine_opcode,right);
	   return;
  case 19: /* D1=(5) */
	   if (len_code != 5)
	    erreur(2,NULL,ligne);

	   strcpy(chaine_opcode,"1F");
	   strcpy(right,strrev(right));
	   strcat(chaine_opcode,right);
	   return;
  case 20: /* D1= */
	   if ( (len_code != 2) && (len_code != 4) && (len_code != 5) )
	    erreur(2,NULL,ligne);

	   if (len_code == 2)
	    strcpy(chaine_opcode,"1D");
	   if (len_code == 4)
	    strcpy(chaine_opcode,"1E");
	   if (len_code == 5)
	    strcpy(chaine_opcode,"1F");

	   strcpy(right,strrev(right));
	   strcat(chaine_opcode,right);
	   return;
  case 21: /* $ -> CON(x) */
	   strcpy(chaine_opcode,right);
	   return;
 }
}

//puts("commande normale.");
pos=posit_cmd[chaine[0]];
occur=occur_cmd[chaine[0]];
deplace_opc(pos);
i=0;
ret=FALSE;
while ((i < occur) && (ret == FALSE))
{
 lit_opcode();

 if (strcmp(chaine,donne_instr()) == 0)
 {
  strcpy(chaine_opcode,donne_opc());
  ret=TRUE;
 }
 i++;
}
if (ret == FALSE)
 erreur(5,chaine,ligne);

}

/* separateur de champ : DAT0=A A -> DAT0=A & A */

int separe(char *chaine,char *left,char *right)
{
int chaine_len,i,k;
char *pointeur,c;

pointeur=left;
chaine_len=strlen(chaine);

for (i=0,k=0;i< chaine_len;i++)
{
 c=chaine[i];
 if (c == ' ')
 {
  left[k]='\0';
  k=0;
  pointeur=right;
 }
 else
 {
  pointeur[k]=c;
  k++;
 }
}
pointeur[k]='\0';
if (strlen(left) == chaine_len)
 return 1;

return 0;
}

void compile( void )
{
char chaine[80];
int ligne=1,len,ret;
long adresse1,adresse2,lg_saut;
FILE *fichier_code;
gotopos *gtp;

fichier_code=ouvre_fichier("$$code$$.tmp","wt");

program_counter=0;
while(fgets(chaine,80,get_in_file()) != NULL)
{
 printf("Compilation... ligne %d\r",ligne);
 len=strlen(chaine);
 if (len > 1)
 {
  chaine[len-1]='\0';

  if (chaine[0] != '*')
  {
   syntaxe(chaine,ligne);
   fputs(give_opcode(),fichier_code);
   program_counter+=strlen(give_opcode());
  }
  else
   insert_posi_label(&chaine[1],program_counter);
 }
ligne++;
}
fclose(fichier_code);

/* ici on resout les problemes de sauts */
fichier_code=ouvre_fichier("$$code$$.tmp","r+t");
puts("");
gtp=goto_one;
if (gtp != NULL)  /* si la chaine n'est pas vide -> presence de saut */
{
 do
 {
  ptr_goto=gtp->next;
  adresse1=gtp->position;
  adresse2=(gtp->reference)->position;
  ret=gtp->type_goto;
  switch(ret)
  {
   case 4  : /* GOC */
	     deplace_pointeur(adresse1+1,fichier_code);
	     lg_saut=adresse2-(adresse1+1);
	     len=2; /* longueur du deplacement */
	break;
   case 5  : /* GOLONG */
	     deplace_pointeur(adresse1+2,fichier_code);
	     lg_saut=adresse2-(adresse1+2);
	     len=4;
	break;
   case 6  : /* GONC */
	     deplace_pointeur(adresse1+1,fichier_code);
	     lg_saut=adresse2-(adresse1+1);
	     len=2;
	break;
   case 8  : /* GOSUB */
	     deplace_pointeur(adresse1+1,fichier_code);
	     lg_saut=adresse2-(adresse1+4); /* +4 -> largeur de gosub */
	     len=3;
	break;
   case 9  : /* GOSUBL */
	     deplace_pointeur(adresse1+2,fichier_code);
	     lg_saut=adresse2-(adresse1+6);
	     len=4;
	break;
   case 10 : /* GOTO */
	     deplace_pointeur(adresse1+1,fichier_code);
	     lg_saut=adresse2-(adresse1+1);
	     len=3;
	break;
   case 12 : /* GOYES */
	     deplace_pointeur(adresse1,fichier_code);
	     lg_saut=adresse2-adresse1;
	     len=2;
	break;
  }

  memset(chaine,'\0',80);
  sprintf(chaine,"%003X",lg_saut);
  ligne=strlen(chaine);
  for (ret=0;ret < len;ret++)
   fputc(chaine[ligne-ret-1],fichier_code);

  gtp=ptr_goto;
 } while (gtp != NULL);
}
fclose(fichier_code);
}