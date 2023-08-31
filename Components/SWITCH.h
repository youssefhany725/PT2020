#pragma once
#include "component.h"
#include "InputPin.h"
#include "OutputPin.h"

class SWITCH :public Component
{
	/*
		Class SWITCH
		------------
		represents zero input 1 output switch
	*/
	//InputPin m_InputPin;
	OutputPin m_OutputPin;
	bool Closed;
 public:
	SWITCH(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	void Operate();	//Calculates the output of the switch
	void Draw(Output* pOut,bool);	//Draws 0 input opened switch
	int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	int GetInputPinStatus(int n);	//returns 0
	void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	OutputPin* getOP(); // Added to get O/P				
	void SetClosed(bool);
	bool GetClosed();

	virtual void SaveComponent(ofstream&);
	virtual void SaveConnection(int, int, int, ofstream&);
	virtual void LoadCircuit(string, int);
};