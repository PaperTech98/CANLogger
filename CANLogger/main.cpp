#include <cstdio>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

int main()
{
    printf("hello from CANLogger!\n");

	int ret;
	int s, nbytes;
	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame;

	memset(&frame, 0, sizeof(struct can_frame));

	//TODO pull baudrate from an XML FILE rather than hardcoding it in
	system("sudo ip link set can0 type can bitrate 100000");
	system("sudo ifconfig can0 up");


	//1.Create socket
	s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (s < 0) {
		perror("socket PF_CAN failed");
		return 1;
	}

	//2.Specify can0 device
	strcpy(ifr.ifr_name, "can0");
	ret = ioctl(s, SIOCGIFINDEX, &ifr);
	if (ret < 0) {
		perror("ioctl failed");
		return 1;
	}

	//3.Bind the socket to can0
	addr.can_family = PF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	ret = bind(s, (struct sockaddr *)&addr, sizeof(addr));
	if (ret < 0) {
		perror("bind failed");
		return 1;
	}









	//6.Close the socket and can0
	close(s);
	system("sudo ifconfig can0 down");

	printf("Shutting Down\n");

    return 0;
}