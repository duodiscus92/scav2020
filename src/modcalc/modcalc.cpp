//#include "modmngr.h"
#include <modmngr.h>

//#include <thread>
//#include <chrono>

using namespace std;

int main (int argc, char ** argv)
{
   int mn, opcalc, ipcam, ipobs;
   short int i, icam, iobs, icalc;
   ModMngr mymngr;

   //  module registration
   if ((mn = mymngr.mopen("calc", 2, 1)) == -1){
      fprintf(stderr, "modcalc: Unable to register the module\"calc\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cout << "modcalc: Module \"" << mymngr.getMname() << "\" succesfully registered with the ID : " << mn << "\n"; 

   // calculate something
   if ((opcalc = mymngr.opcreat("WHASPT", "cm", sizeof(short int), WHASPT, 500)) == -1){
      fprintf(stderr, "modcalc: Unable to open the outport \"DI2FRO\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cerr << "modcalc: OutPort \"" << mymngr.getOpname(opcalc) << "\" succesfully opened with the ID : " << opcalc << "\n"; 

   if ((ipcam = mymngr.ipcreat("LATDEV", "cm", sizeof(short int), LATDEV, 500)) == -1){
      fprintf(stderr, "modcalc: Unable to open the inport \"LATDEV\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cerr << "modcalc: InPort \"" << mymngr.getIpname(ipcam) << "\" succesfully opened with the ID : " << ipcam << "\n"; 

   // test of a 2nd inport creation
   if ((ipobs = mymngr.ipcreat("DI2FRO", "cm", sizeof(short int), DI2FRO, 500)) == -1){
      fprintf(stderr, "modcalc: Unable to open the outport \"DI2FRO\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cerr << "modcalc: InPort \"" << mymngr.getIpname(ipobs) << "\" succesfully opened with the ID : " << ipobs << "\n"; 


   for(i=0; ; i++){
      mymngr.pread (&icam, sizeof(i), ipcam);
      mymngr.pread (&iobs, sizeof(i), ipobs);
      icalc = icam + iobs;
      mymngr.pwrite(&icalc, sizeof(i), opcalc);
      cerr << "modcal: Result of :" << icam << " + " << iobs << " = " << icalc << "\n";
      usleep(500000L);
   }
}
