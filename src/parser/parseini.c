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

#include <stdlib.h>
#include <confini.h>
#include "parseini.h"
//#include <parseini.h>

#define IS_KEY(SECTION, KEY) \
   (ini_array_match(SECTION, disp->append_to, '.', disp->format) && \
   ini_string_match_ii(KEY, disp->data, disp->format))

//static SKV tkv[MAX_SKV];
static SKV *tkv;
static int nvalues;
static int j = 0;

static int callback (IniDispatch * disp, void * v_other) 
{
   int i;

   if (disp->type == INI_KEY) {
      for(i=0; i< nvalues; i++)
         if (IS_KEY(tkv[i].section, tkv[i].key)){
            //printf("callback: index: %d - section:%s - cle:%s -", i, tkv[i].section, tkv[i].key);
            //printf(" Value found: %s\n", disp->value);
            strncpy(tkv[i].value, disp->value, VALUE_LENGTH);
            return 0;
         }
   }
   return 0;
}

/* */
int set_skv(int n, SKV *t)
{
   nvalues = n;
   tkv = t; 
   return 0;
}

int get_skv(SKV *t)
{
   t = tkv;
   return 0;
}

int loadandparse (char *filename) 
{
   if (load_ini_path(filename, INI_DEFAULT_FORMAT, NULL, callback, NULL)) {
      fprintf(stderr, "Sorry, something went wrong :-(\n");
      return 1;
   }
   return 0;
}
