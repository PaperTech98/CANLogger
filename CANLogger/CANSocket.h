#pragma once
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

class CANSocket
{
public:
	CANSocket(int BaudRate); //Constructor
	~CANSocket();

	void notifyAgent(class CANAgent* MyAgent);
	void StartCANRead();

	void CloseSocket();

private:
	int ret;
	int s, nbytes;
	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame;
	
	CANAgent * MyAgent;
	bool AgentNotification = false;
};