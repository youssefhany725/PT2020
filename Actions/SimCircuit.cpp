#include "SimCircuit.h"
#include "..\ApplicationManager.h"

SimCircuit::SimCircuit(ApplicationManager* pApp) :Action(pApp)
{
}
SimCircuit::~SimCircuit(void)
{
}
void SimCircuit::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();	
	pOut->ClearStatusBar();

}

void SimCircuit::Execute()
{
	ReadActionParameters();
	pManager->Simulate();

}

void SimCircuit::Undo()
{
}
void SimCircuit::Redo()
{
}
void SimCircuit::Label()
{
}

bool SimCircuit::CheckArea(int x1, int x2, int y1, int y2, bool Components)
{
	return true;
}