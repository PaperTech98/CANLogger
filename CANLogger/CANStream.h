#pragma once

#define UNUSED -1

enum ByteStructure
{
	Range, //Range of bytes normally for a 16 bit value
	Single, //Single Byte
	BitRange, //Range of bits in a given Byte
	BitSingle //Single Bit boolean
};

typedef struct ByteStructureExt ByteStructureExt;

struct ByteStructureExt {
	ByteStructure MyStructure;
	int StartingByte;
	int FinishingByte;
	int StartingBit;
	int FinishingBit;
};

enum ChannelUnits
{
	RPM, //RPM
	kPa, //kPa
	kPa0_1, //0.1kPa
	Percent0_1, // 0.1%
	Degree0_1, // 0.1Degrees
	kmph0_1, // 0.1km/h
	RPMpS, // RPM/S
	Lambda0_001, // 0.001Lambda
	integer, //considered a literal integer value
	mLpminute, // mL/minute
	Volts0_1, //0.1Volts
	Kelvin0_1, //0.1Kelvin
	Lph, // Litres/Hour
	km, //Kilometers
	Lp100km, //Litres/100km
	TRUE, // TRUE
	None //NULL state in case units cannot be determined
};

typedef struct CANStream CANStream;
typedef struct CANStreamList CANStreamList;

struct CANStream {
	char * Name;
	int ID;
	ByteStructureExt * DataStructure;
	ChannelUnits Units;
	int TransmissionRate;
};

struct CANStreamList {
	CANStream * This;
	CANStreamList * Next;
};


CANStream * FindCANStreamByName(CANStreamList * List, char * name);
void FreeCANStreamList(CANStreamList * List);


ChannelUnits StringtoUnits(char* UnitString);
ByteStructureExt * StringToByteStructure(char* ByteStructureString);

void PrintMyDefinitions(CANStreamList * Entry);