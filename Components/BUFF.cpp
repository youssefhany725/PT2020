#include "BUFF.h"
BUFF::BUFF(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void BUFF::Operate()
{
	//caclulate the output status from the Buffer
	
	m_OutputPin.setStatus(m_InputPins[m_Inputs].getStatus());
}


// Function Draw
// Draws BUFFER gate
void BUFF::Draw(Output* pOut, bool Selected)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawBUFF(m_GfxInfo, Selected);
	pOut->PrintLabel(m_GfxInfo.x1, m_GfxInfo.y1 - 17, GetLabel());
}

//returns status of outputpin
int BUFF::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int BUFF::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void BUFF::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

void BUFF::SaveComponent(ofstream& fout)
{
	
	if (GetLabel().length() == 0)
	{
		SetLabel("BUFFER");
	}
	fout << "BUFFER" << "\t" << MyID << "\t" << GetLabel() << "\t";
	fout << m_GfxInfo.x1 + UI.AND2_Width / 2 << "\t" << m_GfxInfo.y1 + UI.AND2_Height / 2 << endl;
}

void BUFF::SaveConnection(int, int, int, ofstream&)
{}

void BUFF::LoadCircuit(string label, int ID)
{
	SetLabel(label);
	MyID = ID;
}