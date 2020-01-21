#include "modmngr.h"
#include <thread>
#include <chrono>
using namespace std;


static int sockin;
struct can_frame frame;

int canrecv (int period)
{
   int nbytes, i;

   for(;;){
     nbytes = read(sockin,  &frame, sizeof(struct can_frame));
     for (i=0; i< frame.can_dlc; i++)
       fprintf(stderr, "%02X ", frame.data[i]);
     cerr << "\n";
     this_thread::sleep_for (chrono::milliseconds(period));
   }
}

int main(void)
{  
   int i, nbytes;
   struct sockaddr_can addr;
   struct ifreq ifr;
   struct can_filter rfilter[8];
   const char* ifname = "can0";

   // SocketCan initializations
   // Opening a socket
   if((sockin = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
      cerr << "ipcreat: Error while opening socket for inports in module \n";
      exit(EXIT_FAILURE);
   }

   // linking the socket to an interface and other settings/
   strcpy(ifr.ifr_name, ifname);
   ioctl(sockin, SIOCGIFINDEX, &ifr);
   addr.can_family  = AF_CAN;
   addr.can_ifindex = ifr.ifr_ifindex;

   // binding the socket
   if(bind(sockin, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
      cerr <<  "ipcreat: Error in socket bind in module\n";
      exit(EXIT_FAILURE);
   }

   // initialiazing filters
   rfilter[0].can_id = 0x011;
   rfilter[0].can_mask = CAN_SFF_MASK;
   rfilter[1].can_id = 0x012;
   rfilter[1].can_mask = CAN_SFF_MASK;
   rfilter[2].can_id = 0x013;
   rfilter[2].can_mask = CAN_SFF_MASK;
   setsockopt(sockin, SOL_CAN_RAW, CAN_RAW_FILTER, rfilter, sizeof(struct can_filter)*3);

   // receiving frame
   /*for(;;){
      nbytes = read(sockin,  &frame, sizeof(struct can_frame));
      for (i=0; i< frame.can_dlc; i++)
        fprintf(stderr, "%02X ", frame.data[i]);
     cerr << "\n";
   }*/
   thread (canrecv, 500).detach();
   sleep(100);
   exit(EXIT_SUCCESS);
}

