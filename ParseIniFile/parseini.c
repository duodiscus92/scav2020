#include <stdlib.h>
#include <confini.h>
#include "parseini.h"

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
