#ifndef MODMNGR_H
#define MODMNGR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#define PORTNAME_LENGTH		6
#define UNITDEF_LENGTH		10
#define MODNAME_LENGTH		20
#define INPUT_PORT		10
#define OUTPUT_PORT		5
#define PATH_LENGTH		80
#define OUT			1
#define IN			-1
#define INOUT			0
#define MAX_MODULES		100

enum cnamsg {LATDEV, DI2FRO, AS2FRO,DITORO, AS2RRO, MEDASP,SPESPT, MEAWHA,WHASPT};

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
   char id;			 	/* logical id */
   unsigned short int period;	 	/* frame emission period in ms (for out port only, 0 for inport) */ 
   unsigned char idx;		 	/* CAN frame id */
   unsigned char length;
   union info data;
   char direction;		 	/* IN, OUT, or INOUT */
}PORT;

typedef struct module {
   char name[MODNAME_LENGTH];
   char id;			 	/* logical id */
   unsigned char ninport;		/* number of inport */
   PORT *inport[INPUT_PORT];		/* array of ptr on inport */
   unsigned char noutport;		/* number ou outport */
   PORT *outport[OUTPUT_PORT];		/* array of ptr on outport */
   PORT *diagport;			/* ptr on diagnostic out port */
}MODULE;

class ModMngr
{

public:
   ModMngr();
   ~ModMngr();

//   MODULE *mopen(const char *name, int ninport, int noutport);
   int mopen(const char *name, int ninport, int noutport);

private:

   const char *ifname = "can0";
   //MODULE *tm[MAX_MODULES];
   MODULE tm;
   static int mctr;

};
#endif


