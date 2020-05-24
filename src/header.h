/* HEADER.H - Fichier header contenant les constantes
   LEGRAND Sebastien - le 21/02/96 */

#ifndef H_HEADER

/* Definition des constantes */
#define H_HEADER
#define TRUE 1
#define FALSE 0

/* Librairie necessaire au projet */
#include <stdio.h>
#include <process.h>
#include <dir.h>
#include <string.h>

/* definition de la structure des labels */
struct label {
	      char name[40];
	      unsigned long position;
	      struct label *next;
	     };

typedef struct label label;

struct gotopos {
		unsigned long position;
		int type_goto;
		struct label *reference;
		struct gotopos *next;
	       };

typedef struct gotopos gotopos;

/* Compteur de programme & co*/
extern unsigned long program_counter;
extern unsigned posit_cmd[256];
extern int occur_cmd[256];
extern label *etiquette;
extern label *ptr_courant;
extern gotopos *goto_one;
extern gotopos *ptr_goto;

/* Prototype des fonctions */

/* divers.c */
void info(void);
void help2(void);
void help(void);

/* utiles.c */
int change_version(char version);
int donne_version(void);
int str_cherche(char *chaine,char *motif);
void analyse(int nb_arg,char *arg[]);
FILE *get_in_file( void );
FILE *get_out_file( void );
char convert2hexa(int nb);
int  hexa2nombre(char ch[]);
void compose(void);
void efface_trace(void);

/* io.c */
FILE *ouvre_fichier(char *name,char *mode);
void ferme_fichier(FILE *safe);
long taille_fichier(FILE *safe);
int deplace_pointeur(unsigned position,FILE *safe);

/* io_opc */
void ouvre_opcode( void );
void lis_commande(unsigned pos_commande[],int occur[]);
char *donne_instr( void );
char *donne_opc( void );
void reset_opc( void );
void initialise_opc( unsigned commande[],int occur[] );
int lit_opcode(void);
void deplace_opc(unsigned pos);

/* erreur.c */
void erreur(int no,char *mess,int nb);

/* filtres.c */
void filtre_rem(FILE *in);
char *filtre_espace(char *ch);
char *filtre_espfin(char *ch);

/* syntaxe.c */
char *give_opcode(void);
void syntaxe(char *chaine,unsigned ligne);
int separe(char *chaine,char *left,char *right);
void compile( void );

/* pointeur.c */
void ajoute_label(char *nom);
void libere_label(void);
int cherche_label(char *nom,label **posit);
void insert_posi_label(char *nom,unsigned long pos);
label *get_debut_label(void);
void ajoute_goto(label *pointeur,int type);
void libere_goto(void);
#endif