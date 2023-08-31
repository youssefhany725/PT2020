#include "AND2.h"

AND2::AND2(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void AND2::Operate()
{
	//caclulate the output status as the ANDing of the two input pins
	int OP = 1;
	//Add you code here
	for (int i = 1; i <= m_Inputs; i++)
	{
		OP = OP * m_InputPins[i].getStatus();
	}
	if (OP == 1)
	{
		m_OutputPin.setStatus(HIGH);
	}
	else
	{
		m_OutputPin.setStatus(LOW);
	}
}


// Function Draw
// Draws 2-input AND gate
void AND2::Draw(Output* pOut, bool Selected)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawAND2(m_GfxInfo, Selected);
	//pOut->PrintLabel(m_GfxInfo.x1, m_GfxInfo.y1 - 17, NameTag);
	pOut->PrintLabel(m_GfxInfo.x1, m_GfxInfo.y1 - 17, GetLabel());

}

//returns status of outputpin
int AND2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int AND2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void AND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

void AND2::SaveComponent(ofstream& fout)
{
	if (GetLabel().length() == 0)
	{
		SetLabel("AND2");
	}
	fout << "AND2" << "\t" << MyID << "\t" << GetLabel() << "\t";
	fout << m_GfxInfo.x1 + UI.AND2_Width / 2 << "\t" << m_GfxInfo.y1 + UI.AND2_Height / 2 << endl;
}

void AND2::SaveConnection(int, int, int, ofstream&)
{}

void AND2::LoadCircuit(string label, int ID)
{

	SetLabel(label);
	MyID = ID;
	
}

