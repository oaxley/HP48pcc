/* erreur.c - Gestion des erreurs
   LEGRAND Sebastien - Le 21/02/1996 */

#include "header.h"

void erreur(int no,char *mess,int nb)
{
 switch(no)
 {
  /* Erreur syntaxique */
  case 1   : printf("\nErreur ligne %d : Argument requis.\n",nb);
	break;
  case 2   : printf("\nErreur ligne %d : Taille invalide.\n",nb);
	break;
  case 3   : printf("\nErreur ligne %d : Une adresse comporte 5 quartets.\n",nb);
	break;
  case 4   : printf("\nErreur ligne %d : L'etiquette %s n'existe pas.\n",nb,mess);
	break;
  case 5   : printf("\nErreur ligne %d : La commande %s n'existe pas.\n",nb,mess);
	break;
  /* Erreur systeme general */
  case -1  : printf("\nImpossible d'ouvrir le fichier %s.\n",mess);
	break;
  case -2  : puts("\nImpossible de fermer un fichier.");
	break;
  case -3  : puts("\nNombre d'arguments incorrect.");
	     help2();
	break;
  case -4  : printf("\nCommande incorrect : %s\n",mess);
	     help2();
	break;
  case -5  : puts("\nEspace disque insuffisant.\n");
	break;
  case -6  : puts("\nErreur allocation m‚moire.\n");
	break;
  case -10 : puts("\nImpossible de trouver le fichier HP48PCC.EXE .\n");
	break;
  case -11 : printf("\nImpossible de fixer la version HP48-%c.\n",mess[0]);
	break;
  case -12 : puts("\nImpossible de lire le numero de version.");
	break;
 }

fcloseall();
efface_trace();
libere_label();
libere_goto();
exit(1);
}