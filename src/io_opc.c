/* io_opc.c - Gestion des entrees / sorties avec le fichier opcode
   LEGRAND Sebastien - Le 21/02/1996 */

#include "header.h"

FILE *fichier_opcode;
char instruction[40],opcode[40];

void ouvre_opcode( void )
{
fichier_opcode=ouvre_fichier(searchpath("SATURN.OPC"),"rt");
}

void lis_commande(unsigned pos_commande[],int occur[])
{
int i;
char cmd,lettre;
int position,occ;

deplace_pointeur(170,fichier_opcode);

for(i=0;i<=13;++i)
{
 fscanf(fichier_opcode,"%c %c %d %u\n",&cmd,&lettre,&occ,&position);
 pos_commande[lettre]=position;
 occur[lettre]=occ;
}
}

void deplace_opc(unsigned pos)
{
deplace_pointeur(pos,fichier_opcode);
}

char *donne_instr( void )
{
return ( instruction );
}

char *donne_opc( void )
{
return ( opcode );
}

void reset_opc( void )
{
deplace_pointeur(365,fichier_opcode);
}

void initialise_opc( unsigned commande[], int occur[] )
{
ouvre_opcode();
lis_commande(commande,occur);
reset_opc();
}

int lit_opcode(void)
{
char chaine[80],*ptr;
int i,j,len;

if (fgets(chaine,80,fichier_opcode) == NULL)
 return FALSE;

len=strlen(chaine);
i=0;j=0;
ptr=instruction;
while (i <= len)
{
 if (chaine[i] == 'ø')
 {
  instruction[j]='\0';
  ptr=opcode;
  j=0;
 }
 else
 {
  ptr[j]=chaine[i];
  j++;
 }
 i++;
}

ptr[j-2]='\0';
return TRUE;
}

void test(void)
{
int i;
char chaine[80];

printf("Position A:%u\n",posit_cmd['A']);
deplace_pointeur(posit_cmd['A'],fichier_opcode);
//for (i=0;i< occur_cmd['A'];i++)
{
 printf("cmd -> %s ",fgets(chaine,80,fichier_opcode));
}
}