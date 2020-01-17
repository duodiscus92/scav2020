#include "modmngr.h"
#include <thread>
#include <chrono>

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
   for(i = 0; i < MAX_INPORT; i++){
      tm.inport[i] = NULL;
      //tm.rfilter[i].can_id = tm.rfilter[i].can_mask = 0;
   }
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
      cerr << "mopen: Module \"" << name << "\" succesfully registered with the ID : " << mctr << "with: " << ninport << " inport and: "<< noutport << " outport.\n"; 
      mctr++;

      return tm.id;
   }
   else{
      cerr << "mopen: Module \"" << name << "\" not registered with as tm.id :" << tm.id << "\n"; 
      return -1;
   }
}

// create a CAN outport 
int ModMngr::opcreat(const char *name, const char *unit, unsigned char length, canid_t idx, unsigned short period)
{
   PORT *p;

   //if (opctr >=  MAX_OUTPORT){
   if (opctr >=  tm.noutport){
      return -1;
      cerr << "opcreat: Unable to create outport \"" << name << "\" in module \"" << tm.name <<  "\" : max outport already opened\n";
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
   if((tm.sockout = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
      cerr << "opecreat: Error while opening socket for outports in module \"" << tm.name <<  "\"\n";
      exit(EXIT_FAILURE);
   }

   // linking the socket to an interface and other settings/
   strcpy(tm.ifr.ifr_name, ifname);
   ioctl(tm.sockout, SIOCGIFINDEX, &tm.ifr);
   tm.addr.can_family  = AF_CAN;
   tm.addr.can_ifindex = tm.ifr.ifr_ifindex;

   // binding the socket
   if(bind(tm.sockout, (struct sockaddr *)&tm.addr, sizeof(tm.addr)) < 0) {
      cerr <<  "opcreat: Error in socket bind in module  \"" << tm.name <<  "\"\n";
      exit(EXIT_FAILURE);
   }

   // all well done
   cerr << "opcreat: Outport \"" << name << "\" in module \"" << tm.name <<  "\" created\n";
   return opctr++;
}

// write a value on an outport
// thread to send un unsigned char
void ModMngr::cansend (int id, int period)
{
   int nbytes;
   for(;;){
     nbytes = write(tm.sockout,  &tm.outport[id]->frame, sizeof(struct can_frame));
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
      cerr << "cansend: Unable to send a msg on this port due to over/under size\n"; 
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
      thread (&ModMngr::cansend, this, id,  tm.outport[id]->period).detach();
   else
      nbytes = write(tm.sockout, &tm.outport[id]->frame, sizeof(struct can_frame));
   cerr << "pwrite: msg succesfully sent\n";
   return 0;
}

// create a CAN inport 
int ModMngr::ipcreat(const char *name, const char *unit, unsigned char length, canid_t idx, unsigned short period)
{
   PORT *p;
   int i;

   // test if it remains inport to open
   if (ipctr >=  tm.ninport){
      cerr << "ipcreat: Unable to create inport \"" << name << "\" in module \"" << tm.name <<  "\" : max inport has been openend\n";
      return -1;
   }

   // test id the port has not been already opened
   for (i=0; i < ipctr; i++)
      if (!strcmp(tm.inport[i]->name, name)){
         cerr << "ipcreat: Unable to create inport \"" << name << "\" in module \"" << tm.name <<  "\" : an inport with the same name already exists\n";
         return -1;
      }
   p = (PORT*) malloc(sizeof(PORT));
   p->id = ipctr;
   strncpy(p->name, name, PORTNAME_LENGTH);
   strncpy(p->unit, unit, UNITDEF_LENGTH);
   p->length = length;
   p->direction = IN;
   p->idx = idx;
   p->period = period;
   p->updated = 0;
   tm.inport[ipctr] = p;
   // Opening a socket for incoming CAN messages
   if(( tm.inport[ipctr]->sockin = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
      cerr << "mopen: Error while opening socket for inports in module \"" << tm.name <<  "\"\n";
      exit(EXIT_FAILURE);
   }

   // linking the socket to an interface and other settings/
   strcpy( tm.inport[ipctr]->ifr.ifr_name, ifname);
   ioctl( tm.inport[ipctr]->sockin, SIOCGIFINDEX, & tm.inport[ipctr]->ifr);
   tm.inport[ipctr]->addr.can_family  = AF_CAN;
   tm.inport[ipctr]->addr.can_ifindex =  tm.inport[ipctr]->ifr.ifr_ifindex;

   // binding the socket
   if(bind( tm.inport[ipctr]->sockin, (struct sockaddr *)& tm.inport[ipctr]->addr, sizeof( tm.inport[ipctr]->addr)) < 0) {
      cerr <<  "mopen: Error in binding socket bind for inports in module  \"" << tm.name <<  "\"\n";
      exit(EXIT_FAILURE);
   }
   // setting the filter to receive only the message with expected idx
   tm.inport[ipctr]->rfilter[0].can_id = idx;
   tm.inport[ipctr]->rfilter[0].can_mask = CAN_SFF_MASK;;
   setsockopt(tm.inport[ipctr]->sockin, SOL_CAN_RAW, CAN_RAW_FILTER,  tm.inport[ipctr]->rfilter, sizeof(tm.inport[ipctr]->rfilter));

   // all well done
   cerr << "ipcreat: Inport \"" << name << "\" in module \"" << tm.name <<  "\" created with pid: " << ipctr/* << "\n"*/;
   fprintf(stderr, " Filter set to %02x - Mask = %02x\n",  tm.inport[ipctr]->rfilter[0].can_id,  tm.inport[ipctr]->rfilter[0].can_mask); 
   thread (&ModMngr::canrecv, this, ipctr,  tm.inport[ipctr]->period).detach();
   return ipctr++;
}

// read a value from an inport
// thread to receive  a frame
int ModMngr::canrecv (int id, int period)
{
   int nbytes, i;
   unsigned char length = tm.inport[id]->length;

   for(;;){
     nbytes = read(tm.inport[id]->sockin,  &tm.inport[id]->frame, sizeof(struct can_frame));
     tm.inport[id]->updated = 1;
     if(tm.inport[id]->frame.can_dlc != length){
      cerr << "canrecv: ***Error*** in module \"" << tm.name << "\": on port \"" << tm.inport[id]->name <<  "\"\n"; 
      cerr << "This port was createad to receive message of length: " << (int) length << " It receives a message of size: " << tm.inport[id]->frame.can_dlc << "\n";
     }
     this_thread::sleep_for (chrono::milliseconds(period));
   }
}

// read a value
int ModMngr::pread(void *value,  int size, int id)
{
   int nbytes, i;
   unsigned char length = tm.inport[id]->length;

   if(length != size){
      cerr << "pread: ***Error*** in module \"" << tm.name << "\": bad call of pread() on port \"" << tm.inport[id]->name <<  "\"\n"; 
      cerr << "This port was createad to receive message of length: " << (int) length << " You call pread to read message of length: " << size << "\n";
      return -1;
   }

   memcpy(value, &tm.inport[id]->frame.data, size);
   //tm.inport[id]->idx = tm.inport[id]->frame.can_id;
   //tm.inport[id]->length = tm.inport[id]->frame.can_dlc;
   // test if it is an updated value or an old one
   if(tm.inport[id]->updated == 1){
     tm.inport[id]->updated =0;
     return 1;
   }

   //cerr << "pread: msg succesfully received\n";
   return 0;
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
