#include "ChangeSwitch.h"
#include "..\ApplicationManager.h"


ChangeSwitch::ChangeSwitch(ApplicationManager* pApp) :Action(pApp)
{
	Cx = 0;
	Cy = 0;
}

ChangeSwitch::~ChangeSwitch(void)
{
}

void ChangeSwitch::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click on Switch to Open/Close");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void ChangeSwitch::Execute()
{
	ReadActionParameters();
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	Comp = pManager->IsComponent(Cx, Cy);
	Component* IsSwitch = dynamic_cast<SWITCH*>(Comp);
	if (!IsSwitch)
	{
		pOut->PrintMsg("Click on a switch ");

		return;
	}
	bool B = ((SWITCH*)Comp)->GetClosed();
	((SWITCH*)Comp)->SetClosed(!B);
	pManager->Simulate(); 

}

void ChangeSwitch::Label()
{
}
void ChangeSwitch::Undo()
{}

void ChangeSwitch::Redo()
{}

bool ChangeSwitch::CheckArea(int x1, int x2, int y1, int y2, bool Components)
{
	return true;
}