/*==================================================*/
/*
Ceci est une surcouche à la libraire confini.
Elle offre:
1) une interface entre le code C++ d' une application et la librairie confini qui est en C
2) une API très simple pour récupérer les valeurs d'un fichier .ini en fournissant des paires <section, clé>

Fichiers requis : 
==>parseini.h
==>inimngr.h

==>parseini.c à compiler obligatoirement avec gcc
gcc -c parseini.c -o parseini.o

==>scavini.cpp à compiler obligatoirement avec g++
g++ -c inimngr.cpp -o inimngr.o

==> votre application en C++: par exemple: monappli.cpp à compiler et lier comme suit:
g++ monappli.cpp parsini.o inimngr.o -o monappli -lconfini

Bien sur, il faut avoir installé et activé la librairie confini:
https://madmurphy.github.io/libconfini/html/index.html

*/
/*==================================================*/

#include "inimngr.h"

using namespace std; 

ScavIni::ScavIni(const char *filename, const SK *t, int n)
{
   const char *s, *k;
   SK sk;

   inifile = filename;
   for(int i = 0; i<MAX_SKV; i++)
      tkv[i].value[0] = 0;
   askcounter = 0;
   nvalues = n;
   //traitement des sections et clés
   for (int i=0; i < n; i++)
      askvalue(t[i].section, t[i].key);
   // parse
   set_skv(nvalues, tkv);
   loadandparse(filename);
   get_skv(tkv);
}

ScavIni::~ScavIni(){}

int ScavIni::askvalue(const char *section, const char *key)
{
   if(askcounter >= nvalues){
      fprintf(stderr, "%s: cannot ask more than %d nvalue", nvalues);
      return EXIT_FAILURE;
   }
   strncpy(tkv[askcounter].section, section, SECTION_LENGTH);
   strncpy(tkv[askcounter].key, key, KEY_LENGTH);
   askcounter++;
   return EXIT_SUCCESS;
}

int ScavIni::getvalue(const SK *sk, char *value)
{

  int i;
  char source[SECTION_LENGTH+KEY_LENGTH+1], target[SECTION_LENGTH+KEY_LENGTH+1];

  strncpy(target, sk->section, SECTION_LENGTH);
  strncat(target, sk->key, KEY_LENGTH);
  for(i=0; i<MAX_SKV; i++){
    strncpy(source, tkv[i].section, SECTION_LENGTH);
    strncat(source, tkv[i].key, KEY_LENGTH);
    //printf("getvalue:target: %s - source: %s\n", target, source);
    if(!strncmp(source, target, SECTION_LENGTH+KEY_LENGTH)){
       if(tkv[i].value[0] == 0) continue;
       strncpy(value, tkv[i].value, VALUE_LENGTH);
       return EXIT_SUCCESS;
    }
 }
  return EXIT_FAILURE;
}

/*
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
*/
