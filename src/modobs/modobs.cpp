//#include "../print/print.h"
//#include "../print/objprint.h"
//#include "modmngr.h"
#include <print.h>
#include <objprint.h>
#include <modmngr.h>

//#include <thread>
//#include <chrono>

using namespace std;

int main (int argc, char ** argv)
{
   int mn, opobs, ipcalc;
   short int i = 0, icalc;
   ModMngr mymngr;

   //  module registration
   if ((mn = mymngr.mopen("obstacle", 0, 1)) == -1){
   //if ((mn = mymngr.mopen("obstacle", 1, 1)) == -1){
    //fprintf(stderr, "modobs: Unable to register the module\"camera\"\n");
      PRINTERR(ERROR, "Unable to register the module \"obstacle\"", NULL);
      exit(EXIT_FAILURE);
   }
   else
      //cout << "modobs: Module \"" << mymngr.getMname() << "\" succesfully registered with the ID : " << mn << "\n"; 
      PRINTOUT(INFO, "Module \"%s\" succesfully registered with the ID: %d",  mymngr.getMname(), mn);

   // outport deliver distance to front obstacle
   if ((opobs = mymngr.opcreat("DI2FRO", "cm", sizeof(short int), DI2FRO, 100)) == -1){
      //fprintf(stderr, "modobs: Unable to open the outport \"DI2FRO\"\n");
      PRINTERR(ERROR, "Unable to open the outport \"DI2FRO\"", NULL);
      exit(EXIT_FAILURE);
   }
   else
      //cerr << "modobs: OutPort \"" << mymngr.getOpname(opobs) << "\" succesfully opened with the ID : " << opobs << "\n"; 
      PRINTOUT(INFO, "Outport \"%s\" succesfully opened with the ID: %d",  mymngr.getOpname(opobs), opobs);

   // get data from modcalc something
   /*if ((ipcalc = mymngr.ipcreat("WHASPT", "cm", sizeof(short int), WHASPT, 500)) == -1){
      PRINTERR(ERROR, "Unable to open the inport \"WHASPT\"\n", NULL);
      exit(EXIT_FAILURE);
   }
   else
      PRINTOUT(INFO, "Outport \"%s\" succesfully opened with the ID: %d", mymngr.getIpname(ipcalc), ipcalc);*/


   for(i=0; ; i++){
      //mymngr.pread(&icalc, sizeof(icalc), ipcalc);
      //i += icalc/10;
      mymngr.pwrite(&i, sizeof(i), opobs);
      usleep(100000L);
   }
}
