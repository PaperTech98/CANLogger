#pragma once

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
	CANChannel(can_frame frame);
	
private:
	//helper function converting into the unit enum
	//TODO May need to move out into a static method
	ChannelUnits StringtoUnits(char* UnitString);

};

