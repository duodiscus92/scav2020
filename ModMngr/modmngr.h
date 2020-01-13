#ifndef MODMNGR_H
#define MODMNGR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

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

union info {
   char 		csi[8];
   unsigned char 	cusi[8];
   short  int 		ssi[4];
   unsigned short int	sui[4];
   long int		lsi[2];
   unsigned long int	lui[2];
   long long int	llsi;
   unsigned long long int llui;
};

typedef struct port {
   char name[PORTNAME_LENGTH+1];
   char unit[UNITDEF_LENGTH+1];
   int id;			 	/* logical id */
   unsigned short int period;	 	/* frame emission period in ms (for out port only, 0 for inport) */ 
   unsigned char idx;		 	/* CAN frame id */
   unsigned char length;
   union info data;
   char direction;		 	/* IN, OUT, or INOUT */
}PORT;

typedef struct module {
   char name[MODNAME_LENGTH];
   int id;			 	/* logical id */
   unsigned char ninport;		/* number of inport */
   PORT *inport[MAX_INPORT];		/* array of ptr on inport */
   unsigned char noutport;		/* number ou outport */
   PORT *outport[MAX_OUTPORT];		/* array of ptr on outport */
   PORT *diagport;			/* ptr on diagnostic out port */
}MODULE;

class ModMngr
{

public:
   ModMngr();
   ~ModMngr();

   int mopen(const char *name, int ninport, int noutport);
   int opcreat(const char *name, const char *unit, unsigned char length);
   int ipcreat(const char *name, const char *unit, unsigned char length);
   char *getMname(void);		// get module name
   char *getOpname(unsigned char index);// get outport name
   char *getIpname(unsigned char index);// get inport name

private:

   const char *ifname = "can0";
   MODULE tm;
   static int mctr;
   static int ipctr;			// input port counter
   static int opctr;			// ouput port countery
   static int pid;			// logical port id
};
#endif


