#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

struct port {
   char name[PORTNAME_LENGTH+1];
   char unit[UNITDEF_LENGTH+1];
   unsigned char id;		 	/* logical id */
   unsigned short int period;	 	/* frame emission period in ms (for out port only, 0 for inport) */ 
   unsigned char idx;		 	/* CAN frame id */
   unsigned char length;
   union info data;
   char direction;		 	/* IN, OUT, or INOUT */
};

typedef struct module {
   char name[MODNAME_LENGTH];
   unsigned char id;		 	/* logical id */
   unsigned char ninport;		/* number of inport */
   struct port inport[INPUT_PORT];	/* array of inport */
   unsigned char noutport;		/* number ou outport */
   struct port outport[OUTPUT_PORT];	/* array of outport */
   struct port diagport;		/* diagnostic out port  */
}MODULE;

struct port ld, op1;
MODULE *pm, *tm[MAX_MODULES];
int mctr =0;

void minit(void)
{
   int i;

   for(i=0; i<MAX_MODULES; i++){
     tm[i] = NULL;
     //tm[i].name[0] = 0;
  }
}


MODULE *mopen(char *name, int ninport, int noutport)
{
   MODULE *p;
   int i;

   /* verify module not yet been registered */
   for(i=0; i<MAX_MODULES; i++)
     if ((tm[i] != NULL) && (!strcmp(tm[i]->name, name)))
     	return NULL;

   /* search for free registration slot */
   for(i=0; i<MAX_MODULES; i++)
       if(tm[i] == NULL){
          /* found : alloc memory for a module descriptor and fill it */
          p = malloc(sizeof(MODULE));
          p->id = mctr;
          strncpy(p->name, name, MODNAME_LENGTH);
          p->ninport = ninport;
          p->noutport = noutport;
          /* register module */
          tm[i] = p;
          fprintf(stderr, "Module %s succesgfully registered\n", tm[i]->name);
          return tm[i];
       }

   /* error : no free registration slot found */
   return NULL;
}

void main(void)
{
   MODULE *p;

   minit();

/*
   printf("Taille : %d\n", sizeof(op1));
   strcpy(ld.name, "LATDEV");
   strcpy(ld.unit, "cm");
   ld.period = 40;
   ld.idx = 100;
   ld.length = 2;
   ld.data.ssi[0] = -4096;

   tm[mctr] = malloc(sizeof(MODULE));
   tm[mctr]->id = mctr;
   mctr++;
*/

   if ((p = mopen("detection", 2, 1)) == NULL){
      fprintf(stderr, "Unable to register this module\n");
      exit(EXIT_FAILURE);
   }
}
