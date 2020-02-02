#include "print.h"
#include "../parser/inimngr.h"
#include "../loader/loader.h"

print::print()
{
   // valeur renvoyée par association d'une section et d'un clé
   char value[VALUE_LENGTH];

   current_severity = ERROR;


   // déclarer dans un tableau les sections et les clés dont on veut les valeurs
   const SK tsk[]={{"tstprint", "severity"}};


   // toujours déclarer un objet de la classe ScavIni comme ci-dessous
   ScavIni sci ("scav.ini", tsk, sizeof(tsk)/sizeof(SK));

   set_severity(INFO);

   if (sci.getvalue(&tsk[0], value) == EXIT_SUCCESS){
	 if(strcmp("nil", value)){ 
         printout(INFO, __FILE__, __FUNCTION__, __LINE__, "Section: %s - Clé:%s - Valeur:%s\n", tsk[0].section, tsk[0].key, value);
      }
      else
         printerr(ERROR, __FILE__, __FUNCTION__, __LINE__, "Section: %s- Key: %s not found\n", tsk[0].section, tsk[0].key);
   }
   set_severity(convert_severity(value));
}

print::~print(){}

char *print::myctime(char *strtime)
{
   time_t t;

   t = time(NULL);
   strcpy(strtime, ctime(&t));
   strtime[strlen(strtime)-1] = 0;

   return strtime;
}

void print::set_severity(SEVERITY g)
{
  current_severity = g;
}

SEVERITY print::get_severity(void)
{
  return current_severity;
}

SEVERITY print::convert_severity(const char *severity)
{
   const char *s[4]={"debug", "info", "warning", "error"};
   int i;

   for(i=0; i<(sizeof(s)/sizeof(char*)); i++)
      if(!strcmp(s[i], severity))
         return (SEVERITY)i;
   printout(ERROR, __FILE__, __FUNCTION__, __LINE__, "Severiry level not found");
   return DEBUG;
}

int print::printerr(SEVERITY level, const char *fi, const char *fu, int li,  const char *format, ...)
{
   char t[80];
   va_list args;
   va_start(args,format);
   int retvalue=0;

   if(level < get_severity())
      retvalue = -1;
   else {
      fprintf(stderr,"%10s %s in File: %s Function: %s Line: %d\t", gmesg[level], myctime(t), fi, fu, li);
      vfprintf(stderr, format, args);
      fprintf(stderr, "\n");
   }
   va_end(args);
   return retvalue;

}

int print::printout(SEVERITY level, const char *fi, const char *fu, int li,  const char *format, ...)
{
   va_list args;
   va_start(args,format);
   int retvalue=0;

   if(level < get_severity())
      retvalue = -1;
   else {
      fprintf(stdout,"%10s in File: %s Function: %s Line: %d\t", gmesg[level], fi, fu, li);
      vfprintf(stdout, format, args);
      fprintf(stdout, "\n");
   }
   va_end(args);
   return retvalue;

}

// not used in this class but intersting anyway
char* print::reverse(char *s)
{
   int i, l = strlen(s);
   char c;

   for(i=0; i < l/2; i++){
      c = s[i];
      s[i] = s[l-i-1];
      s[l-i-1] = c;
   }
   return s;
}

// not used in this class but intersting anyway
char* print::itoa(int n, char* s)
{
   int d, i=0, l;

   if(i<0)
      strcpy(s, "ERROR");
   else {
      while(n>0){
         d = n/10;
         s[i++] = (n-d*10)+'0';
         n = d;
      }
      s[i] = 0;
   }
   return reverse(s);
}

/*
int main(void)
{
   int i = 1234;

   PRINTERR(DEBUG, __FFL__ , "Bonjour au niveau %d ", DEBUG);
   PRINTERR(INFO, __FFL__ , "Bonjour au niveau %d ", INFO);
   PRINTERR(WARNING, __FFL__ , "Bonjour au niveau %d ", WARNING);
   PRINTERR(ERROR, __FFL__ , "Bonjour au niveau %d ", ERROR);
   SETSEVERITY(DEBUG);
   PRINTOUT(DEBUG, __FFL__ , "Bonjour au niveau %d ", DEBUG);
   PRINTOUT(INFO, __FFL__ , "Bonjour au niveau %d ", INFO);
   PRINTOUT(WARNING, __FFL__ , "Bonjour au niveau %d ", WARNING);
   PRINTOUT(ERROR, __FFL__ , "Bonjour au niveau %d ", ERROR);
   PRINTOUT(DEBUG, __FFL__, "%d + %d = %d\n", i, i, i+i);
   exit(EXIT_SUCCESS);
}
*/

