#include "CANSocket.h"

#include <cstdio>
#include <stdio.h>
#include <stdlib.h>



#include "LogColour.h"

CANSocket::CANSocket() {

	LogYellow();
	printf("Opening CAN Socket\n");
	ResetLogColour();

	memset(&frame, 0, sizeof(struct can_frame));

	//TODO pull baudrate from an XML FILE rather than hardcoding it in
	system("sudo ip link set can0 type can bitrate 100000");
	system("sudo ifconfig can0 up");


	//1.Create socket
	s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (s < 0) {
		perror("socket PF_CAN failed");
		
		//TODO fail better
		exit(EXIT_FAILURE);
	}

	//2.Specify can0 device
	strcpy(ifr.ifr_name, "can0");
	ret = ioctl(s, SIOCGIFINDEX, &ifr);
	if (ret < 0) {
		perror("ioctl failed");
		
		//TODO fail better
		exit(EXIT_FAILURE);
	}

	//3.Bind the socket to can0
	addr.can_family = PF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	ret = bind(s, (struct sockaddr *)&addr, sizeof(addr));
	if (ret < 0) {
		perror("bind failed");
		
		//TODO fail better
		exit(EXIT_FAILURE);
	}

	//4.Define receive rules
	struct can_filter rfilter[1];
	//rfilter[0].can_id = 0x123;
	//rfilter[0].can_mask = CAN_SFF_MASK;
	setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));

	//5.Receive data and exit
	while (0) {
		nbytes = read(s, &frame, sizeof(frame));
		if (nbytes > 0) {
			printf("can_id = 0x%X\r\ncan_dlc = %d \r\n", frame.can_id, frame.can_dlc);
			int i = 0;
			for (i = 0; i < 8; i++)
				printf("data[%d] = %d\r\n", i, frame.data[i]);
			break;
		}
	}
}


void CANSocket::CloseSocket()
{
	LogRed();
	printf("Closing CAN Socket\n");
	ResetLogColour();
	
	//Close the socket and can0
	close(s);
	system("sudo ifconfig can0 down");
}
