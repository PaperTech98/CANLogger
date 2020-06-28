#include "CANAgent.h"

#include "CANSocket.h"

CANAgent::CANAgent(class CANSocket * MySocket)
{
	Socket = MySocket;

	MySocket->notifyAgent(this);

	//TODO Setup XML Interpretation for referencing all enquirey Keys against

}

/*function to subscribe to a data stream returns true if subscription was sucessful and 
false if Agent has no defintion for the Channel Name provided*/
bool CANAgent::Subscribe(char * ChannelName, void(*Notify)(CANChannel))
{
	//TODO fill out logic and implement data structure to store notification data

	return false;
}

//Unsubscribes a Module from all data streams it is subscribed to
void CANAgent::UnSubscribe(CANModule * Module)
{

}

void CANAgent::RecieveFrame(can_frame * frame)
{

	//TODO 
	//check if have any defintions for the frame provided

	//Check subscription data structure if any modules are subscribed to any part of the frame and notify them


}
