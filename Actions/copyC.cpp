#include "copyC.h"
#include "..\ApplicationManager.h"

copyC::copyC(ApplicationManager* pApp) :Action(pApp)
{
	Cx = 0;
	Cy = 0;
}

copyC::~copyC(void)
{
}

void copyC::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click on the item to be copied");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void copyC::Execute()
{
	
	ReadActionParameters();
	Comp = pManager->IsComponent(Cx, Cy);
	pManager->SetClipboard(Comp);
	pManager->setItemCut(false);
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMsg("Item Copied, Click anywhere to continue");
	int wait1 = 0;
	int wait2 = 0;
	pIn->GetPointClicked(wait1, wait2);

}

void copyC::Label()
{
}
void copyC::Undo()
{}

void copyC::Redo()
{}

bool copyC::CheckArea(int x1, int x2, int y1, int y2, bool Components)
{
	return true;
}

