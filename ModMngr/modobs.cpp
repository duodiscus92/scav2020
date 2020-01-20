#include "modmngr.h"

//#include <thread>
//#include <chrono>

using namespace std;

int main (int argc, char ** argv)
{
   int mn, opobs;
   short int i;
   ModMngr mymngr;

   //  module registration
   if ((mn = mymngr.mopen("obstacle", 0, 1)) == -1){
      fprintf(stderr, "modobs: Unable to register the module\"camera\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cout << "modobs: Module \"" << mymngr.getMname() << "\" succesfully registered with the ID : " << mn << "\n"; 

   // outport deliver distance to front obstacle
   if ((opobs = mymngr.opcreat("DI2FRO", "cm", sizeof(short int), DI2FRO, 100)) == -1){
      fprintf(stderr, "modobs: Unable to open the outport \"DI2FRO\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cerr << "modobs: OutPort \"" << mymngr.getOpname(opobs) << "\" succesfully opened with the ID : " << opobs << "\n"; 


   for(i=0; ; i++){
      mymngr.pwrite(&i, sizeof(i), opobs);
      usleep(100000L);
  }
}
