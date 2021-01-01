#include "LED.h"

LED::LED(const GraphicsInfo& r_GfxInfo, int r_FanOut, string Label) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	NameTag = Label;
}


void LED::Operate()
{
	//caclulate the output status as the input
	//Add you code here
	m_OutputPin.setStatus(m_InputPins[0].getStatus());
}


// Function Draw
// Draws Led
void LED::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawLED(m_GfxInfo);
	pOut->PrintLabel(m_GfxInfo.x1, m_GfxInfo.y1 - 17, NameTag);
}

//returns status of outputpin
int LED::GetOutPinStatus()
{
	return -1;
}


//returns status of Inputpin #n
int LED::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void LED::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
