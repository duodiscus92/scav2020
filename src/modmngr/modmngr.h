#ifndef MODMNGR_H
#define MODMNGR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <mutex>
#include "../loader/loader.h"
//#include <loader.h>
using  namespace std;

#define PORTNAME_LENGTH		6
#define UNITDEF_LENGTH		10
#define MODNAME_LENGTH		20
#define MAX_INPORT		10
#define MAX_OUTPORT		5
#define PATH_LENGTH		80
#define OUT			1
#define IN			-1
#define INOUT			0
#define MAX_MODULES		100

enum cnamsg {LATDEV=0x11, DI2FRO=0x12, AS2FRO=0x13,DITORO=0x14, AS2RRO=0x15, MEDASP=0x16,SPESPT=0X17, MEAWHA=0x18,WHASPT=0x19};

/*
union info {
   char 		sc[8];
   unsigned char 	uc[8];
   short  int 		ssi[4];
   unsigned short int	usi[4];
   long int		sli[2];
   unsigned long int	uli[2];
   long long int	slli;
   unsigned long long int ulli;
};
*/

typedef struct port {
   char name[PORTNAME_LENGTH+1];
   char unit[UNITDEF_LENGTH+1];
   int id;			 	/* logical port id */
   unsigned short int period;	 	/* frame emission period in ms (for out port only, 0 for inport) */ 
   canid_t idx;			 	/* CAN frame id */
   unsigned char length;
   char direction;		 	/* IN, OUT, or INOUT */
   struct can_frame frame;
   //int firstcall;
   int updated;
   int sockout, sockin;
   struct sockaddr_can addr;
   struct ifreq ifr;			// pysical interface
   struct can_filter rfilter[1];	// filters for inports
   mutex ver;
}PORT;

typedef struct module {
   char name[MODNAME_LENGTH];
   int id;			 	/* logical id */
   unsigned char ninport;		/* number of inport */
   PORT *inport[MAX_INPORT];		/* array of ptr on inport */
   unsigned char noutport;		/* number ou outport */
   PORT *outport[MAX_OUTPORT];		/* array of ptr on outport */
}MODULE;

class ModMngr
{

public:
   ModMngr();
   ~ModMngr();

   int mopen(const char *name, int ninport, int noutport);
   int opcreat(const char *name, const char *unit, unsigned char length, canid_t idx, unsigned short period);
   int ipcreat(const char *name, const char *unit, unsigned char length, canid_t idx, unsigned short period);
   char *getMname(void);							// get module name
   char *getOpname(unsigned char index);					// get outport name
   char *getIpname(unsigned char index);					// get inport name
   int pwrite(void *value, int size, int pid);					// write on port of id pid */
   int pread(void *value, int size, int pid);					// read on port of id pid */

private:

   const char *ifname = "can0";
   MODULE tm;
   static int mctr;			// module counter (obsolete)
   static int ipctr;			// input port counter
   static int opctr;			// ouput port counter
   static int pid;			// logical port id
   void cansend (int id, int period);	// thread to send a frame
   int canrecv (int id, int period);	// thread ro receive a frame
};
#endif


