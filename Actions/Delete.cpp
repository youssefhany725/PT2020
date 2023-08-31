#include "Delete.h"
#include "..\ApplicationManager.h"



Delete::Delete(ApplicationManager* pApp) :Action(pApp)
{
	Cx = 0;
	Cy = 0;
}

Delete::~Delete()
{
}

void Delete::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Action Delete: Click anywhere to continue.");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

	//we wil get a compenent pointer here

}

void Delete::Execute()
{
	ReadActionParameters();

	pManager->Delete1();
	


}

void Delete::Label()
{}

bool Delete::CheckArea(int x1, int x2, int y1, int y2, bool Components)
{
	return true;
}

void Delete::Undo()
{}

void Delete::Redo()
{}