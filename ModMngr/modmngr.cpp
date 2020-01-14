#include "modmngr.h"
#include <thread>
#include <chrono>
//#define MODMNGR_STANDALONE

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
   p->firstcall = 1;
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
void ModMngr::UC_cansend (int id, int period)
{
   int nbytes;
   for(;;){
     nbytes = write(tm.sock,  &tm.outport[id]->frame, sizeof(struct can_frame));
     //cerr << "Sending a msg of " << (int)tm.outport[id]->length << " bytes\n";
     this_thread::sleep_for (chrono::milliseconds(period));
   }
}
// write an unsigned char
int ModMngr::pwrite(void *value,  int size, int id)
{
   int nbytes;
   unsigned char length = tm.outport[id]->length;

   if(length != size){
      cerr << "pwrite: Unable to send a msg on this port due to over/under size\n"; 
      return -1;
   }

   if (!tm.outport[id]->firstcall){
     //update the value to be sent
     memcpy(&tm.outport[id]->frame.data, value, length);
     return 0;
   }
   tm.outport[id]->firstcall = 0;
   memcpy(&tm.outport[id]->frame.data, value, length);
   tm.outport[id]->frame.can_id = tm.outport[id]->idx;
   tm.outport[id]->frame.can_dlc = tm.outport[id]->length;
   // period == 0 means one shot, then thread in not util 
   if (tm.outport[id]->period)
      thread (&ModMngr::UC_cansend, this, id,  tm.outport[id]->period).detach();
   else
      nbytes = write(tm.sock, &tm.outport[id]->frame, sizeof(struct can_frame));
   cerr << "pwrite: msg succesfully\n";
   return 0;
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
   int mn1, mn2, op1, op2, op3, ip1, ip2;
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

   // test of a 3rd outport creation
   if ((op3 = mymngr.opcreat("AS2FRO", "cm", 8, AS2FRO, 250)) == -1){
      fprintf(stderr, "Unable to open the outport \"AS2FRO\"\n");
      exit(EXIT_FAILURE);
   }
   else
      cerr << "OutPort \"" << mymngr.getOpname(op1) << "\" succesfully opened with the ID : " << op3 << "\n"; 
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
#endif
