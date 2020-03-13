#ifndef PRINT_H
#define PRINT_H
#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#define INIPRINT print myprint
#define SETSEVERITY(l) (myprint.set_severity(l))
#define GETSEVERITY(l) (myprint.get_severity(l))
#define CONVSEVERITY(s) (myprint.convert_severity(s))
#define PRINTOUT(g,fmt, ...) (myprint.printout(g, __FILE__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__))
#define PRINTERR(g,fmt, ...) (myprint.printerr(g, __FILE__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__))
//#define PRINTOUT(g,fmt, ...) (myprint.printout(g, __FILE__, __FUNCTION__, __LINE__,  __VA_ARGS__))
//#define PRINTERR(g,fmt, ...) (myprint.printerr(g, __FILE__, __FUNCTION__, __LINE__,  __VA_ARGS__))


//namespace A
//{
typedef enum {DEBUG, INFO, WARNING, ERROR} SEVERITY;

class print{

public:
   print();
   ~print();

   void set_severity(SEVERITY g);
   SEVERITY get_severity(void);
   SEVERITY convert_severity(const char *severity);
   int printout(SEVERITY level, const char *fi, const char *fu, int li,  const char *format, ...);
   int printerr(SEVERITY level, const char *fi, const char *fu, int li,  const char *format, ...);
   //int printout(SEVERITY level, const char *fi, const char *fu, int li, ...);
   //int printerr(SEVERITY level, const char *fi, const char *fu, int li, ...);

   // not used in this class but intersting anyway
   char *itoa(int i, char *s);

private:
   const char *gmesg[4]={"Debug: ", "Info: ", "Warning: ", "Error: "};
   SEVERITY current_severity;
   char *myctime(char *strtime);

   // not used in this class but intersting anyway
   char *reverse(char * s);
};
//}
//using namespace A;
//print myprint;
#endif
