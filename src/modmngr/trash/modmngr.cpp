#include "modmngr.h"

#define MODMNGR_STANDALONE

using namespace std;

//Module counter
int ModMngr::mctr = 0;

ModMngr::ModMngr()
{
//   int i;

//   for(i=0; i<MAX_MODULES; i++){
//     tm[i] = NULL;
  tm.id = -1;
//  }
}

ModMngr::~ModMngr() {}

//MODULE *ModMngr::mopen(const char *name, int ninport, int noutport)
int ModMngr::mopen(const char *name, int ninport, int noutport)
{
//   MODULE *p;
//   int i;

   /* verify module not yet been registered */
//   for(i=0; i<MAX_MODULES; i++)
//     if ((tm[i] != NULL) && (!strcmp(tm[i]->name, name)))
   if ((tm.id != -1) && (!strcmp(tm.name, name)))
//     	return NULL;
      return -1;

   /* search for free registration slot */
//   for(i=0; i<MAX_MODULES; i++)
//       if(tm[i] == NULL){
          /* found : alloc memory for a module descriptor and fill it */
//          p = (MODULE*)malloc(sizeof(MODULE));
//          p->id = mctr;
//          strncpy(p->name, name, MODNAME_LENGTH);
//          p->ninport = ninport;
//          p->noutport = noutport;
          /* register module */
//          tm[i] = p;
   tm.id = mctr;
   strncpy(tm.name, name, MODNAME_LENGTH);
   tm.ninport = ninport;
   tm.noutport = noutport;
          cout << "Module \"" << name << "\" succesfully registered with the ID : " << mctr << "\n"; 
          mctr++;
//          return &tm;
   return 0;

   /* error : no free registration slot found */
//   return -1;
}

#ifdef MODMNGR_STANDALONE
int main (int argc, char ** argv)
{
//   MODULE *p, *q;
   int mn1, mn2;
   ModMngr mymngr;


   if ((mn1 = mymngr.mopen("detection", 2, 1)) == -1){
      fprintf(stderr, "Unable to register this module\n");
      exit(EXIT_FAILURE);
   }
   if ((mn2 = mymngr.mopen("controle direction", 2, 2)) == -1){
      fprintf(stderr, "Unable to register this module\n");
      exit(EXIT_FAILURE);
   }
}
#endif
