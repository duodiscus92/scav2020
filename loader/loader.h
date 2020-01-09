#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <netdb.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#define MAX_HOST		6
#define HOSTNAME_LENGTH 	10
#define NOT_LAST_FRAME 		0
#define LAST_FRAME 		1

const char thost[MAX_HOST][HOSTNAME_LENGTH]={
   "ecu0",
   "ecu1",
   "ecu2",
   "ecu3",
   "ecu4",
   "ecu5"
}; 
