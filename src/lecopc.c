#include <stdio.h>

main()
{
FILE *safe;
char *ch;
long pos;

safe=fopen("saturn.opc","rt");
fseek(safe,0L,SEEK_SET);
pos=ftell(safe);
while ( fgets(ch,80,safe) != NULL)
{
 clrscr();
 printf("POS=%ld\n",pos);
 printf("%s",ch);
 if (getch() == 27)
  return 0;
 pos=ftell(safe);
}
fclose(safe);
return 0;
}