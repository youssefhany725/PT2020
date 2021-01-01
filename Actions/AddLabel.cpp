// E7TMAL KBEER AMSA7 EL CLASS. aw msh hms7o, bs h5leeh by3adel 3la gate mwgooda asln

#include "AddLabel.h"
#include "..\ApplicationManager.h"

AddLabel::AddLabel(ApplicationManager* pApp) :Action(pApp)
{
}

AddLabel::~AddLabel(void)
{
}

void AddLabel::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click on a component to edit its label.");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();  // ha7ot el function el tanya el kont 3amelha lel label

}

void AddLabel::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();


	//GraphicsInfo GInfo; //Gfx info to be used to construct the XNOR2 gate

	//////GInfo.x1 = Cx - Cx / 2;
	//////GInfo.x2 = Cx + Cx / 2;
	//////GInfo.y1 = Cy - Cx / 2;
	//////GInfo.y2 = Cy + Cx / 2;
	//////

	//ApplicationManager* pApp;  // mlhash lazma
	Component* Comp;
	Comp = pManager->IsComponent(Cx, Cy);
	if (Comp)
	{
		string msg;
		Output* pOut = pManager->GetOutput();
		Input* pIn = pManager->GetInput();

		msg = pIn->GetSrting(pOut);

		pManager->EditLabel(Comp, msg);
	}
	

	//XOR3* pA = new XOR3(GInfo, AND2_FANOUT);
	//pManager->AddComponent(pA);
}

void AddLabel::Label()
{}

void AddLabel::Undo()
{}

void AddLabel::Redo()
{}

