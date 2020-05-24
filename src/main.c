/* main.c - Fichier contenant le programme principal
   LEGRAND Sebastien - le 21/02/1996 */

/* Librairie */
#include "header.h"

unsigned long program_counter;
unsigned posit_cmd[256]={0};
int occur_cmd[256]={0};

int main(int argc,char *argv[])
{
label *lbl;
gotopos *gtp;

info();
analyse(argc,argv);
initialise_opc(posit_cmd,occur_cmd);

puts("");
filtre_rem( get_in_file() );

compile();
compose();

efface_trace();
fcloseall();
libere_label();
libere_goto();

return 0;
}
