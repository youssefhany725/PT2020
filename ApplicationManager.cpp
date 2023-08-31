#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddXORgate2.h"
#include "Actions\AddXNORgate2.h"
#include "Actions\AddXORgate3.h"
#include "Actions\EditC.h"
#include "Actions\AddLed.h"
#include "Actions\AddORgate2.h"
#include "Actions\AddNOTgate.h"
#include "Actions\AddNORgate2.h"
#include "Actions\AddNORgate3.h"
#include "Actions\AddSwitch.h"
#include "Actions\AddANDgate3.h"
#include "Actions\AddNANDgate.h"
#include "Actions\AddBUFFERgate.h"
#include "Actions\AddConnection.h"
#include "Actions\Select.h"
#include "Actions\Delete.h"
#include "Actions\copyC.h"
#include "Actions\cutC.h"
#include "Actions\PasteC.h"
#include "Actions\SimCircuit.h"
#include "Actions\ChangeSwitch.h"

#include "Actions\Save.h"
#include "Actions\LoadCircuits.h"


#include <fstream>
#include <istream>



int Component::ID = 0;

ApplicationManager::ApplicationManager()
{
	Clipboard = NULL;
	CompCount = 0;
	IteminClipboard = false;
	ItemCut = false;
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
			pAct = new AddConnection(this);
			break;
		case ADD_XOR_GATE_2:
			pAct = new AddXORgate2(this);
			break;
		case ADD_XNOR_GATE_2:
			pAct = new AddXNORgate2(this);
			break;
		case ADD_XOR_GATE_3:
			pAct = new AddXORgate3(this);
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
		case ADD_INV:
			pAct = new AddNOTgate(this);
			break;
		case ADD_Switch:
			pAct = new AddSwitch(this);
			break;
		case ADD_LED:
			pAct = new AddLED(this);
			break;
		case EDIT_Label:
			pAct = new EditC(this);
			break;
		case SELECT:
			pAct = new Select(this);
			break;
		case COPY:
			pAct = new copyC(this);
			break;
		case CUT:
			pAct = new cutC(this);
			break;
		case PASTE:
			pAct = new PasteC(this);
			break;
		case DEL:
			pAct = new Delete(this);
			break;
		case CLEAR:
			ClearData();
			break;
		case SAVE:
			pAct = new Save(this);
			break;
		case LOAD:
			pAct = new LoadCircuits(this);
			break;
		case SimulateCircuit:
			
			pAct = new SimCircuit(this);
			break;
		case Validate_Circuit:
			if (ValidCir() == true)
			{
				OutputInterface->PrintMsg("Circuit is valid");
				int click11 = 0;
				int click22 = 0;
				InputInterface->GetPointClicked(click22, click11);
			}
			else
			{
				OutputInterface->PrintMsg("Circuit is invalid");
				int click11 = 0;
				int click22 = 0;
				InputInterface->GetPointClicked(click22, click11);
			}
			break;
		case Change_Switch:
			pAct = new ChangeSwitch(this);
			break;
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
		case DSN_MODE:
			UI.AppMode = DESIGN;
			OutputInterface->PrintMsg("Action: create Design toolbar, Click anywhere");
			OutputInterface->ClearDesignToolBar();
			OutputInterface->CreateDesignToolBar();
			break;
		case SIM_MODE:
			if (ValidCir() == true)
			{
				UI.AppMode = SIMULATION;
				Simulate();
				OutputInterface->PrintMsg("Action: create Simulation toolbar, Click anywhere");
				OutputInterface->ClearDesignToolBar();
				OutputInterface->CreateSimulationToolBar();
			}
			else
			{
				OutputInterface->PrintMsg("Check that all components are connected, Click anywhere to continue");
				int click11 = 0;
				int click22 = 0;
				InputInterface->GetPointClicked(click22, click11);
			}
			
			break;
		
		case EXIT:
			ClearData();     // Deletes all items before exiting
			OutputInterface->PrintMsg("Action: Exit program, Click anywhere");
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
		CompList[i]->Draw(OutputInterface, CompList[i]->getSelected());

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
		Component* C = dynamic_cast<Connection*>(CompList[i]);
		if (!C)    // Checks to make sure it's not a connection
		{
			if (CompList[i]->Inarea(x, y))    // all components except connection call this function
			{
				return  CompList[i];
			}
		}
		else
		{
			if (CompList[i]->InConnection(x, y))  // only connection calls this function
			{
				return CompList[i];
			}
		}
		
	}
	return NULL;
}
////////////////////////////////////////////////////////////////////
Component* ApplicationManager::IsConnection(int x, int y)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->InConnection(x, y))
		{
			return  CompList[i];
		}
	}
	return NULL;
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::ClearData()
{
	for (int i = 0; i < CompCount; i++)
	{
		CompList[i]->setSelected(true);
	}
	Delete1();
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::Load(ifstream& finput)
{
	ClearData();
	int LoadedCount;
	finput >> LoadedCount;
	string TypeOfGate;
	int ID;
	string label;
	GraphicsInfo GInfo;
	int CoordinateX;
	int CoordinateY;
	for (int i = 0; i < LoadedCount; i++)
	{
		finput >> TypeOfGate >> ID >> label >> CoordinateX >> CoordinateY;
		GInfo.x1 = CoordinateX - UI.AND2_Width / 2;
		GInfo.x2 = CoordinateX + UI.AND2_Width / 2;
		GInfo.y1 = CoordinateY - UI.AND2_Height / 2;
		GInfo.y2 = CoordinateY + UI.AND2_Height / 2;
		if (TypeOfGate == "AND2")
		{
			AND2* pA = new AND2(GInfo, AND2_FANOUT);
			AddComponent(pA);
			CompList[i]->LoadCircuit(label, ID);
		}
		else if (TypeOfGate == "AND3")
		{
			AND3* pA = new AND3(GInfo, AND2_FANOUT);
			AddComponent(pA);
			CompList[i]->LoadCircuit(label, ID);
		}
		else if (TypeOfGate == "OR2")
		{
			OR2* pA = new OR2(GInfo, AND2_FANOUT);
			AddComponent(pA);
			CompList[i]->LoadCircuit(label, ID);
		}
		else if (TypeOfGate == "NOT")
		{
			NOT* pA = new NOT(GInfo, AND2_FANOUT);
			AddComponent(pA);
			CompList[i]->LoadCircuit(label, ID);
		}
		else if (TypeOfGate == "SWITCH")
		{
			SWITCH* pA = new SWITCH(GInfo, AND2_FANOUT);
			AddComponent(pA);
			CompList[i]->LoadCircuit(label, ID);
		}
		else if (TypeOfGate == "NOR2")
		{
			NOR2* pA = new NOR2(GInfo, AND2_FANOUT);
			AddComponent(pA);
			CompList[i]->LoadCircuit(label, ID);
		}
		else if (TypeOfGate == "NOR3")
		{
			NOR3* pA = new NOR3(GInfo, AND2_FANOUT);
			AddComponent(pA);
			CompList[i]->LoadCircuit(label, ID);
		}
		else if (TypeOfGate == "NAND")
		{
			NAND* pA = new NAND(GInfo, AND2_FANOUT);
			AddComponent(pA);
			CompList[i]->LoadCircuit(label, ID);
		}
		else if (TypeOfGate == "XOR2")
		{
			XOR2* pA = new XOR2(GInfo, AND2_FANOUT);
			AddComponent(pA);
			CompList[i]->LoadCircuit(label, ID);
		}
		else if (TypeOfGate == "XOR3")
		{
			XOR3* pA = new XOR3(GInfo, AND2_FANOUT);
			AddComponent(pA);
			CompList[i]->LoadCircuit(label, ID);
		}
		else if (TypeOfGate == "XNOR2")
		{
			XNOR2* pA = new XNOR2(GInfo, AND2_FANOUT);
			AddComponent(pA);
			CompList[i]->LoadCircuit(label, ID);
		}
		else if (TypeOfGate == "BUFFER")
		{
			BUFF* pA = new BUFF(GInfo, AND2_FANOUT);
			AddComponent(pA);
			CompList[i]->LoadCircuit(label, ID);
		}
		else if (TypeOfGate == "LED")
		{
			LED* pA = new LED(GInfo, AND2_FANOUT);
			AddComponent(pA);
			CompList[i]->LoadCircuit(label, ID);
		}
	}
	string ConnectionChecker;
	finput >> ConnectionChecker;
	int SourceId, DestId, PinNo;
	GraphicsInfo SourceInfo;
	GraphicsInfo DestInfo;
	OutputPin* SourcePin;
	InputPin* DestPin;
	Component* F;
	if (ConnectionChecker == "Connections")
	{
		Action* pAct = new AddConnection(this);
		while (!finput.eof())
		{
			finput >> SourceId >> DestId >> PinNo;
			if (SourceId != -1)
			{
				for (int i = 0; i < CompCount; i++)
				{
					F = dynamic_cast<Connection*>(CompList[i]);
					if (!F)
					{
						if (SourceId == CompList[i]->GetmyID())
						{
							F = dynamic_cast<SWITCH*>(CompList[i]);
							if (F)
							{
								SourceInfo = ((AddConnection*)pAct)->ChangeSource(CompList[i]);
								SourcePin = ((SWITCH*)CompList[i])->getOP();
								
							}
							else
							{
								SourceInfo = ((AddConnection*)pAct)->ChangeSource(CompList[i]);
								SourcePin = ((Gate*)CompList[i])->getOP();
							}
						}
						if (DestId == CompList[i]->GetmyID())
						{
							DestInfo = ((AddConnection*)pAct)->ChangeDestination(CompList[i], PinNo);
							F = dynamic_cast<LED*>(CompList[i]);
							if (F)
							{
								DestPin = ((LED*)CompList[i])->getIP();
								DestPin->setIPnotconnected(!(DestPin->getIPnotconnected()));
							}
							else
							{
								DestPin = ((Gate*)CompList[i])->getIP(PinNo);
								DestPin->setIPnotconnected(!(DestPin->getIPnotconnected()));
							}
						}
					}
				}
				GInfo.x1 = SourceInfo.x1;
				GInfo.y1 = SourceInfo.y1;
				GInfo.x2 = DestInfo.x2;
				GInfo.y2 = DestInfo.y2;
				Connection* pA = new Connection(GInfo, SourcePin, DestPin);
				bool fanO = SourcePin->ConnectTo(pA);
				if (fanO == false)
				{
					DestPin->setIPnotconnected(!(DestPin->getIPnotconnected()));
				}
				AddComponent(pA);
				CompList[CompCount-1]->LoadCircuit("", ID);
			}
			else
			{
				finput.close();
				break;
			}
		}
		if (finput.is_open() == true)
			finput.close();
	}

}
////////////////////////////////////////////////////////////////////
void ApplicationManager::EditLabel(Component* Comp, string msg)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (Comp == CompList[i])
		{
			Comp->SetLabel(msg);
			break;
		}
	}
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::EditSource(Component* ConnectionLine, Component* Source)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (ConnectionLine == CompList[i])
		{
			Action* pAct = new AddConnection(this);

			GraphicsInfo SourceInfo = ((AddConnection*)pAct)->ChangeSource(Source);
			((Connection*)ConnectionLine)->ChangeSourceInfo(SourceInfo);

			delete pAct;
			pAct = NULL;
			break;
		}
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::EditDst(Component* ConnectionLine, Component* Dst, int PinNo)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (ConnectionLine == CompList[i])
		{
			Action* pAct = new AddConnection(this);

			GraphicsInfo DstInfo = ((AddConnection*)pAct)->ChangeDestination(Dst, PinNo);
			((Connection*)ConnectionLine)->ChangeDstInfo(DstInfo);

			delete pAct;
			pAct = NULL;
			break;
		}
	}
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::Delete1()
{
	int k = 0;
	int count = 0; 
	Component* F = NULL; 
	Component* AllConnections[MaxCompCount]; 
	Connection* neededconnection = NULL; 
	Gate* neededgate = NULL; 
	SWITCH* neededswitch = NULL;
	LED* neededLED = NULL;
	InputPin* IP = NULL; 
	OutputPin* OP = NULL;

	for (int i = 0; i < CompCount; i++)
	{
		F = dynamic_cast<Connection*>(CompList[i]);
		if (F != NULL)
		{
			AllConnections[count] = CompList[i];
			count++;
		}
	}
	for (int i = 0; i < MaxCompCount; i++)
	{

		if (CompList[i] == NULL)
		{
			break;
		}

		F = dynamic_cast<Gate*>(CompList[i]);

		if (CompList[i]->getSelected() == true)
		{
			if (F)
			{
				for (int j = 0; j < count; j++)
				{
					neededgate = dynamic_cast<Gate*>(CompList[i]);
					neededconnection = dynamic_cast<Connection*>(AllConnections[j]);
					for (int l = 1; l <= (neededgate->getNoIpins()); l++)
					{
						if (neededconnection->getDestPin() == neededgate->getIP(l))
						{
							AllConnections[j]->setSelected(true);
						}
					}
					if (neededconnection->getSourcePin() == neededgate->getOP())
					{
						AllConnections[j]->setSelected(true);
					}
				}
			}
		}
		F = dynamic_cast<SWITCH*>(CompList[i]);
		if (CompList[i]->getSelected() == true)
		{
			if (F)
			{
				for (int j = 0; j < count; j++)
				{
					neededswitch = dynamic_cast<SWITCH*>(CompList[i]);
					neededconnection = dynamic_cast<Connection*>(AllConnections[j]);
					if (neededconnection->getSourcePin() == neededswitch->getOP())
					{
						AllConnections[j]->setSelected(true);
					}
				}
			}
		}
		F = dynamic_cast<LED*>(CompList[i]);
		if (CompList[i]->getSelected() == true)
		{
			if (F)
			{
				for (int j = 0; j < count; j++)
				{
					neededLED = dynamic_cast<LED*>(CompList[i]);
					neededconnection = dynamic_cast<Connection*>(AllConnections[j]);
					if (neededconnection->getDestPin() == neededLED->getIP())
					{
						AllConnections[j]->setSelected(true);
					}

				}
			}
		}
	}



	for (int i = 0; i < MaxCompCount; i++)
	{
		if (CompList[i - k] == NULL)
		{
			break;
		}
		if (CompList[i - k]->getSelected() == true)
		{
			F = dynamic_cast<Connection*>(CompList[i - k]);


			if (F)
			{
				neededconnection = ((Connection*)CompList[i - k]);
				OP = neededconnection->getSourcePin();
				IP = neededconnection->getDestPin();
				OP->DisconnectOP();
				IP->setIPnotconnected(!(IP->getIPnotconnected()));
			}
			delete CompList[i - k];
			CompList[i - k] = CompList[CompCount - 1];
			CompList[CompCount - 1] = NULL;
			CompCount--;
			k++;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
void ApplicationManager::Delete2(Component* Compo)
{
	int k = 0;
	int p = 0;
	int count = 0;
	int l = 0;
	Component* F = NULL;
	Component* AllConnections[MaxCompCount];
	Connection* neededconnection = NULL;
	Gate* neededgate = NULL;
	SWITCH* neededswitch = NULL;
	LED* neededLED = NULL;
	InputPin* IP = NULL;
	OutputPin* OP = NULL;
	Component* WasSelected[MaxCompCount];

	for (int i = 0; i < CompCount; i++)
	{
		F = dynamic_cast<Connection*>(CompList[i]);
		if (F != NULL)
		{
			AllConnections[count] = CompList[i];
			count++;
		}
	}
	for (int i = 0; i < MaxCompCount; i++)
	{

		if (CompList[i] == NULL)
		{
			break;
		}

		F = dynamic_cast<Gate*>(CompList[i - k]);

		if (CompList[i]->getSelected() == true && CompList[i] != Compo)
		{
			WasSelected[l] = CompList[i];
			l++;
			CompList[i]->setSelected(false);
		}
	}
	for (int i = 0; i < MaxCompCount; i++)
	{

		if (CompList[i] == NULL)
		{
			break;
		}

		F = dynamic_cast<Gate*>(CompList[i - k]);

		if (CompList[i]->getSelected() == true)
		{
			if (F)
			{
				for (int j = 0; j < count; j++)
				{
					neededgate = dynamic_cast<Gate*>(CompList[i]);
					neededconnection = dynamic_cast<Connection*>(AllConnections[j]);
					for (int l = 1; l <= (neededgate->getNoIpins()); l++)
					{
						if (neededconnection->getDestPin() == neededgate->getIP(l))
						{
							AllConnections[j]->setSelected(true);
						}
					}
					if (neededconnection->getSourcePin() == neededgate->getOP())
					{
						AllConnections[j]->setSelected(true);
					}
				}
			}

		}
		F = dynamic_cast<SWITCH*>(CompList[i]);
		if (CompList[i]->getSelected() == true)
		{
			if (F)
			{
				for (int j = 0; j < count; j++)
				{
					neededswitch = dynamic_cast<SWITCH*>(CompList[i]);
					neededconnection = dynamic_cast<Connection*>(AllConnections[j]);
					if (neededconnection->getSourcePin() == neededswitch->getOP())
					{
						AllConnections[j]->setSelected(true);
					}
				}
			}
		}
		F = dynamic_cast<LED*>(CompList[i]);
		if (CompList[i]->getSelected() == true)
		{
			if (F)
			{
				for (int j = 0; j < count; j++)
				{
					neededLED = dynamic_cast<LED*>(CompList[i]);
					neededconnection = dynamic_cast<Connection*>(AllConnections[j]);
					if (neededconnection->getDestPin() == neededLED->getIP())
					{
						AllConnections[j]->setSelected(true);
					}

				}
			}
		}
	}
	for (int i = 0; i < MaxCompCount; i++)
	{
		if (CompList[i - k] == NULL)
		{
			break;
		}
		if (CompList[i - k]->getSelected() == true)
		{
			F = dynamic_cast<Connection*>(CompList[i - k]);

			if (F)
			{
				neededconnection = ((Connection*)CompList[i - k]);
				OP = neededconnection->getSourcePin();
				IP = neededconnection->getDestPin();
				OP->DisconnectOP();
				IP->setIPnotconnected(!(IP->getIPnotconnected()));
			}
			delete CompList[i - k];
			CompList[i - k] = CompList[CompCount - 1];
			CompList[CompCount - 1] = NULL;
			CompCount--;
			k++;
		}
	}
	for (int i = 0; i < l; i++)
	{
		WasSelected[i]->setSelected(true);
	}
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::Simulate()
{
	for (int i = 0; i < CompCount; i++)
	{
		for (int j = 0; j < CompCount; j++)
		{
			CompList[j]->Operate();
		}
	}
}

////////////////////////////////////////////////////////////////////
void ApplicationManager::SetClipboard(Component* Comp)
{
	IteminClipboard = true;
	Clipboard = Comp;
}
////////////////////////////////////////////////////////////////////
Component* ApplicationManager::GetClipboard()
{
	if (IteminClipboard)
	{
		return Clipboard;
	}
	else
	{
		return NULL;
	}
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::setItemCut(bool b)
{
	ItemCut = b;
}
////////////////////////////////////////////////////////////////////
bool ApplicationManager::getItemCut()
{
	return ItemCut;
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::SaveCircuit( ofstream& fout)
{
	int Ncomp = 0;  // number of components excluding connections
	for (int i = 0; i < CompCount; i++)
	{
		Component * C = dynamic_cast <Connection*>(CompList[i]);
		if (!C)   
		{
			Ncomp++;
		}
	}
	
	fout << Ncomp << endl;
	for (int i = 0; i < CompCount; i++)
	{
		Component* C = dynamic_cast <Connection*>(CompList[i]);
		if (!C)
		{
			CompList[i]->SaveComponent(fout);   // Saves the components
		}	
	}
	
	fout << "Connections" << endl;
	
	InputPin* IP;
	OutputPin* OP;
	int SrcID = -1, DstID = -1, PinNo = 1;
	for (int i = 0; i < CompCount; i++)
	{
		SrcID = -1, DstID = -1, PinNo = 1;   // To avoid unnecessary breaking
		if (Component* C = dynamic_cast <Connection*>(CompList[i]))
		{
			OP = ((Connection*)CompList[i])->getSourcePin();   // pinter to the source pin
			IP = ((Connection*)CompList[i])->getDestPin();     // pointer to the destination pin  

			// getting the ID of the source component
			for (int j = 0; j < CompCount; j++)
			{
				Component* C1 = dynamic_cast <Connection*>(CompList[j]);
				Component* C2 = dynamic_cast <LED*>(CompList[j]);
				if ( (!C1) && (!C2) )   // Excludes connections and components that don't have outputs
				{
					if (OP == ((SWITCH*)CompList[j])->getOP())
					{
						SrcID = CompList[j]->GetmyID();
						break;
					}
					if (OP == ((Gate*)CompList[j])->getOP())
					{
						SrcID = CompList[j]->GetmyID();   // Obtained the ID of the source component
						break;
					}
				}
				
			}
			
			// Getting the ID of the destination component
			for (int j = 0; j < CompCount; j++)
			{
				Component* C1 = dynamic_cast <Connection*>(CompList[j]);
				Component* C2 = dynamic_cast <SWITCH*>(CompList[j]);
				if (  (!C1) && (!C2)  )   // Excludes connections and components with no inputs
				{
					if (IP == ((LED*)CompList[j])->getIP())
					{
						DstID = CompList[j]->GetmyID();
						break;
					}
					for (int k = 1; k <= ((Gate*)CompList[j])->getNoIpins(); k++)
					{
						if (IP == ((Gate*)CompList[j])->getIP(k))
						{
							DstID = CompList[j]->GetmyID();
							PinNo = k;
							break;
						}
					}
					if (DstID != -1)    // Breaks when it find the destination component
					{
						break;
					}
				}
				

			}
			

			CompList[i]->SaveConnection(SrcID, DstID, PinNo, fout);

		}
	}


	fout << "-1" << endl;
}
////////////////////////////////////////////////////////////////////
bool ApplicationManager::ValidCir()
{
	int n;
	for (int i = 0; i < CompCount; i++)
	{
		if (dynamic_cast<Gate*>(CompList[i]))
		{

			n = (((Gate*)CompList[i])->getOP())->getCurrentConnections();
			if (n == 0)
			{
				return false;
			}
			for (int j = 0; j < ((Gate*)CompList[i])->getNoIpins(); j++)
			{
				if ((((Gate*)CompList[i])->getIP(j + 1))->getIPnotconnected())
				{
					return false;
				}
			}
		}
		else if (dynamic_cast<SWITCH*>(CompList[i]))
		{
			n = (((SWITCH*)CompList[i])->getOP())->getCurrentConnections();
			if (n == 0)
			{
				return false;
			}		
		}
		else if (dynamic_cast<LED*>(CompList[i]))
		{
			if ((((LED*)CompList[i])->getIP())->getIPnotconnected())
			{
				return false;
			}
		}
	}
	return true;

}

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
	
}