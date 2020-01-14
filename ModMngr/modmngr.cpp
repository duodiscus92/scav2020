#include "modmngr.h"
#include <thread>
#include <chrono>
#define MODMNGR_STANDALONE

using namespace std;

//Module counter
int ModMngr::mctr = 0;		// module counter (obsolete)
int ModMngr::ipctr = 0;		// inport counter
int ModMngr::opctr = 0;		// outport counter
int ModMngr::pid = 0;		// port logical id

ModMngr::ModMngr()
{
   int i;

   tm.id = -1;
   for(i = 0; i < MAX_OUTPORT; i++)
      tm.outport[i] = NULL;
   for(i = 0; i < MAX_INPORT; i++)
      tm.inport[i] = NULL;
}

ModMngr::~ModMngr() {}

// register a module
int ModMngr::mopen(const char *name, int ninport, int noutport)
{

   // verify module not yet been registered
   if (tm.id == -1){
      tm.id = mctr;
      strncpy(tm.name, name, MODNAME_LENGTH);
      tm.ninport = ninport;
      tm.noutport = noutport;
      cerr << "Module \"" << name << "\" succesfully registered with the ID : " << mctr << "\n"; 
      mctr++;
      return tm.id;
   }
   else{
      cerr << "Module \"" << name << "\" not registered with as tm.id :" << tm.id << "\n"; 
      return -1;
   }
}

// create a CAN outport 
int ModMngr::opcreat(const char *name, const char *unit, unsigned char length, canid_t idx, unsigned short period)
{
   PORT *p;

   if (opctr >=  MAX_OUTPORT){
      return -1;
      cerr << "Unable to create outport \"" << name << "\" in module \"" << tm.name <<  "\" : max outport already opened\n";
   }

   // port struct allocation and setup
   p = (PORT*) malloc(sizeof(PORT));
   p->id = opctr;
   strncpy(p->name, name, PORTNAME_LENGTH);
   strncpy(p->unit, unit, UNITDEF_LENGTH);
   p->length = length;
   p->direction = OUT;
   p->idx = idx;
   p->period = period;
   tm.outport[opctr] = p;
   // SocketCan initializations
   // Opening a socket
   if((tm.sock = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
      cerr << "Error while opening socket in module \"" << tm.name <<  "\"\n";
      exit(EXIT_FAILURE);
   }

   // linking the socket to an interface and other settings/
   strcpy(tm.ifr.ifr_name, ifname);
   ioctl(tm.sock, SIOCGIFINDEX, &tm.ifr);
   tm.addr.can_family  = AF_CAN;
   tm.addr.can_ifindex = tm.ifr.ifr_ifindex;

   // binding the socket
   if(bind(tm.sock, (struct sockaddr *)&tm.addr, sizeof(tm.addr)) < 0) {
      cerr <<  "Error in socket bind in module  \"" << tm.name <<  "\"\n";
      exit(EXIT_FAILURE);
   }

   /* setting the filter to receive only the ACK can message from the target host
   tm.rfilter[0].can_id = 0x002;
   tm.rfilter[0].can_mask = CAN_SFF_MASK;
   setsockopt(tm.sock, SOL_CAN_RAW, CAN_RAW_FILTER, &tm.rfilter, sizeof(tm.rfilter));
   fprintf(stderr, "Filter set to %02x - Mask = %02x\n", tm.rfilter[0].can_id, tm.rfilter[0].can_mask); 
   */

   // all well done
   cerr << "Outport \"" << name << "\" in module \"" << tm.name <<  "\" created\n";
   return opctr++;
}

// write a value on an outport
// thread to send un unsigned char
void UC_cansend (int sock, can_frame *frame, int period)
{
   int nbytes;
   for(;;){
     nbytes = write(sock, frame, sizeof(struct can_frame));
     cerr << "Sending unsigned char frame\n";
     this_thread::sleep_for (chrono::milliseconds(period));
   }
}
// wrtie an unsigned char
int ModMngr::pwrite(unsigned char value, /*unsigned char size,*/ int id)
{
   int nbytes;
   unsigned char length = tm.outport[id]->length;

   if(length != sizeof (unsigned char)){
      cerr << "pwrite: Unable to send an unsigned char on this port\n"; 
      return -1;
   }

   tm.outport[id]->data.uc[0] = value;
   //memcpy(&tm.frame.data, &tm.outport[id]->data.uc, size);
   memcpy(&tm.outport[id]->frame.data, &tm.outport[id]->data.uc, length);
   tm.outport[id]->frame.can_id = tm.outport[id]->idx;
   tm.outport[id]->frame.can_dlc = tm.outport[id]->length;
   // period == 0 means one shot, then thread in not util 
   if (tm.outport[id]->period)
      thread (UC_cansend, tm.sock, &tm.outport[id]->frame, tm.outport[id]->period).detach();
   else
      nbytes = write(tm.sock, &tm.outport[id]->frame, sizeof(struct can_frame));
   cerr << "pwrite: Unsigned char sent succesfully\n";
   return 0;
}

int  ModMngr::pwrite(char value, /*unsigned char size,*/ int id)
{
   int nbytes;

   tm.outport[id]->data.sc[0] = value;
   memcpy(&tm.outport[id]->frame.data, &tm.outport[id]->data.sc,  tm.outport[id]->length);
   tm.outport[id]->frame.can_id = tm.outport[id]->idx;
   tm.outport[id]->frame.can_dlc = tm.outport[id]->length;
   nbytes = write(tm.sock, &tm.outport[id]->frame, sizeof(struct can_frame));
   cerr << "Signed char sent succesfully\n";
   return 0;
}

int  ModMngr::pwrite(unsigned short int value, /*unsigned char size,*/ int id)
{
   int nbytes;

   tm.outport[id]->data.usi[0] = value;
   memcpy(&tm.outport[id]->frame.data, &tm.outport[id]->data.usi, tm.outport[id]->length);
   tm.outport[id]->frame.can_id = tm.outport[id]->idx;
   tm.outport[id]->frame.can_dlc = tm.outport[id]->length;
   nbytes = write(tm.sock, &tm.outport[id]->frame, sizeof(struct can_frame));
   cerr << "Unsigned short int sent succesfully\n";
   return 1;
}

// thread to send a signed short int
void SSI_cansend (int sock, can_frame *frame, int period)
{
   int nbytes;
   for(;;){
     nbytes = write(sock, frame, sizeof(struct can_frame));
     cerr << "Sending signed short int frame\n";
     this_thread::sleep_for (chrono::milliseconds(period));
   }
}
// write a signed short int
int  ModMngr::pwrite(short int value, /*unsigned char size,*/ int id)
{
   int nbytes;
   unsigned char length = tm.outport[id]->length;

   if(length != sizeof (short int)){
      cerr << "pwrite: Unable to send a short int on this port\n"; 
      return -1;
   }
   tm.outport[id]->data.ssi[0] = value;
   memcpy(&tm.outport[id]->frame.data, &tm.outport[id]->data.ssi, length);
   tm.outport[id]->frame.can_id = tm.outport[id]->idx;
   tm.outport[id]->frame.can_dlc = length;
   // period == 0 means one shot, then thread in not util 
   if (tm.outport[id]->period)
      thread (SSI_cansend, tm.sock, &tm.outport[id]->frame, tm.outport[id]->period).detach();
   else
      nbytes = write(tm.sock, &tm.outport[id]->frame, sizeof(struct can_frame));
   cerr << "pwrite: Signed short int sent succesfully\n";
   return 1;
}


// create a CAN inport 
int ModMngr::ipcreat(const char *name, const char *unit, unsigned char length, canid_t idx, unsigned short period)
{
   PORT *p;

   if (ipctr >=  MAX_INPORT){
      return -1;
      cerr << "Unable to create inport \"" << name << "\" in module \"" << tm.name <<  "\" : max inport already opened\n";
   }

   p = (PORT*) malloc(sizeof(PORT));
   p->id = ipctr;
   strncpy(p->name, name, PORTNAME_LENGTH);
   strncpy(p->unit, unit, UNITDEF_LENGTH);
   p->length = length;
   p->direction = IN;
   p->idx = idx;
   p->period = period;
   tm.inport[ipctr] = p;
   cerr << "Inport \"" << name << "\" in module \"" << tm.name <<  "\" created\n";
   return ipctr++;
}

char *ModMngr::getMname(void)
{
   return tm.name;
}

char *ModMngr::getOpname(unsigned char index)
{
   return tm.outport[index]->name;
}

char *ModMngr::getIpname(unsigned char index)
{
   return tm.inport[index]->name;
}

#ifdef MODMNGR_STANDALONE
int main (int argc, char ** argv)
{
//   MODULE *p, *q;
   int mn1, mn2, op1, op2, ip1, ip2;
   ModMngr mymngr;

   // test of module registration
   if ((mn1 = mymngr.mopen("detection", 2, 1)) == -1){
      fprintf(stderr, "Unable to register the module\"detection\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cout << "Module \"" << mymngr.getMname() << "\" succesfully registered with the ID : " << mn1 << "\n"; 
/*
   if ((mn2 = mymngr.mopen("controle direction", 2, 2)) == -1){
      fprintf(stderr, "Unable to register the module \"controle direction\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cout << "Module \"" << mymngr.getMname() << "\" succesfully registered with the ID : " << mn2 << "\n"; 
*/

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
/*
   // test of a 1st inport creation
   if ((ip1 = mymngr.opcreat("LATDEV", "cm", sizeof(int), LATDEV)) == -1){
      fprintf(stderr, "Unable to open the inport \"LATDEV\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cerr << "InPort \"" << mymngr.getOpname(ip1) << "\" succesfully opened with the ID : " << ip1 << "\n"; 

   // test of a 2nd intport creation
   if ((ip2 = mymngr.opcreat("DI2FRO", "cm", sizeof(int), DI2FRO)) == -1){
      fprintf(stderr, "Unable to open the inport \"DI2FRO\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cerr << "InPort \"" << mymngr.getOpname(ip2) << "\" succesfully opened with the ID : " << ip2 << "\n"; 
*/
   mymngr.pwrite((unsigned char)'H', op1);
   //mymngr.pwrite((char)-127, op1);
   //mymngr.pwrite((unsigned char)255, op1);
   mymngr.pwrite((short int)256, op2);
   //mymngr.pwrite((short int)257, op1);
   sleep(10); 
   cerr << "ModMngr normally terminated\n";
   exit(EXIT_SUCCESS);
}
#endif
