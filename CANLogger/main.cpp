#include <cstdio>
#include <stdio.h>
#include <stdlib.h>

#include "LogColour.h"

#include "CANSocket.h"
#include "CANAgent.h"



#define DEFAULT_BAUDRATE 100000
#define XMLINTERP "Haltech_CANBus_v2.xml"

int main()
{
	LogGreen();
	printf("hello from CANLogger!\n");
	ResetLogColour();

	//open CAN socket
	CANSocket Socket = CANSocket(DEFAULT_BAUDRATE);

	//Create Agent and pass it the socket and XML definitions
	CANAgent Agent  = CANAgent(&Socket, XMLINTERP);

	//TODO
	//Create Program Modules giving a reference to the CAN Agent to direct all CAN enquires to


	//notify socket to start reading Can Packets and hence the agent will notify the modules of packets recieved
	Socket.StartCANRead();
	
	//TODO Decide if a tick function call is needed here if so may need to call it using a seperate thread but will need to limit the scope of what a tick function is allowed to do to read only?


	//Close CAN Socket
	Socket.CloseSocket();

	//terminate program
	LogRed();
	printf("Shutting Down\n");
	ResetLogColour();

    return 0;
}