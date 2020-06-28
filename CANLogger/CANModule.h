#pragma once
class CANModule
{
public:
	CANModule(class CANAgent * Agent);
	~CANModule();

	//TODO Tick Function? as abstract?

private:
	//TODO used for rendering if the module has a GUI component
	//class Widget * MyWidget;

	CANAgent * MyAgent;

};

