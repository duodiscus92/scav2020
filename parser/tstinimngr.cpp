#include "inimngr.h"
int main ()
{

   char value[VALUE_LENGTH];

   //déclarer les sections et les clés dont on veut les valeurs
   const SK sk1 = {"module1", "name"}, sk2 = {"module2", "name"}, sk3 = {"module1.inport1", "idx"}, sk4 = {"module1", "ninport"}, sk5 = {"module1", "noutport"};

   // les mettre dans un tableau
   const SK tsk[]={sk1, sk2, sk3, sk4, sk5};

   // on pourrait se passer de déclarer les sk1, sk2 etc et déclarer comme ci-dessous directeuement 
   //const SK tsk[]={ {"module1", "name"},{"module2", "name"}, {"module1.inport1", "idx"}, {"module1", "ninport"} , {"module1", "noutport"} };

   // toujours déclarer un objet de la classe ScavIni comme ci-dessous
   ScavIni sci ("scav.ini", tsk, sizeof(tsk)/sizeof(SK));

   // y a plus qu'a récupérer les valeurs par exemple avec cette boucle ou tout autre façon
   for (int i=0; i<sizeof(tsk)/sizeof(SK); i++)
      if (sci.getvalue(&tsk[i], value) == EXIT_SUCCESS)
         fprintf(stderr, "Section: %s - Clé:%s - Valeur:%s\n", tsk[i].section, tsk[i].key, value); 
      else
         fprintf(stderr, "Section: %s- Key: %s not found\n", tsk[i].section, tsk[i].key);

   return 0;
}
