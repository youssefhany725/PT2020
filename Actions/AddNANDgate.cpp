#include "AddNANDgate.h"
#include "..\ApplicationManager.h"

AddNANDgate::AddNANDgate(ApplicationManager* pApp) :Action(pApp)
{
}

AddNANDgate::~AddNANDgate(void)
{
}

void AddNANDgate::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input NAND Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddNANDgate::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	NAND* pA = new NAND(GInfo, NAND_FANOUT);
	pManager->AddComponent(pA);
}

void AddNANDgate::Undo()
{}

void AddNANDgate::Redo()
{}

