#include "Gate.h"

//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin
Gate::Gate(int r_Inputs, int r_FanOut):m_OutputPin(r_FanOut)
{
	Selected = false;
	MyID = ++ID;
	//Allocate number of input pins (equals r_Inputs)
	m_InputPins = new InputPin[r_Inputs];
	m_Inputs = r_Inputs;	//set no. of inputs of that gate
	
	//Associate all input pins to this gate
	for(int i=0; i<m_Inputs; i++)
		m_InputPins[i].setComponent(this);
}
int Gate::getNoIpins()
{
	return m_Inputs;
}

OutputPin* Gate::getOP()
{
	return &m_OutputPin;
}
InputPin* Gate::getIP(int i)
{
	return &(m_InputPins[i]);
}

bool Gate::IPnotConnected(int i)
{
	return m_InputPins[i].getIPnotconnected();
}
