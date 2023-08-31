#include "cutC.h"
#include "..\ApplicationManager.h"
#include "..\Components\AND2.h"

cutC::cutC(ApplicationManager* pApp) :Action(pApp)
{
	Cx = 0;
	Cy = 0;
}

cutC::~cutC(void)
{
}

void cutC::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMsg("Click on the item to be cut");
	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void cutC::Execute()
{
	
	ReadActionParameters();

	Comp = (pManager->IsComponent(Cx, Cy));
	pManager->SetClipboard(Comp);
	pManager->setItemCut(true);
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMsg("Item Cut, Click anywhere to continue");
	int wait1 = 0;
	int wait2 = 0;
	pIn->GetPointClicked(wait1, wait2);

}
void cutC::Label()
{}

void cutC::Undo()
{}

void cutC::Redo()
{}

bool cutC::CheckArea(int x1, int x2, int y1, int y2, bool Components)
{
	return true;
}
