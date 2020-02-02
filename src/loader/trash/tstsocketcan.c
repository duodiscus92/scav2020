#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

int
main(void)
{
	int i, s;
	int nbytes;
	struct sockaddr_can addr;
	struct can_frame frame;
	struct ifreq ifr;
	struct can_filter rfilter[2];


	//const char *ifname = "vcan0";
	const char *ifname = "can0";

	if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Error while opening socket");
		return -1;
	}

	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);

	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Error in socket bind");
		return -2;
	}
#ifdef TRANSMIT
	frame.can_id  = 0x123;
	frame.can_dlc = 2;
	frame.data[0] = 0x11;
	frame.data[1] = 0x22;

	nbytes = write(s, &frame, sizeof(struct can_frame));

	printf("Wrote %d bytes\n", nbytes);
#else
	// setting the filter
	rfilter[0].can_id   = 0x123;
	rfilter[0].can_mask = CAN_SFF_MASK;
	rfilter[1].can_id   = 0x200;
	rfilter[1].can_mask = 0x700;
	setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));

for(;;){
	nbytes = read(s, &frame, sizeof(struct can_frame));

	if (nbytes < 0) {
        	perror("Error in can raw socket read");
        	return 1;
	}

	/* paranoid check ... */
	if (nbytes < sizeof(struct can_frame)) {
        	fprintf(stderr, "read: incomplete CAN frame\n");
        	return 1;
	}

	/* do something with the received CAN frame */
	printf("Read %d  bytes\n", nbytes);
	printf("Message received:  ID=%02X DLC=%02x Message=:", frame.can_id, frame.can_dlc);
	for(i=0; i< frame.can_dlc; i++)
		printf("%02X ",  frame.data[i]);
	printf("\n");
} /* end for(;;) */
#endif
	return 0;
}
