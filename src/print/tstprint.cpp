#include "print.h"
#include "objprint.h"

#include "../parser/inimngr.h"
#include "../loader/loader.h"

int main(void)
{
   int i = 1234;

   PRINTERR(ERROR, "Hello", NULL);
   PRINTERR(DEBUG,"1Bonjour au niveau %d ", DEBUG);
   PRINTERR(INFO, "2Bonjour au niveau %d ", INFO);
   PRINTERR(WARNING, "3Bonjour au niveau %d ", WARNING);
   PRINTERR(ERROR, "4Bonjour au niveau %d ", ERROR);
   PRINTOUT(DEBUG, "5Bonjour au niveau %d ", DEBUG);
   PRINTOUT(INFO, "6Bonjour au niveau %d ", INFO);
   PRINTOUT(WARNING, "7Bonjour au niveau %d ", WARNING);
   PRINTOUT(ERROR, "8Bonjour au niveau %d ", ERROR);
   PRINTOUT(ERROR, "9Bonjour au niveau %d ", ERROR);
   PRINTERR(DEBUG, "10 %d + %d = %d\n", i, i, i+i);
   PRINTERR(ERROR, "11Bonjour au niveau %d ", ERROR);
   PRINTERR(ERROR, "12Bonjour au niveau %d ", ERROR);

   exit(EXIT_SUCCESS);
}
