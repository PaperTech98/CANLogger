#pragma once

/*A CAN Channel object is used to pass to subscribed CAN Modles with recieved data from the CAN Socket*/

#include <linux/can.h>
#include <linux/can/raw.h>
#include "CANStream.h"







class CANChannel
{
private:
	int data;
	CANStream * MyStream;

public:
	//Constructors
	//given CAN frame and need to work out what stream it is from
	CANChannel(can_frame frame);
	

};

