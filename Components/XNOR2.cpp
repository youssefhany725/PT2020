#include "XNOR2.h"

XNOR2::XNOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void XNOR2::Operate()
{
	//caclulate the output status as the XNORing of the two input pins

	
	int sum = 0;
	for (int i = 1; i <= m_Inputs; i++)
	{
		sum += m_InputPins[i].getStatus();
	}
	if (sum % 2 == 0)
	{
		m_OutputPin.setStatus(HIGH);
	}
	else
	{
		m_OutputPin.setStatus(LOW);
	}
	
}


// Function Draw
// Draws 2-input XNOR gate
void XNOR2::Draw(Output* pOut, bool Selected)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawXNOR2(m_GfxInfo, Selected);
	pOut->PrintLabel(m_GfxInfo.x1, m_GfxInfo.y1 - 17, GetLabel());
}

//returns status of outputpin
int XNOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XNOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin to HIGH or LOW
void XNOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

void XNOR2::SaveComponent(ofstream& fout)
{
	if (GetLabel().length() == 0)
	{
		SetLabel("XNOR2");
	}
	fout << "XNOR2" << "\t" << MyID << "\t" << GetLabel() << "\t";
	fout << m_GfxInfo.x1 + UI.AND2_Width / 2 << "\t" << m_GfxInfo.y1 + UI.AND2_Height / 2 << endl;
}

void XNOR2::SaveConnection(int, int, int, ofstream&)
{}

void XNOR2::LoadCircuit(string label, int ID)
{
	SetLabel(label);
	MyID = ID;
}