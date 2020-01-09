#include "../hasher/hasher.h"
#include "loader.h"

char *myctime(char *strtime)
{
   time_t t;

   t = time(NULL);
   strcpy(strtime, ctime(&t));
   strtime[strlen(strtime)-1] = 0;

   return strtime;
}

/* return 0 if hostname is found otherwise -1 */
int istarget(char *hostname)
{
   int i, ret;
   for (i=0; i<MAX_HOST; i++)
      if( !(ret = strcmp(hostname, thost[i])) )
	return ret; 
   return -1;
}

int main(int argc, char ** argv)
{
   int i, s, done, c, verbose = 0;
   int nbytes, totalbytes;
   struct sockaddr_can addr;
   struct can_frame frame, frameack;
   struct ifreq ifr;
   struct can_filter rfilter[1];
   char fname[80], t[80], hostname[HOSTNAME_LENGTH];
   FILE *fp;
   /* for hash calulation */
   unsigned char mhash[32];

   /* gzetting parameters on command call */
   while ((c = getopt(argc , argv, "f:t:vh")) != -1)
   switch (c){
   case 'v': /* verbose mode */
      verbose = 1;
      break;
   case 't': /* select the destination target */
      strncpy(hostname, optarg, HOSTNAME_LENGTH-1);
      if(istarget(hostname)){
         fprintf(stderr, "Sorry : this hostname %s is not a target for SCAV. Should be on the form ecuX (X=0, 1...6)\n", hostname);
         exit(EXIT_FAILURE);
      }
      fprintf(stderr, "Hostname: %s - Id for can frame filtering=%02x\n", hostname, hostname[3] -'0');
      frame.can_id =  ((canid_t)hostname[3]) - '0'; 
      break;
   case 'f': /* file name to send */
      strcpy(fname, optarg);
      fprintf(stderr, "%s: Opening file %s\n", myctime(t), fname);
      if ((fp = fopen(fname, "r")) == NULL){
         fprintf(stderr, "%: Unable to open file %s \n", myctime(t), fname);
         exit(EXIT_FAILURE);
      }
      fprintf(stderr, "%s: Succeed to open file %s\n", myctime(t), fname);
      break;
   case 'h':
   default: /* '?' */
      fprintf(stderr, "Usage: %s -f <file name> -t <target hostname> [-v]\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   const char *ifname = "can0";

   if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
      fprintf(stderr, "Error while opening socket");
      exit(EXIT_FAILURE);
   }

   /* */
   strcpy(ifr.ifr_name, ifname);
   ioctl(s, SIOCGIFINDEX, &ifr);
   addr.can_family  = AF_CAN;
   addr.can_ifindex = ifr.ifr_ifindex;

   if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
      fprintf(stderr, "Error in socket bind");
      exit(EXIT_FAILURE);
   }

   // setting the filter to receive only the ACK can message from the target host */
   rfilter[0].can_id = 0x002;
   rfilter[0].can_mask = CAN_SFF_MASK;
   setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
   fprintf(stderr, "Filter set to %02x - Mask = %02x\n", rfilter[0].can_id, rfilter[0].can_mask); 

   /* hash init */
   hasher_init();
   //uploadinbg a binary file
   totalbytes =  frame.can_dlc = 0;
   c = fgetc(fp);
   while(!feof(fp)){
      /* write a char into the send buffer */
      frame.data[frame.can_dlc++] = c;
      /*update hash */
      hasher_calculate(c);
      //if(verbose) printf("dlc=%02x - data=%02x\n", frame.can_dlc-1,  frame.data[frame.can_dlc-1]);
      totalbytes++;
      if(frame.can_dlc ==  CAN_MAX_DLC-1){
         /* set flag to tell that another frame will be sent after this one */
	 frame.data[frame.can_dlc] = 0;
	 frame.can_dlc = CAN_MAX_DLC;
	 /* send the can frame */
         if(verbose) {printf("."); fflush(stdout);}
         nbytes = write(s, &frame, sizeof(struct can_frame));
	 /* reset the frame size */
	 frame.can_dlc = 0;
         /* wait for ACK */
         nbytes = read(s, &frameack, sizeof(struct can_frame));
         if( (frameack.can_dlc != 1) || (frameack.data[0] != 0x55) ){
	    fprintf(stderr, "Bad ACK frame received dlc=%02x data=%02x\n", frameack.can_dlc, frameack.data[0]);
            exit(EXIT_FAILURE);
         }
      }
      /* read next byte */
      c = fgetc(fp);
   }
   /* EOF encountered must send the remaining bytes in a las frame */
   /* set flag to tell that it is the last frame */
   frame.data[frame.can_dlc] = 1;
   if(verbose) {printf("."); fflush(stdout);}
   frame.can_dlc++;
   nbytes = write(s, &frame, sizeof(struct can_frame));
   /* hash termination */
   hasher_term();
   hasher_hashget(mhash);
   frame.can_dlc = 8;
   /* send 4 frames of hash (32 bytes)*/
   for(i=0; i<2; i++){
      memcpy(frame.data, &mhash[i*8], 8);
      nbytes = write(s, &frame, sizeof(struct can_frame));
      /* wait for ACK */
      nbytes = read(s, &frameack, sizeof(struct can_frame));
      if( (frameack.can_dlc != 1) || (frameack.data[0] != 0x55) ){
         fprintf(stderr, "Bad ACK frame received dlc=%02x data=%02x\n", frameack.can_dlc, frameack.data[0]);
         exit(EXIT_FAILURE);
      }
   }
   fclose(fp);
   fprintf(stderr, "\nDone. Uploaded %d bytes\n", totalbytes);
   /* print hash code that has been sent */
   /*
   fprintf(stderr, "Hash sent:\n");
   for(i=0; i<16; i++)
      fprintf(stderr, "%02x ", mhash[i]);
   fprintf(stderr, "\n");
   */
   exit(EXIT_SUCCESS);
}
