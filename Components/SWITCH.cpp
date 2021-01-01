#include "SWITCH.h"

SWITCH::SWITCH(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut)
{
	Selected = false;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void SWITCH::Operate()
{
	//calculate the output status as the inverting of the input pin
	if (UI.AppMode == SIMULATION)
	{
		window* pW{};
		int x, y = 0;
		pW->GetMouseClick(x, y);
		if (x >= m_GfxInfo.x1 && x <= m_GfxInfo.x2 && y >= m_GfxInfo.y1 && y <= m_GfxInfo.y2)
		{
			if (m_OutputPin.getStatus()==LOW)
			{
				m_OutputPin.setStatus(HIGH);
			}
			else
			{
				m_OutputPin.setStatus(LOW);
			}
		}
	}
}


// Function Draw
// Draws 2-input AND gate
void SWITCH::Draw(Output* pOut, bool Selected)
{
	//Call output class and pass gate drawing info to it.
	if (UI.AppMode == SIMULATION)
	{
		if (m_OutputPin.getStatus() == LOW)
		{
			pOut->DrawOpenSWITCH(m_GfxInfo,Selected);
		}
		else
		{
			pOut->DrawClosedSWITCH(m_GfxInfo,Selected);
		}
	}
	else if (UI.AppMode == DESIGN)
	{
		pOut->DrawOpenSWITCH(m_GfxInfo,Selected);
	}
}

int SWITCH::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}
int SWITCH::GetInputPinStatus(int n)
{
	return 0;
}

void SWITCH::setInputPinStatus(int n, STATUS s)
{
}