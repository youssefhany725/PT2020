#pragma once
#include "Gate.h"

class SWITCH :public Gate
{
	/*
		Class SWITCH
		------------
		represents zero input 1 output switch
	*/
 public:
	SWITCH(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	void Operate();	//Calculates the output of the switch
	void Draw(Output* pOut,bool);	//Draws 0 input opened switch
	int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	int GetInputPinStatus(int n);	//returns 0
	void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
};