#include "modmngr.h"

//#include <thread>
//#include <chrono>

using namespace std;

int main (int argc, char ** argv)
{
   int mn, opcam;
   short int i;
   ModMngr mymngr;

   //  module registration
   if ((mn = mymngr.mopen("camera", 0, 1)) == -1){
      fprintf(stderr, "modcam: Unable to register the module\"camera\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cout << "modcam: Module \"" << mymngr.getMname() << "\" succesfully registered with the ID : " << mn << "\n"; 

   // outport deliver lateral deviation
   if ((opcam = mymngr.opcreat("LATDEV", "cm", sizeof(short int), LATDEV, 100)) == -1){
      fprintf(stderr, "modcam: Unable to open the outport \"LATDEV\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cerr << "modcam: OutPort \"" << mymngr.getOpname(opcam) << "\" succesfully opened with the ID : " << opcam << "\n"; 


   for(i=0; ; i++){
      mymngr.pwrite(&i, sizeof(i), opcam);
      usleep(100000L);
  }
}
