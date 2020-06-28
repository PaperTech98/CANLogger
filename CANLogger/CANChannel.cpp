#include "CANChannel.h"

#include <cstdio>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

CANChannel::CANChannel(can_frame frame, char* DataStrcture, char* Units, char* DataRate)
{
	//TODO Set Channel Name
	//TODO Set Byte Structure Enum
	this->Units = StringtoUnits(Units);
	//TODO Set Data
	this->DataRate = atoi(DataRate);
}

/*Takes a string representing the units and returns the propper enum, not a pretty method but works so long 
as unit specifier matches key exactly, this simply means the xml specification must be well formatted, 
May in future pull out unit keys as constants for use elsewhere*/
ChannelUnits CANChannel::StringtoUnits(char * UnitString)
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
