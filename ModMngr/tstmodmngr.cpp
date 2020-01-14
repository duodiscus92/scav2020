#include "modmngr.h"

//#include <thread>
//#include <chrono>

using namespace std;

int main (int argc, char ** argv)
{
   int mn1, mn2, op1, op2, op3;
   ModMngr mymngr;

   // test of module registration
   if ((mn1 = mymngr.mopen("detection", 2, 1)) == -1){
      fprintf(stderr, "Unable to register the module\"detection\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cout << "Module \"" << mymngr.getMname() << "\" succesfully registered with the ID : " << mn1 << "\n"; 

   // test of a 1st outport creation
   if ((op1 = mymngr.opcreat("LATDEV", "cm", sizeof(unsigned char), LATDEV, 1000)) == -1){
      fprintf(stderr, "Unable to open the outport \"LATDEV\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cerr << "OutPort \"" << mymngr.getOpname(op1) << "\" succesfully opened with the ID : " << op1 << "\n"; 

   // test of a 2nd outport creation
   if ((op2 = mymngr.opcreat("DI2FRO", "cm", sizeof(short int), DI2FRO, 500)) == -1){
      fprintf(stderr, "Unable to open the outport \"DI2FRO\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cerr << "OutPort \"" << mymngr.getOpname(op1) << "\" succesfully opened with the ID : " << op2 << "\n"; 

   // test of a 3rd outport creation
   if ((op3 = mymngr.opcreat("AS2FRO", "cm", 8, AS2FRO, 250)) == -1){
      fprintf(stderr, "Unable to open the outport \"AS2FRO\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cerr << "OutPort \"" << mymngr.getOpname(op1) << "\" succesfully opened with the ID : " << op3 << "\n"; 

   char c = 'H';
   mymngr.pwrite(&c, sizeof(c), op1);
   short int si = 256;
   mymngr.pwrite(&si, sizeof(si), op2);
   sleep(5);
   c = '0';
   mymngr.pwrite(&c, sizeof(c), op1);
   si = 4095;
   mymngr.pwrite(&si, sizeof(si), op2);
   char msg[10];
   strcpy(msg, "HI WORLD");
   mymngr.pwrite(msg, strlen(msg), op3);
   sleep(20); 
   cerr << "ModMngr normally terminated\n";
   exit(EXIT_SUCCESS);
}
