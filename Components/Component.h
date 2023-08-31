#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\GUI\Output.h"

#include <iostream>
#include <fstream>
#include "OutputPin.h"
#include "InputPin.h"

//Base class for classes Gate, Switch, and LED. w kaman connection
class Component
{
private:
	string NameTag;
protected:
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component
	bool Selected;
	int MyID;
	
public:
	static int ID;
	Component(const GraphicsInfo &r_GfxInfo);
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut, bool) = 0;	//for each component to Draw itself
	
	
	
	virtual void setSelected(bool);
	virtual bool getSelected();

	virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1

	
	virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.

	virtual void getGInfo(int& x1, int& y1, int& x2, int& y2); // Getter for m_GfxInfo 

	virtual void SetLabel(string Label);
	virtual string GetLabel();
	virtual bool Inarea(int x, int y);
	virtual bool InConnection(int x, int y);


	virtual void SaveComponent( ofstream&)=0;
	virtual void SaveConnection(int, int, int, ofstream&)=0;
	virtual void LoadCircuit(string, int) = 0;

	
	virtual int GetmyID();
	

	
	Component();	
	
	//Destructor must be virtual
	virtual ~Component();
};

#endif

