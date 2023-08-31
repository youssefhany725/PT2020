#pragma once
#include "component.h"
#include "InputPin.h"
#include "OutputPin.h"

/*
  Class LED
  -----------
  represent the LED
*/


class LED :public Component
{
	InputPin m_InputPin;
	bool ON;
public:
	LED(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the LED
	virtual void Draw(Output* pOut, bool);	//Draws LED

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	//virtual int GetInputPinStatus();	//returns status of Inputpin # n if SWITCH, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	InputPin* getIP();

	bool IPnotConnected();

	virtual void SaveComponent(ofstream&);
	virtual void SaveConnection(int, int, int, ofstream&);
	virtual void LoadCircuit(string, int);



};