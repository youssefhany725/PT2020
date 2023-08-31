#include "Select.h"
#include "..\ApplicationManager.h"



Select::Select(ApplicationManager* pApp) : Action(pApp)
{
	Cx = 0;
	Cy = 0;
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
	pOut->PrintMsg("Action Select: Click on a component to select it");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

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
	else
	{
		pOut->PrintMsg("A click on the drawing area");
	}

}

void Select::Label()
{}

bool Select::CheckArea(int x1, int x2, int y1, int y2, bool Components)
{
	return true;
}

void Select::Undo()
{}

void Select::Redo()
{}