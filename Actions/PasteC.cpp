#include "PasteC.h"
#include "..\ApplicationManager.h"

PasteC::PasteC(ApplicationManager* pApp) :Action(pApp)
{
	Cx = 0;
	Cy = 0;
}

PasteC::~PasteC(void)
{
}

void PasteC::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click to Add item");
	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void PasteC::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	GraphicsInfo GInfo;
	GInfo.x1 = Cx;
	GInfo.y1 = Cy;
	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	//GraphicsInfo GInfo; //Gfx info to be used to construct the component

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	Comp = pManager->GetClipboard();
	
	if (Comp==NULL)
	{
		return;
	}
	// Checks if the desired spot is already taken by a component or a connection
	Component* Compx1, * Compx2, * Compy1, * Compy2;
	// + & - 17 is to account for the label 
	Compx1 = pManager->IsComponent(GInfo.x1, GInfo.y1 - 17); // upper left  (Checks if the upper left corner is inside a component)
	Compx2 = pManager->IsComponent(GInfo.x2, GInfo.y1 - 17); // upper right
	Compy1 = pManager->IsComponent(GInfo.x1, GInfo.y2 + 17); // lower left 
	Compy2 = pManager->IsComponent(GInfo.x2, GInfo.y2 + 17); // lower right


	// Checks that the item is being placed inside the Drawing Area
	if (GInfo.x1 < 0 || GInfo.x2 + 15 > UI.width || GInfo.y1 < (UI.ToolBarHeight + 20) || GInfo.y2 > UI.height - UI.StatusBarHeight || Compx1 || Compx2 || Compy1 || Compy2)
	{
		Output* pOut = pManager->GetOutput();
		Input* pIn = pManager->GetInput();
		pOut->PrintMsg("You can only draw in the drawing area. Click anywhere to continue");
		if (Compx1 || Compx2 || Compy1 || Compy2)
		{
			pOut->PrintMsg("Please avoid overlapping gates. Click anywhere to continue");
		}
		pIn->GetPointClicked(GInfo.x1, GInfo.x1);     // Waits for the user to read the message and clicks to continue

	}
	else

	{
		if (dynamic_cast<AND2*>(Comp))//Checks the component type in clipboard
		{
			Label();
			AND2* pA = new AND2(GInfo, AND2_FANOUT);
			pA->SetLabel(NameTag);
			pManager->AddComponent(pA);
		}
		else if (dynamic_cast<LED*>(Comp))
		{
			Label();
			LED* pA = new LED(GInfo, AND2_FANOUT);
			pA->SetLabel(NameTag);
			pManager->AddComponent(pA);
		}
		else if (dynamic_cast<SWITCH*>(Comp))
		{
			Label();
			SWITCH* pA = new SWITCH(GInfo, AND2_FANOUT);
			pA->SetLabel(NameTag);
			pManager->AddComponent(pA);
		}
		else if (dynamic_cast<AND3*>(Comp))
		{
			Label();
			AND3* pA = new AND3(GInfo, AND2_FANOUT);
			pA->SetLabel(NameTag);
			pManager->AddComponent(pA);
		}
		else if (dynamic_cast<OR2*>(Comp))
		{
			Label();
			OR2* pA = new OR2(GInfo, AND2_FANOUT);
			pA->SetLabel(NameTag);
			pManager->AddComponent(pA);
		}
		else if (dynamic_cast<NOR2*>(Comp))
		{
			Label();
			NOR2* pA = new NOR2(GInfo, AND2_FANOUT);
			pA->SetLabel(NameTag);
			pManager->AddComponent(pA);
		}
		else if (dynamic_cast<BUFF*>(Comp))
		{
			Label();
			BUFF* pA = new BUFF(GInfo, AND2_FANOUT);
			pA->SetLabel(NameTag);
			pManager->AddComponent(pA);
		}
		else if (dynamic_cast<NAND*>(Comp))
		{
			Label();
			NAND* pA = new NAND(GInfo, AND2_FANOUT);
			pA->SetLabel(NameTag);
			pManager->AddComponent(pA);
		}
		else if (dynamic_cast<NOR3*>(Comp))
		{
			Label();
			NOR3* pA = new NOR3(GInfo, AND2_FANOUT);
			pA->SetLabel(NameTag);
			pManager->AddComponent(pA);
		}
		else if (dynamic_cast<NOT*>(Comp))
		{
			Label();
			NOT* pA = new NOT(GInfo, AND2_FANOUT);
			pA->SetLabel(NameTag);
			pManager->AddComponent(pA);
		}
		else if (dynamic_cast<XOR2*>(Comp))
		{
			Label();
			XOR2* pA = new XOR2(GInfo, AND2_FANOUT);
			pA->SetLabel(NameTag);
			pManager->AddComponent(pA);
		}
		else if (dynamic_cast<XOR3*>(Comp))
		{
			Label();
			XOR3* pA = new XOR3(GInfo, AND2_FANOUT);
			pA->SetLabel(NameTag);
			pManager->AddComponent(pA);
		}
		else if (dynamic_cast<XNOR2*>(Comp))
		{
			Label();
			XNOR2* pA = new XNOR2(GInfo, AND2_FANOUT);
			pA->SetLabel(NameTag);
			pManager->AddComponent(pA);
		}
	}
	if (pManager->getItemCut()==true)// item in clipboard is cut
	{
		Comp->setSelected(true);
		pManager->Delete2(Comp);
		pManager->SetClipboard(NULL);
	}
}



void PasteC::Label()
{ 
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	NameTag = pIn->GetSrting(pOut);
}
void PasteC::Undo()
{}

void PasteC::Redo()
{}

bool PasteC::CheckArea(int x1, int x2, int y1, int y2, bool Components)
{
	return true;
}
