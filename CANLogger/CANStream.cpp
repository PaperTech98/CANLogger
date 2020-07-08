#include "CANStream.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AddToCANStreamList(CANStreamList * List, CANStream * ToAdd)
{
	if (List == nullptr) {
		List = (CANStreamList*)malloc(sizeof(CANStreamList));
		List->This = ToAdd;
	}
	else {
		AddToCANStreamList(List->Next, ToAdd);
	}
}

CANStream * FindCANStreamByName(CANStreamList * List, char * name)
{
	//means end of list
	if (List == nullptr) { return nullptr; }
	
	//check that data is present (pointer protection) if not skip this entry
	if(List->This == nullptr || List->This->Name == nullptr){ return FindCANStreamByName(List->Next, name); }

	//check if stream names match
	if (strcmp(List->This->Name, name) == 0) { return List->This; }
	
	//if not check next entry
	else { return FindCANStreamByName(List->Next, name); }
}

void FreeCANStreamList(CANStreamList * List)
{
	if (List != nullptr) {
		FreeCANStreamList(List->Next);
		free(List->This);
		free(List);
	}
}
