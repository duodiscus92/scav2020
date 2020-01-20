/*==================================================*/
/*
Ceci est une surcouche à la libraire confini.
Elle offre:
1) une interface entre le code C++ d' une application et la librairie confini qui est en C
2) une API très simple pour récupérer les valeurs d'un fichier .ini en fournissant des paires <section, clé>

Fichier requis : 
==>scavini.h
==>parseini.h

==>confini.c à compiler obligatoirement avec gcc
gcc -c parseini.c -o parse.o

==>scavini.cpp à compiler obligatoirement avec g++
g++ -c scavini.cpp -o scavini.o

==> votre application en C++: par exemple: monappli.cpp à compiler et lier comme suit:
g++ monappli.cpp parse.o scavini.o -o monappli -lconfini

Bien sur, il faut avoir installé et activé la librairie confini:
https://madmurphy.github.io/libconfini/html/index.html

*/
/*==================================================*/

#include <string.h>

#define SECTION_LENGTH 50
#define KEY_LENGTH 50
#define VALUE_LENGTH 20
#define MAX_SKV 100
#define MAX_PATH 80


typedef struct sk{
   const char *section;
   const char *key;
}SK;

//section, key, velue type definition
typedef struct skv{
   char section[SECTION_LENGTH];
   char key[KEY_LENGTH];
   char value[VALUE_LENGTH];
}SKV;

