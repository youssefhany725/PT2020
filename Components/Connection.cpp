#include "Connection.h"

Connection::Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin,InputPin *pDstPin):Component(r_GfxInfo)	
	
{
	SrcPin = pSrcPin;
	DstPin = pDstPin;
}
void Connection::setSourcePin(OutputPin *pSrcPin)
{	SrcPin = pSrcPin;	}

OutputPin* Connection::getSourcePin()
{	return SrcPin;	}


void Connection::setDestPin(InputPin *pDstPin)
{	DstPin = pDstPin;	}

InputPin* Connection::getDestPin()
{	return DstPin;	}


void Connection::Operate()
{
	//Status of connection destination pin = status of connection source pin
	DstPin->setStatus((STATUS)SrcPin->getStatus());
}

void Connection::Draw(Output* pOut, bool Selecteed)
{
	pOut->DrawConnection(m_GfxInfo, Selected);
	pOut->PrintLabel(m_GfxInfo.x1 + 5, m_GfxInfo.y1 - 17 - 5, GetLabel());
}

int Connection::GetOutPinStatus()	//returns status of outputpin if LED, return -1
{
	return DstPin->getStatus();
}

int Connection::GetInputPinStatus(int n)	//returns status of Inputpin # n if SWITCH, return -1
{
	return SrcPin->getStatus();	//n is ignored as connection has only one input pin (src pin)	
}

void Connection::setInputPinStatus(int n, STATUS s)
{
	SrcPin->setStatus(s);
}

void Connection::ChangeSourceInfo(GraphicsInfo SourceInfo)
{
	// In case of source component, we only need x1 & y1
	m_GfxInfo.x1 = SourceInfo.x1;
	m_GfxInfo.y1 = SourceInfo.y1;
}

void Connection::ChangeDstInfo(GraphicsInfo DstInfo)
{
	// In case of destination, we only need x2 & y2
	m_GfxInfo.x2 = DstInfo.x2;
	m_GfxInfo.y2 = DstInfo.y2;
}


void Connection::SaveComponent(ofstream& fout)
{}

void Connection::SaveConnection(int SrcCompID, int DstCompID, int PinNo, ofstream& fout)
{

	fout << SrcCompID << "\t" << DstCompID << "\t" << PinNo << endl;

}

void Connection::LoadCircuit(string label, int id)
{
	SetLabel(label);
}