#include "CANModule.h"

#include "CANAgent.h"

CANModule::CANModule(CANAgent * Agent)
{
	this->MyAgent = Agent;
	
	//in the child module classes call the subscribe method on the agent to subscribe to data from the CAN Socket
	//Agent->Subscribe()
}

CANModule::~CANModule()
{
	MyAgent->UnSubscribe(this);
}
