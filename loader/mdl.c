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
   unsigned char mhash[32], rmhash[32];

   /* getting the hostname */
   if(gethostname(hostname, HOSTNAME_LENGTH) == -1){
      fprintf(stderr, "Unable to get hostname\n");
      exit(EXIT_FAILURE);
   }
   if (istarget(hostname)){
      fprintf(stderr, "Sorry : this hostname %s is not a target for SCAV. Should be on the form ecuX (X=0, 1...6)\n", hostname);
      exit(EXIT_FAILURE);
   }
   fprintf(stderr, "Hostname: %s - Id for can frame filtering=%02x\n", hostname, hostname[3] -'0');

   /* gzetting parameters on command call */
   while ((c = getopt(argc , argv, "f:vh")) != -1)
   switch (c){
   case 'v': /* verbose mode */
      verbose = 1;
      break;
   case 'f': /* file name to receive */
      strcpy(fname, optarg);
      fprintf(stderr, "%s: Opening file %s\n", myctime(t), fname);
      if ((fp = fopen(fname, "w")) == NULL){
         fprintf(stderr, "%: Unable to open file %s \n", myctime(t), fname);
         exit(EXIT_FAILURE);
      }
      fprintf(stderr, "%s: Succeed to open file %s\n", myctime(t), fname);
      break;
   case 'h':
   default: /* '?' */
      fprintf(stderr, "Usage: %s -f <file name>\n", argv[0]);
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

   // setting the filter to receive only the can message targeted to this hostname
   rfilter[0].can_id = rfilter[0].can_mask  = ((canid_t)hostname[3])-'0';
   //rfilter[0].can_mask = CAN_SFF_MASK;
   setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
   fprintf(stderr, "Filter set to %02x - Mask = %02x\n", rfilter[0].can_id, rfilter[0].can_mask); 

   /* hash init */
   hasher_init();
   //downloading a binary file
   done = 0; totalbytes = 0;
   while(!done){
      nbytes = read(s, &frame, sizeof(struct can_frame));
      if(verbose){ printf("."); fflush(stdout);}
      if (nbytes < 0) {
         fprintf(stderr, "Error in can raw socket read");
         exit(EXIT_FAILURE);
      }

      /* paranoid check ... */
      if (nbytes < sizeof(struct can_frame)) {
         fprintf(stderr, "read: incomplete CAN frame\n");
         exit(EXIT_FAILURE);
      }

      /* download a binary stream */
      //printf("Read %d  bytes\n", nbytes);
      //printf("Message received:  ID=%02X DLC=%02x Message=:", frame.can_id, frame.can_dlc);
      for(i=0; i< frame.can_dlc-1; i++){
      //printf("%02X ",  frame.data[i]);
         fputc(frame.data[i], fp);
         /*update hash */
         hasher_calculate(frame.data[i]);
      }
      done =  frame.data[frame.can_dlc-1] & 0x01;
      //printf("Next=%s\n", done==1 ? "true" : "false");
      totalbytes += (frame.can_dlc-1);
      /* send ACK */
      frameack.can_id  = 0x002;
      frameack.can_dlc = 1;
      frameack.data[0] = 0x55;
      nbytes = write(s, &frameack, sizeof(struct can_frame));
   }
   fclose(fp);
   fprintf(stderr, "\nDone. Downloaded %d bytes\n", totalbytes);
   /* hash termination */
   hasher_term();
   hasher_hashget(mhash);
   /* get the 4 hash frame (32 bytes) */
   for (i = 0; i<2; i++){
      nbytes = read(s, &frame, sizeof(struct can_frame));
      memcpy(&rmhash[i*8], frame.data, 8);
      /* send ACK */
      frameack.can_id  = 0x002;
      frameack.can_dlc = 1;
      frameack.data[0] = 0x55;
      nbytes = write(s, &frameack, sizeof(struct can_frame));
   }
   /* print hash code received and calculated */
   /*
   fprintf(stderr, "Received hash:\n"); 
   for(i=0; i<16; i++)
      fprintf(stderr, "%02x ", rmhash[i]);
   fprintf(stderr, "\n");
   fprintf(stderr, "Calculated hash:\n"); 
   for(i=0; i<16; i++)
      fprintf(stderr, "%02x ", mhash[i]);
   fprintf(stderr, "\n");
   */

   /* compare hash received with hash calculated */
   if(memcmp(mhash, rmhash, 16)) {
      fprintf(stderr, "Bad hash comparison\n");
      exit(EXIT_FAILURE);
   }
   fprintf(stderr, "SHA MD5 comparison is OK\n");
   exit(EXIT_SUCCESS);
}
