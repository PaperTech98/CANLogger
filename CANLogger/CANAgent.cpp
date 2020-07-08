#include "CANAgent.h"

#include "CANSocket.h"
#include "CANChannel.h"

//Used to parse the CAN structures
#include "rapidxml/rapidxml_utils.hpp"

CANAgent::CANAgent(class CANSocket * MySocket, const char * CANDefinitions)
{
	Socket = MySocket;

	MySocket->notifyAgent(this);

	
	//TODO Setup XML Interpretation for referencing all enquirey Keys against
	rapidxml::file<> xmlFile(CANDefinitions);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	
	//Traverse Tree and put into own data Structure
	rapidxml::xml_node<char>* EntryNode = doc.first_node();
	rapidxml::xml_node<char>* CurrentNode = EntryNode->first_node();

	//TODO create stuct's here and put them into my data structure
	//Itterates through all Streams listed in provided XML
	while (CurrentNode) {
		printf("Found Interpretation for : %s\n", CurrentNode->name());



		//TODO create struct to parse into this function
		AddToCANStreamList(MyCANStreams, nullptr);



		CurrentNode = CurrentNode->next_sibling();
	}

	
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
