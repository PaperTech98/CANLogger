#pragma once

//not ideal to include in a header file but can't forward declare enums
#include "CANStream.h"




class CANAgent
{
public:
	CANAgent(class CANSocket * MySocket, const char * CANDefinitions);

	//TODO return pointer to CANChannel class not return whole frame
	bool Subscribe(char * ChannelName, void(*Notify)(class CANChannel));
	
	void UnSubscribe(class CANModule * Module);
	//TODO Unsubscribe from individual Channel


	void RecieveFrame(struct can_frame * frame);

private: 
	CANSocket* Socket;

	//Data structure for all CAN Streams
	CANStreamList * MyCANStreams = nullptr;

	void GetCANStreamData(char * DataName, char * Data, CANStream * DataStruct);

	void AddToCANStreamList(CANStreamList * List, CANStream * ToAdd);
};

