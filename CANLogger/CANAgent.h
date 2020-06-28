#pragma once

//not ideal to include in a header file but can't forward declare enums
#include "CANChannel.h"


class CANAgent
{
public:
	CANAgent(class CANSocket * MySocket);

	//TODO return pointer to CANChannel class not return whole frame
	bool Subscribe(char * ChannelName, void(*Notify)(CANChannel));
	
	void UnSubscribe(class CANModule * Module);
	//TODO Unsubscribe from individual Channel


	void RecieveFrame(struct can_frame * frame);

private: 
	CANSocket* Socket;
};

