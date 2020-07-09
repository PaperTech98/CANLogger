#include "CANStream.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LogColour.h"



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
		//free next node/s
		FreeCANStreamList(List->Next);

		//free this nodes data
		free(List->This->Name);

		//free this node
		free(List->This);
		free(List);
	}
}



/*Takes a string representing the units and returns the propper enum, not a pretty method but works so long
as unit specifier matches key exactly, this simply means the xml specification must be well formatted,
May in future pull out unit keys as constants for use elsewhere*/
ChannelUnits StringtoUnits(char * UnitString)
{
	if (!strcmp(UnitString, "RPM")) {
		return ChannelUnits::RPM;
	}
	else if (!strcmp(UnitString, "kPa")) {
		return ChannelUnits::kPa;
	}
	else if (!strcmp(UnitString, "0.1kPa")) {
		return ChannelUnits::kPa0_1;
	}
	else if (!strcmp(UnitString, "0.1%")) {
		return ChannelUnits::Percent0_1;
	}
	else if (!strcmp(UnitString, "0.1Degrees")) {
		return ChannelUnits::Degree0_1;
	}
	else if (!strcmp(UnitString, "0.1km/h")) {
		return ChannelUnits::kmph0_1;
	}
	else if (!strcmp(UnitString, "RPM/S")) {
		return ChannelUnits::RPMpS;
	}
	else if (!strcmp(UnitString, "0.001Lambda")) {
		return ChannelUnits::Lambda0_001;
	}
	else if (!strcmp(UnitString, "integer")) {
		return ChannelUnits::integer;
	}
	else if (!strcmp(UnitString, "mL/minute")) {
		return ChannelUnits::mLpminute;
	}
	else if (!strcmp(UnitString, "0.1Volts")) {
		return ChannelUnits::Volts0_1;
	}
	else if (!strcmp(UnitString, "0.1Kelvin")) {
		return ChannelUnits::Kelvin0_1;
	}
	else if (!strcmp(UnitString, "Litres/Hour")) {
		return ChannelUnits::Lph;
	}
	else if (!strcmp(UnitString, "Kilometers")) {
		return ChannelUnits::km;
	}
	else if (!strcmp(UnitString, "Litres/100km")) {
		return ChannelUnits::Lp100km;
	}
	else if (!strcmp(UnitString, "TRUE")) {
		return ChannelUnits::TRUE;
	}
	else {
		return ChannelUnits::None;
	}
}

//TODO Clean up this monster of a function
ByteStructureExt * StringToByteStructure(char * ByteStructureString)
{
	ByteStructureExt * MyStructure = (ByteStructureExt*)malloc(sizeof(ByteStructureExt));
	
	
	//contains ':' -> always bit structure
		//contains ':'x2 -> Bit Range
	if (strstr(ByteStructureString, ":") != nullptr) {
		char * second = strstr(ByteStructureString, ":");

		if (strstr(strstr(ByteStructureString, ":"),":") != nullptr) //CASE: Bit range
		{
			//printf("Bit Range\n");
			MyStructure->MyStructure = ByteStructure::BitRange;
			MyStructure->StartingByte = atoi(ByteStructureString);
			MyStructure->StartingBit = atoi(second);

			second = strstr(second, "-") + 1;
			MyStructure->FinishingByte = atoi(second);

			second = strstr(second, ":");
			MyStructure->FinishingBit = atoi(second);

		}
		else //CASE: SingleBit
		{
			//printf("Bit Single\n");
			MyStructure->MyStructure = ByteStructure::BitSingle;
			MyStructure->StartingByte = atoi(ByteStructureString);
			MyStructure->StartingBit = atoi(second);

			MyStructure->FinishingByte = MyStructure->StartingByte;
			MyStructure->FinishingBit = MyStructure->StartingBit;
		}
	}
	else //Can only be error or Byte bassed
	{
		if (strstr(ByteStructureString, "-") != nullptr) //CASE: Byte Range (Assume inclusive and is in two's compliment)
		{
			//printf("Byte Range\n");
			MyStructure->MyStructure = ByteStructure::Range;
			char* second = strstr(ByteStructureString, "-") + 1 ;

			MyStructure->StartingByte = atoi(ByteStructureString);
			MyStructure->FinishingByte = atoi(second);

			//printf("%s\n", second);

			MyStructure->StartingBit = UNUSED;
			MyStructure->FinishingBit = UNUSED;
		}
		else //CASE Assume Single Byte
		{
			//printf("Byte Single\n");
			MyStructure->MyStructure = ByteStructure::Single;
			MyStructure->StartingByte = atoi(ByteStructureString);
			MyStructure->FinishingByte = MyStructure->StartingByte;

			MyStructure->StartingBit = UNUSED;
			MyStructure->FinishingBit = UNUSED;

		}
	}
	
	return MyStructure;
}

void PrintMyDefinitions(CANStreamList * Entry)
{
	if (Entry != nullptr /*|| Entry->This != nullptr*/) {
		LogGreen();
		printf("CAN Stream %s found on ID %d with data rate of %d\n", Entry->This->Name, Entry->This->ID, Entry->This->TransmissionRate);
		ResetLogColour();

		PrintMyDefinitions(Entry->Next);
	}
}
	
