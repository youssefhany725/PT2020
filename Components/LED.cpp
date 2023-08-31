#include "LED.h"

LED::LED(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Component(r_GfxInfo)
{
	ON = false;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void LED::Operate()
{
	//caclulate the output status as the input
	if (m_InputPin.getStatus() == HIGH)
	{
		ON = true;
	}
	else if (m_InputPin.getStatus() == LOW)
	{
		ON = false;
	}
}


// Function Draw
// Draws Led
void LED::Draw(Output* pOut, bool Selected)
{
	//Call output class and pass LED drawing info to it.
	pOut->DrawLED(m_GfxInfo, Selected, ON);
	pOut->PrintLabel(m_GfxInfo.x1, m_GfxInfo.y1 - 17, GetLabel());
}

//returns status of outputpin
int LED::GetOutPinStatus()
{
	return -1;
}

int LED::GetInputPinStatus(int n)
{
	return m_InputPin.getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void LED::setInputPinStatus(int n, STATUS s)
{
	m_InputPin.setStatus(s);
}

InputPin* LED::getIP()
{
	return &m_InputPin;
}


bool LED::IPnotConnected()
{
	return m_InputPin.getIPnotconnected();
}

void LED::SaveComponent(ofstream& fout)
{
	if (GetLabel().length() == 0)
	{
		SetLabel("LED");
	}
	fout << "LED" << "\t" << MyID << "\t" << GetLabel() << "\t";
	fout << m_GfxInfo.x1 + UI.AND2_Width / 2 << "\t" << m_GfxInfo.y1 + UI.AND2_Height / 2 << endl;
}

void LED::SaveConnection(int, int, int, ofstream&)
{}

void LED::LoadCircuit(string label, int ID)
{
	SetLabel(label);
	MyID = ID;
}