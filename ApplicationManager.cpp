#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddANDgate3.h"
#include "Actions\AddNANDgate.h"
#include "Actions\AddBUFFERgate.h"
#include "Actions\AddConnection.h"


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
			OutputInterface->PrintMsg("Action: create Design toolbar, Click anywhere");
			OutputInterface->ClearDesignToolBar();
			OutputInterface->CreateDesignToolBar();
			break;
		case ADD_GATE:
			UI.ActiveBar = GateBar;
			OutputInterface->PrintMsg("Action: create Gate toolbar, Click anywhere");
			OutputInterface->ClearDesignToolBar();
			OutputInterface->CreateGateToolBar();
			break;
		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);
			break;
		case ADD_AND_GATE_3:
			pAct = new AddANDgate3(this);
			break;
		case ADD_NAND_GATE_2:
			pAct = new AddNANDgate(this);
			break;
		case ADD_Buff:
			pAct = new AddBUFFERgate(this);
			break;

		case ADD_CONNECTION:
			//TODO: Create AddConection Action here
			pAct = new AddConnection(this);
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

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
	
}