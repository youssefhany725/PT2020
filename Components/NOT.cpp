#include "NOT.h"

NOT::NOT(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(1, r_FanOut)
{
	
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void NOT::Operate()
{
	//calculate the output status as the inverting of the input pin
	int input = 0;
	for (int i = 1; i <= m_Inputs; i++)
	{
		input += m_InputPins[i].getStatus();
	}
	if (input == 0)
	{
		m_OutputPin.setStatus(HIGH);
	}
	else if (input == 1)
	{
		m_OutputPin.setStatus(LOW);
	}

}


// Function Draw
// Draws NOT gate
void NOT::Draw(Output* pOut, bool Selected)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawNOT(m_GfxInfo, Selected);
	pOut->PrintLabel(m_GfxInfo.x1, m_GfxInfo.y1 - 17, GetLabel());
}

//returns status of outputpin
int NOT::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NOT::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NOT::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}

void NOT::SaveComponent(ofstream& fout)
{
	
	if (GetLabel().length() == 0)
	{
		SetLabel("NOT");
	}
	fout << "NOT" << "\t" << MyID << "\t" << GetLabel() << "\t";
	fout << m_GfxInfo.x1 + UI.AND2_Width / 2 << "\t" << m_GfxInfo.y1 + UI.AND2_Height / 2 << endl;
}

void NOT::SaveConnection(int, int, int, ofstream&)
{}

void NOT::LoadCircuit(string label, int ID)
{
	SetLabel(label);
	MyID = ID;
}