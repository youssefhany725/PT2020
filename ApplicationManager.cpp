#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddXORgate2.h"
#include "Actions\AddXNORgate2.h"
#include "Actions\AddXORgate3.h"
#include "Actions\AddLabel.h"


ApplicationManager::ApplicationManager()
{
	CompCount = 0;

	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;		
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return InputInterface->GetUserAction();
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);
			break;
		/*
		case ADD_XOR_GATE_2:
			pAct = new AddXORgate2(this);
			break;
		case ADD_XNOR_GATE_2:
			pAct = new AddXNORgate2(this);
			break;
			*/
		case ADD_XOR_GATE_3:
			pAct = new AddXORgate3(this);
			break;
		case EDIT_Label:
			pAct = new AddLabel(this);
			break;
		//case ADD_Label:
		case Go_Back:
			UI.ActiveBar = DesignBar;
			OutputInterface->PrintMsg("Action: create Design toolbar, Click anywhere");  // momkn nb2a nsheel el satr dh l2n lw fy gate byt3mlo overwrite 3la tool fa byb2a shaklo w7sh
			OutputInterface->ClearDesignToolBar();
			OutputInterface->CreateDesignToolBar();
			break;
		case ADD_GATE:
			UI.ActiveBar = GateBar;
			OutputInterface->PrintMsg("Action: create Gate toolbar, Click anywhere");  // momkn nb2a nsheel el satr dh l2n lw fy gate byt3mlo overwrite 3la tool fa byb2a shaklo w7sh
			OutputInterface->ClearDesignToolBar();
			OutputInterface->CreateGateToolBar();
			break;
			
		case ADD_CONNECTION:
			//TODO: Create AddConection Action here
			break;
	

		case EXIT:
			///TODO: create ExitAction here
			break;
	}
	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
	OutputInterface->ClearDrawingArea();
	for(int i=0; i<CompCount; i++)
		CompList[i]->Draw(OutputInterface);

}

////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

Component* ApplicationManager::IsComponent(int x, int y)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->Inarea(x,y))
		{
			return  CompList[i];
		}
	}
	return NULL;
}

void ApplicationManager::EditLabel(Component* Comp, string msg)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (Comp == CompList[i])
		{
			Comp->SetLabel(msg);
		}
	}
}

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
	
}