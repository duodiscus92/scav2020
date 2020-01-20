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
#include <iostream>
#include "parseini.h"

extern "C"
{
  int loadandparse(const char *filename);
  int set_skv(int nvalue, SKV *t);
  int get_skv(SKV *t);
}

class ScavIni
{

public:
   ScavIni(const char *filename, const SK *t, int n);
   ~ScavIni();
   int getvalue(const SK *sk, char *value);

private:
   const char *inifile;
   int nvalues;
   int askcounter = 0;
   SKV tkv[MAX_SKV];
   int askvalue(const char *section, const char *key);
};
