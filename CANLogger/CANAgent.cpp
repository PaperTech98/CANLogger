#include "CANAgent.h"

#include "CANSocket.h"

CANAgent::CANAgent(class CANSocket * MySocket)
{
	Socket = MySocket;

	//TODO Setup XML Interpretation for referencing all enquirey Keys against

}

/*function to subscribe to a data stream returns true if subscription was sucessful and 
false if Agent has no defintion for the Channel Name provided*/
bool CANAgent::Subscribe(char * ChannelName, void(*Notify)(can_frame *RequestedFrame))
{
	//TODO decide if to pass whole can frame or intpret data and pass that instead
	
	
	
	return false;
}
