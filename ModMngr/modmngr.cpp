#include "modmngr.h"

#define MODMNGR_STANDALONE

using namespace std;

//Module counter
int ModMngr::mctr = 0;		// module counter (obsolete)
int ModMngr::ipctr = 0;		// inport counter
int ModMngr::opctr = 0;		// outport counter
int ModMngr::pid = 0;		// port logical id

ModMngr::ModMngr()
{
   int i;

   tm.id = -1;
   for(i = 0; i < MAX_OUTPORT; i++)
      tm.outport[i] = NULL;
   for(i = 0; i < MAX_INPORT; i++)
      tm.inport[i] = NULL;
}

ModMngr::~ModMngr() {}

// register a module
int ModMngr::mopen(const char *name, int ninport, int noutport)
{

   // verify module not yet been registered
   if (tm.id == -1){
      tm.id = mctr;
      strncpy(tm.name, name, MODNAME_LENGTH);
      tm.ninport = ninport;
      tm.noutport = noutport;
      cerr << "Module \"" << name << "\" succesfully registered with the ID : " << mctr << "\n"; 
      mctr++;
      return tm.id;
   }
   else{
      cerr << "Module \"" << name << "\" not registered with as tm.id :" << tm.id << "\n"; 
      return -1;
   }
}

// create a CAN outport 
int ModMngr::opcreat(const char *name, const char *unit, unsigned char length)
{
   PORT *p;

   if (opctr >=  MAX_OUTPORT){
      return -1;
      cerr << "Unable to create outport \"" << name << "\" in module \"" << tm.name <<  "\" : max outport already opened\n";
   }

   p = (PORT*) malloc(sizeof(PORT));
   p->id = opctr;
   strncpy(p->name, name, PORTNAME_LENGTH);
   strncpy(p->unit, unit, UNITDEF_LENGTH);
   p->length = length;
   p->direction = OUT;
   tm.outport[opctr] = p;
   cerr << "Outport \"" << name << "\" in module \"" << tm.name <<  "\" created\n";
   return opctr++;
}

// create a CAN inport 
int ModMngr::ipcreat(const char *name, const char *unit, unsigned char length)
{
   PORT *p;

   if (ipctr >=  MAX_INPORT){
      return -1;
      cerr << "Unable to create inport \"" << name << "\" in module \"" << tm.name <<  "\" : max inport already opened\n";
   }

   p = (PORT*) malloc(sizeof(PORT));
   p->id = ipctr;
   strncpy(p->name, name, PORTNAME_LENGTH);
   strncpy(p->unit, unit, UNITDEF_LENGTH);
   p->length = length;
   p->direction = OUT;
   tm.inport[ipctr] = p;
   cerr << "Inport \"" << name << "\" in module \"" << tm.name <<  "\" created\n";
   return ipctr++;
}

char *ModMngr::getMname(void)
{
   return tm.name;
}

char *ModMngr::getOpname(unsigned char index)
{
   return tm.outport[index]->name;
}

char *ModMngr::getIpname(unsigned char index)
{
   return tm.inport[index]->name;
}

#ifdef MODMNGR_STANDALONE
int main (int argc, char ** argv)
{
//   MODULE *p, *q;
   int mn1, mn2, p1, p2;
   ModMngr mymngr;

   // test of module registration
   if ((mn1 = mymngr.mopen("detection", 2, 1)) == -1){
      fprintf(stderr, "Unable to register the module\"detection\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cout << "Module \"" << mymngr.getMname() << "\" succesfully registered with the ID : " << mn1 << "\n"; 
/*
   if ((mn2 = mymngr.mopen("controle direction", 2, 2)) == -1){
      fprintf(stderr, "Unable to register the module \"controle direction\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cout << "Module \"" << mymngr.getMname() << "\" succesfully registered with the ID : " << mn2 << "\n"; 
*/

   // test of a 1st outport creation
   if ((p1 = mymngr.opcreat("LATDEV", "cm", sizeof(int))) == -1){
      fprintf(stderr, "Unable to open the outport \"LATDEV\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cerr << "OutPort \"" << mymngr.getOpname(p1) << "\" succesfully opened with the ID : " << p1 << "\n"; 

   // test of a 2nd outport creation
   if ((p1 = mymngr.opcreat("DI2FRO", "cm", sizeof(int))) == -1){
      fprintf(stderr, "Unable to open the outport \"DI2FRO\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cerr << "OutPort \"" << mymngr.getOpname(p1) << "\" succesfully opened with the ID : " << p1 << "\n"; 
   
   // test of a 1st inport creation
   if ((p1 = mymngr.opcreat("LATDEV", "cm", sizeof(int))) == -1){
      fprintf(stderr, "Unable to open the inport \"LATDEV\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cerr << "InPort \"" << mymngr.getOpname(p1) << "\" succesfully opened with the ID : " << p1 << "\n"; 

   // test of a 2nd intport creation
   if ((p1 = mymngr.opcreat("DI2FRO", "cm", sizeof(int))) == -1){
      fprintf(stderr, "Unable to open the inport \"DI2FRO\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cerr << "InPort \"" << mymngr.getOpname(p1) << "\" succesfully opened with the ID : " << p1 << "\n"; 
   exit(EXIT_SUCCESS);
}
#endif
