#include "modmngr.h"

//#include <thread>
//#include <chrono>

using namespace std;

int main (int argc, char ** argv)
{
   int mn1, ip1, ip2, ip3;
   ModMngr mymngr;

   // test of module registration
   if ((mn1 = mymngr.mopen("detection", 3, 1)) == -1){
      fprintf(stderr, "tstinport: Unable to register the module\"detection\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cout << "tstinport: Module \"" << mymngr.getMname() << "\" succesfully registered with the ID : " << mn1 << "\n"; 

   // test of a 1st inport creation
   if ((ip1 = mymngr.ipcreat("LATDEV", "cm", sizeof(unsigned char), LATDEV, 1000)) == -1){
      fprintf(stderr, "tstinport: Unable to open the inport \"LATDEV\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cerr << "tstinport: InPort \"" << mymngr.getIpname(ip1) << "\" succesfully opened with the ID : " << ip1 << "\n"; 

   // test of a 2nd inport creation
   if ((ip2 = mymngr.ipcreat("DI2FRO", "cm", sizeof(short int), DI2FRO, 500)) == -1){
      fprintf(stderr, "tstinport: Unable to open the outport \"DI2FRO\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cerr << "tstinport: InPort \"" << mymngr.getIpname(ip2) << "\" succesfully opened with the ID : " << ip2 << "\n"; 

   // test of a 3rd inport creation
   if ((ip3 = mymngr.ipcreat("AS2FRO", "cm", 8, AS2FRO, 250)) == -1){
      fprintf(stderr, "tstinport: Unable to open the outport \"AS2FRO\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cerr << "tstinport: InPort \"" << mymngr.getIpname(ip3) << "\" succesfully opened with the ID : " << ip3 << "\n"; 


   char c; short int i; char msg[10];
   for(;;){
      if(mymngr.pread(&c, sizeof(c), ip1) ==1)
         cerr << "tstinport: Reçu char : " << c << "\n";
      //else
         //cerr << "tstinport: rien de nouveau\n";

      if(mymngr.pread(&i, sizeof(short int), ip2) ==1)
         cerr << "tstinport: Reçu short int: " << i << "\n";
      //else
         //cerr << "tstinport: rien de nouveau\n";

      if(mymngr.pread(msg, 8, ip3) == 1) {
         msg[8]=0;
         cout << "tstinport: Reçu string: "<< msg << "\n";
      }

      sleep(1);
   }
   cerr << "tstinport: ModMngr normally terminated\n";
   exit(EXIT_SUCCESS);
}
