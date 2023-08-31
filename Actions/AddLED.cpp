#include "AddLED.h"
#include "..\ApplicationManager.h"

AddLED::AddLED(ApplicationManager *pApp):Action(pApp)
{
	Cx = 0;
	Cy = 0;
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
}

AddLED::~AddLED(void)
{
}

void AddLED::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Output Led: Click to add the Led");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();
	
}

void AddLED::Execute()
{
	//Get Center point of the LED
	ReadActionParameters();
	
	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;
	
	GraphicsInfo GInfo; //Gfx info to be used to construct the LED 
	
	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	
	

	bool Components = false;
	bool Area = CheckArea(GInfo.x1, GInfo.x2, GInfo.y1, GInfo.y2, Components);

	if (Area)
	{
		Output* pOut = pManager->GetOutput();
		Input* pIn = pManager->GetInput();
		pOut->PrintMsg("You can only draw in the drawing area. Click anywhere to continue");
		if (Components)
		{
			pOut->PrintMsg("Please avoid overlapping gates. Click anywhere to continue");
		}
		pIn->GetPointClicked(GInfo.x1, GInfo.x1);    
	}
	else
	{
		Label();
		LED* pA = new LED(GInfo, AND2_FANOUT);
		pA->SetLabel(NameTag);
		pManager->AddComponent(pA);

		
	}
}

void AddLED::Label()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	NameTag = pIn->GetSrting(pOut);
}

bool AddLED::CheckArea(int x1, int x2, int y1, int y2, bool Components)
{
	// Checks if the desired spot is already taken by a component or a connection
	Component* CompLx1, * CompLx2, * CompLy1, * CompLy2, * Compx1, * Compx2, * Compy1, * Compy2;
	CompLx1 = pManager->IsComponent(x1, y1 - 17); // upper left 
	CompLx2 = pManager->IsComponent(x2, y1 - 17); // upper right
	CompLy1 = pManager->IsComponent(x1, y2 + 17); // lower left   
	CompLy2 = pManager->IsComponent(x2, y2 + 17); // lower right 
	Compx1 = pManager->IsComponent(x1, y1); // upper left 
	Compx2 = pManager->IsComponent(x2, y1); // upper right
	Compy1 = pManager->IsComponent(x1, y2); // lower left 
	Compy2 = pManager->IsComponent(x2, y2); // lower right

	// Checks that the item is being placed inside the Drawing Area
	if (x1 < 0 || x2 + 15 > UI.width || y1 < (UI.ToolBarHeight + 20) || y2 > UI.height - UI.StatusBarHeight || CompLx1 || CompLx2 || CompLy1 || CompLy2 || Compx1 || Compx2 || Compy1 || Compy2)
	{
		Components = false;
		if (CompLx1 || CompLx2 || CompLy1 || CompLy2 || Compx1 || Compx2 || Compy1 || Compy2)
		{
			Components = true;
		}
		return true;
	}
	return false;
}

void AddLED::Undo()
{}

void AddLED::Redo()
{}

