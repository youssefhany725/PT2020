#include "LoadCircuits.h"
#include "..\ApplicationManager.h"
#include <cstring>
#include <fstream>



LoadCircuits::LoadCircuits(ApplicationManager* pApp) : Action(pApp)
{
	Cx = 0;
	Cy = 0;
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;
}

LoadCircuits::~LoadCircuits(void)
{
}

void LoadCircuits::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Action Load: Click anywhere to enter name of file. Warning file must be in the same folder as the program!");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

	

}

void LoadCircuits::Execute()
{
	
	ReadActionParameters();

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	string name;
	do
	{
		pOut->PrintMsg("file name :");
		name = pIn->GetInt(pOut);
	} while (name == "");

	name += ".txt";
	ifstream fin;
	fin.open(name, ios::in);
	pManager->Load(fin);
}

void LoadCircuits::Label()
{}

void LoadCircuits::Undo()
{}

void LoadCircuits::Redo()
{}

bool LoadCircuits::CheckArea(int x1, int x2, int y1, int y2, bool Components)
{
	return true;
}