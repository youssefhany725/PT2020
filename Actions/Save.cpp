#include "Save.h"
#include "..\ApplicationManager.h"

Save::Save(ApplicationManager* pApp) :Action(pApp)
{
	Cx = 0;
	Cy = 0;
}

Save::~Save()
{
}

void Save::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Action Save: Saving circuit to a file. Enter file name.");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void Save::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	Component* Comp;
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	string name;
	do
	{
		pOut->PrintMsg("file name :");
		name = pIn->GetInt(pOut);
	} while (name == "");

	name += ".txt";

	ofstream fout;
	fout.open(name);
	pManager->SaveCircuit( fout);
	fout.close();
}

void Save::Label()
{}

bool Save::CheckArea(int x1, int x2, int y1, int y2, bool Components)
{
	return true;
}

void Save::Undo()
{}

void Save::Redo()
{}

