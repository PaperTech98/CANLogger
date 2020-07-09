#include "CANAgent.h"

#include "CANSocket.h"
#include "CANChannel.h"

//Used to parse the CAN structures
#include "rapidxml/rapidxml_utils.hpp"

CANAgent::CANAgent(class CANSocket * MySocket, const char * CANDefinitions)
{
	Socket = MySocket;

	MySocket->notifyAgent(this);
	
	CANStreamList ** Bottom = &MyCANStreams;
	
	//Setup XML Interpretation
	rapidxml::file<> xmlFile(CANDefinitions);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	
	//Traverse Tree and put into own data Structure
	rapidxml::xml_node<char>* EntryNode = doc.first_node();
	rapidxml::xml_node<char>* CurrentNode = EntryNode->first_node();
	rapidxml::xml_node<char>* Child;

	//Itterates through all Streams listed in provided XML
	while (CurrentNode) {
		printf("Found Interpretation for : %s\n", CurrentNode->name());

		CANStream * newStream = (CANStream *)malloc(sizeof(CANStream));

		newStream->Name = (char*)malloc(CurrentNode->name_size() * sizeof(char));

		newStream->Name = strcpy(newStream->Name, CurrentNode->name());
		
		//LOOP going through children
		Child = CurrentNode->first_node();

		while (Child) {
			//printf("    Found : %s\n", Child->name());

			this->GetCANStreamData(Child->name(), Child->value(), newStream);


			Child = Child->next_sibling();
		}
		
		/*
		//Insert node
		while (Bottom != nullptr) {
			Bottom = Bottom->Next;
			printf("Called\n");
		}

		*/


		*Bottom = (CANStreamList * )malloc(sizeof(CANStreamList));
		(*Bottom)->This = newStream;
		(*Bottom)->Next = nullptr;

		Bottom = &((*Bottom)->Next);
		CurrentNode = CurrentNode->next_sibling();
	}

	PrintMyDefinitions(MyCANStreams);
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

void CANAgent::GetCANStreamData(char * DataName, char * Data, CANStream * DataStruct)
{
	if (strcmp(DataName, "ID") == 0) {
		DataStruct->ID = atoi(Data);
		//printf("ID = %d\n", DataStruct->ID);
	}
	else if (strcmp(DataName, "Structure") == 0) {
		DataStruct->DataStructure = StringToByteStructure(Data);
	}
	else if (strcmp(DataName, "Units") == 0) {
		DataStruct->Units = StringtoUnits(Data);
	}
	else if (strcmp(DataName, "Rate") == 0) {
		DataStruct->TransmissionRate = atoi(Data);
	}
}

void CANAgent::AddToCANStreamList(CANStreamList * List, CANStream * ToAdd)
{
	if (List == nullptr) {
		printf("adding\n");
		List = (CANStreamList*)malloc(sizeof(CANStreamList));
		List->This = ToAdd;
	}
	else {
		printf("called\n");
		AddToCANStreamList(List->Next, ToAdd);
		
	}
}