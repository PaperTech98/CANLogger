#pragma once
class CANAgent
{
public:
	CANAgent(class CANSocket * MySocket);

	bool Subscribe(char * ChannelName, void(*Notify)(struct can_frame * RequestedFrame));

private: 
	CANSocket* Socket;
};

