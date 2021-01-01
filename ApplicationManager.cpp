#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddORgate2.h"
#include "Actions\Delete.h"
#include "Actions\AddNOTgate.h"
#include "Actions\AddNORgate2.h"
#include "Actions\AddNORgate3.h"
#include "Actions\AddSwitch.h"
#include "Actions\Select.h"


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
		case Go_Back:
			UI.ActiveBar = DesignBar;
			OutputInterface->CreateDesignToolBar();
			break;
		case ADD_GATE:
			UI.ActiveBar = GateBar;
			OutputInterface->CreateGateToolBar();
			break;
		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);
			break;
		case ADD_OR_GATE_2:
			pAct = new AddORgate2(this);
			break;
		case ADD_NOR_GATE_2:
			pAct = new AddNORgate2(this);
			break;
		case ADD_NOR_GATE_3:
			pAct = new AddNORgate3(this);
			break;
		case ADD_CONNECTION:
			//TODO: Create AddConection Action here
			break;
		case ADD_INV:
			pAct = new AddNOTgate(this);
			break;
		case ADD_Switch:
			pAct = new AddSwitch(this);
			break;
		case SELECT:
			pAct = new Select(this);
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


Component* ApplicationManager::IsComponent(int x, int y)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->Inarea(x, y))
		{
			return  CompList[i];
		}
	}
	return NULL;
}


void ApplicationManager::UpdateInterface()
{
	OutputInterface->ClearDrawingArea();
	for(int i=0; i<CompCount; i++)
		CompList[i]->Draw(OutputInterface,CompList[i]->getSelected());

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

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
	
}