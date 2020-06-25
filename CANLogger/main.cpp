#include <cstdio>
#include <stdio.h>
#include <stdlib.h>


//#include <libxml/tree.h>
//#include <libxml/parser.h>

#include "LogColour.h"

#include "CANSocket.h"
#include "CANAgent.h"


int main()
{
	LogGreen();
	printf("hello from CANLogger!\n");
	ResetLogColour();

	//TODO Pass BaudRate Here?
	//open CAN socket
	CANSocket Socket = CANSocket();

	//Create Agent and pass it the socket and XML definitions
	CANAgent Agent  = CANAgent(&Socket);

	//TODO
	//Create Program Modules giving a reference to the CAN Agent to direct all CAN enquires to


	//notify socket to start reading Can Packets and hence the agent will notify the modules of packets recieved

	
	//TODO Decide if a tick function call is needed here


	//Close CAN Socket
	Socket.CloseSocket();

	//terminate program
	LogRed();
	printf("Shutting Down\n");
	ResetLogColour();

    return 0;
}