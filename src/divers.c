/* divers.c - Fichier contenant la fonction d'aide & d'information
   LEGRAND Sebastien - le 21/06/1996 */
#include "header.h"

/* Affiche l'information au debut du programme */
void info(void)
{
int version;

version=donne_version();
printf("HP48G/GX - PC Compiler / LEGRAND Sebastien - Version: HP48-%c\n",version);
}

/* Aide sur l'aide */
void help2(void)
{
puts("\nTapez HP48PCC /? pour l'aide compl‚te.");
}

/* Affiche l'aide */
void help(void)
{
puts("\nSyntaxe : HP48PCC [/V:x] [/?] <source> <destination>");
puts("\nsource      : Nom du fichier ascii contenant le programme HP48");
puts("destination : Nom du fichier HP48 (extension par defaut .COD)");

puts("\noption :");
puts("/?   : Affiche cet aide");
puts("/V:x : Change la version de la HP48 (version M d'origine)");
exit(0);
}