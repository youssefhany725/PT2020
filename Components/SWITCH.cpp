#include "SWITCH.h"

SWITCH::SWITCH(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Component(r_GfxInfo), m_OutputPin(r_FanOut)
{
	Closed = false;
	
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void SWITCH::Operate()
{
	
	if (Closed)
	{
		m_OutputPin.setStatus(HIGH);
	}
	else
	{
		m_OutputPin.setStatus(LOW);
	}
	
}


// Function Draw
// Draws Open/Closed Switch
void SWITCH::Draw(Output* pOut, bool Selected)
{


	//Call output class and pass gate drawing info to it.

	if (Closed)
	{
		pOut->DrawClosedSWITCH(m_GfxInfo, Selected);

	}
	else
	{
		pOut->DrawOpenSWITCH(m_GfxInfo, Selected);
	}
	pOut->PrintLabel(m_GfxInfo.x1, m_GfxInfo.y1 - 17, GetLabel());
}

int SWITCH::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}
int SWITCH::GetInputPinStatus(int n)
{
	return -1;
}

void SWITCH::setInputPinStatus(int n, STATUS s)
{         
}

void SWITCH::SetClosed(bool b)
{
	Closed = b;
}
bool SWITCH::GetClosed()
{
	return Closed;
}

OutputPin* SWITCH::getOP()
{
	return &m_OutputPin;
}

void SWITCH::SaveComponent(ofstream& fout)
{

	if (GetLabel().length() == 0)
	{
		SetLabel("SWITCH");
	}
	fout << "SWITCH" << "\t" << MyID << "\t" << GetLabel() << "\t";
	fout << m_GfxInfo.x1 + UI.AND2_Width / 2 << "\t" << m_GfxInfo.y1 + UI.AND2_Height / 2 << endl;
}

void SWITCH::SaveConnection(int, int, int, ofstream&)
{}

void SWITCH::LoadCircuit(string label, int ID)
{
	SetLabel(label);
	MyID = ID;
}