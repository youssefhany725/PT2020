#include "Select.h"
#include "..\ApplicationManager.h"



Select::Select (ApplicationManager* pApp) : Action(pApp)
{
}

Select::~Select(void)
{
}

void Select::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Select");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

	//we wil get a compenent pointer here

}

void Select::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners
	Output* pOut = pManager->GetOutput();
	Component* pComp = pManager->IsComponent(Cx, Cy);
	if (pComp != NULL)
	{
		if (pComp->getSelected() == true)
			pComp->setSelected(false);
		else
			pComp->setSelected(true);
	}

}

void Select::Undo()
{}

void Select::Redo()
{}