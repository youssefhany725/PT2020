#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\GUI\Output.h"

//Base class for classes Gate, Switch, and LED.
class Component
{
private:
	string m_Label;
protected:
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component
	bool Selected;
public:
	Component(const GraphicsInfo &r_GfxInfo);
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut,bool) = 0;	//for each component to Draw itself
	
	virtual int GetCoordsx1();//youssef was here
	virtual int GetCoordsx2();//youssef was here
	virtual int GetCoordsy1();//youssef was here
	virtual int GetCoordsy2();//youssef was here
	virtual void setSelected(bool);
	virtual bool getSelected();
	virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.
	bool Inarea(int, int);
	
	Component();	
	
	//Destructor must be virtual
	virtual ~Component();
};

#endif
