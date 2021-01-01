#include "Delete.h"
#include "ApplicationManager.h"



Delete::Delete(ApplicationManager* pApp) :Action(pApp)
{
}

Delete::~Delete(void)
{
}

void Delete::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input AND Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void Delete::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners





}

void Delete::Undo()
{}

void Delete::Redo()
{}