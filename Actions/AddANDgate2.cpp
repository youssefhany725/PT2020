#include "AddANDgate2.h"
#include "..\ApplicationManager.h"

AddANDgate2::AddANDgate2(ApplicationManager *pApp):Action(pApp)
{
}

AddANDgate2::~AddANDgate2(void)
{
}

void AddANDgate2::ReadActionParameters()
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

void AddANDgate2::Execute()
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
	//width = 1500, height = 750
	Component* Compx1, *Compx2, *Compy1, *Compy2;
	Compx1 = pManager->IsComponent(GInfo.x1, GInfo.y1); // upper left
	Compx2 = pManager->IsComponent(GInfo.x2, GInfo.y1); // upper right
	Compy1 = pManager->IsComponent(GInfo.x1, GInfo.y2); // lower left
	Compy2 = pManager->IsComponent(GInfo.x2, GInfo.y2); // lower right
	if (GInfo.x1 < 0 || GInfo.x2+15 > UI.width || GInfo.y1 < (UI.ToolBarHeight + 20) || GInfo.y2 > UI.height - UI.StatusBarHeight || Compx1 || Compx2 || Compy1 || Compy2)
	{
		Output* pOut = pManager->GetOutput(); 
		Input* pIn = pManager->GetInput();
		pOut->PrintMsg("You can only draw in the drawing area. Click anywhere to continue");
		if (Compx1 || Compx2 || Compy1 || Compy2)
		{
			pOut->PrintMsg("Please avoid overlapping gates. Click anywhere to continue");
		}
		pIn->GetPointClicked(GInfo.x1, GInfo.x1);     // mlhash lazma aktr mn eno ystna el sha5s ydoos 3l mouse 3lshan 5ater yel7a2 ye2ra el reasla
		
	}
	else
	{
		Label();
		AND2* pA = new AND2(GInfo, AND2_FANOUT);
		pA->SetLabel(NameTag);
		pManager->AddComponent(pA);
	}
}

void AddANDgate2::Label()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	NameTag = pIn->GetSrting(pOut);
	//AND2.NameTag = NameTag;
}
void AddANDgate2::Undo()
{}

void AddANDgate2::Redo()
{}

