#include "AddConnection.h"
#include "..\ApplicationManager.h"
AddConnection::AddConnection(ApplicationManager* pApp) :Action(pApp)
{
	Cx1 = 0;
	Cy1 = 0;
	Cx2 = 0;
	Cy2 = 0;
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
}

AddConnection::~AddConnection(void)
{
}

void AddConnection::ReadActionParameters()
{
	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	
	//Wait for User Input
	pOut->PrintMsg("Click on the source gate");
	pIn->GetPointClicked(Cx1, Cy1);
	pOut->PrintMsg("Click on the Destination gate ");
	pIn->GetPointClicked(Cx2, Cy2);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddConnection::Execute()
{
	ReadActionParameters();

	int a1 = 0, b1 = 0, a2 = 0, b2 = 0; /// coordinates of source component
	int d1 = 0, e1 = 0, d2 = 0, e2 = 0; /// coordinates of dst component
	

	if (pManager->IsComponent(Cx1, Cy1) != NULL) 
	{
		Comp1 = pManager->IsComponent(Cx1, Cy1);
		Component* Comp3 = pManager->IsConnection(Cx1, Cy1);
		Component* C = dynamic_cast<Connection*>(Comp1);
		Component* C2 = dynamic_cast<LED*>(Comp1);
		if ((C || C2) && Comp3)
		{
			return;
		}
		Comp1->getGInfo(a1, b1, a2, b2);
	}
	else
	{
		return;
	}
	if (pManager->IsComponent(Cx2, Cy2) != NULL)
	{
		Comp2 = pManager->IsComponent(Cx2, Cy2);
		Component* Comp3 = pManager->IsConnection(Cx2, Cy2);
		Component* C = dynamic_cast<Connection*>(Comp2);
		Component* C2 = dynamic_cast<SWITCH*>(Comp2);
		if ((C || C2) && Comp3)
		{
			return;
		}
		Comp2->getGInfo(d1, e1, d2, e2);
	}
	else
	{
		return;
	}
	

	GraphicsInfo GInfo; //Gfx info to be used to draw connection
	

	

		// SRC PIN info 
	if (Component* C = dynamic_cast<Gate*>(Comp1))
	{
		GInfo.x1 = a1 + UI.AND2_Width;
		GInfo.y1 = b1 + (0.5 * UI.AND2_Height);
		
	}
	else if (Component* C = dynamic_cast<SWITCH*>(Comp1))
	{
		GInfo.x1 = a1 + UI.AND2_Width;
		GInfo.y1 = b1 + (0.5 * UI.AND2_Height) + 14;

	}
	
		//add condition to check type of component

	if (Component* C = dynamic_cast<Gate*>(Comp1))
	{
		SrcPin = ((Gate*)Comp1)->getOP();
	}
	else if (Component* C = dynamic_cast<SWITCH*>(Comp1))
	{
		SrcPin = ((SWITCH*)Comp1)->getOP();
	}

	
	// Getting DstPin info
	if (Component* C = dynamic_cast<LED*>(Comp2))
	{
		if (((LED*)Comp2)->IPnotConnected())
		{
			DstPin = ((LED*)Comp2)->getIP();
			DstPin->setStatus(SrcPin->getStatus());
			Comp2->setInputPinStatus(1, DstPin->getStatus());
			DstPin->setIPnotconnected(!(DstPin->getIPnotconnected()));
			GInfo.x2 = d1 + UI.AND2_Width / 2;
			GInfo.y2 = e1 + UI.AND2_Height;
		}
		else
		{
			return;
		}
	}

	
	if (Component* C = dynamic_cast<Gate*>(Comp2))
	{
		Output* pOut = pManager->GetOutput();
		Input* pIn = pManager->GetInput();
		pOut->PrintMsg("Enter pin #: ");
		string pinNo = pIn->GetInt(pOut);

		if (pinNo == "1" && ((((Gate*)Comp2)->getNoIpins() == 3) || (((Gate*)Comp2)->getNoIpins() == 2)))
		{
			if (((Gate*)Comp2)->IPnotConnected(1))
			{	
				DstPin = ((Gate*)Comp2)->getIP(1);
				DstPin->setStatus(SrcPin->getStatus());
				Comp2->setInputPinStatus(1, (DstPin->getStatus()));
				DstPin->setIPnotconnected(!(DstPin->getIPnotconnected()));
				GInfo.x2 = d1;
				GInfo.y2 = e1 + 12;
				
			}
			else
			{
				return;
			}

		}
		else if ((pinNo == "2" && (((Gate*)Comp2)->getNoIpins() == 3)))
		{
			if (((Gate*)Comp2)->IPnotConnected(2))
			{
				
				DstPin = ((Gate*)Comp2)->getIP(2);
				DstPin->setStatus(SrcPin->getStatus());
				Comp2->setInputPinStatus(2, (DstPin->getStatus()));
				DstPin->setIPnotconnected(!(DstPin->getIPnotconnected()));
				GInfo.x2 = d1;
				GInfo.y2 = e1 + UI.AND2_Height / 2;
				
			}
			else
			{
				return;
			}
		}
		else if ((pinNo == "1") && (((Gate*)Comp2)->getNoIpins() == 1))
		{
			if (((Gate*)Comp2)->IPnotConnected(1))
			{
				DstPin = ((Gate*)Comp2)->getIP(1);
				DstPin->setStatus(SrcPin->getStatus());
				Comp2->setInputPinStatus(1, (DstPin->getStatus()));
				DstPin->setIPnotconnected(!(DstPin->getIPnotconnected()));
				GInfo.x2 = d1;
				GInfo.y2 = e1 + (UI.AND2_Height / 2);
			}
			else
			{
				return;
			}
		}

		else if (((pinNo == "3") && (((Gate*)Comp2)->getNoIpins() == 3)) || ((pinNo == "2") && ((Gate*)Comp2)->getNoIpins() == 2))
		{
			if (pinNo == "3")
			{

				if (((Gate*)Comp2)->IPnotConnected(3)) 
				{
					DstPin = ((Gate*)Comp2)->getIP(3);
					DstPin->setStatus(SrcPin->getStatus());
					Comp2->setInputPinStatus(3, (DstPin->getStatus()));
					DstPin->setIPnotconnected(!(DstPin->getIPnotconnected()));
				}
				else
				{
					return;
				}
			}
			else
			{
				if (((Gate*)Comp2)->IPnotConnected(2))
				{
					DstPin = ((Gate*)Comp2)->getIP(2);
					DstPin->setStatus(SrcPin->getStatus());
					Comp2->setInputPinStatus(3, (DstPin->getStatus()));
					DstPin->setIPnotconnected(!(DstPin->getIPnotconnected()));
				}
				else
				{
					return;
				}
			}
			GInfo.x2 = d1;
			GInfo.y2 = e1 + UI.AND2_Height - 10;

		}

		else
		{
			return;
		}

	}

	Connection* pA = new Connection(GInfo, SrcPin, DstPin);
	bool fanO = SrcPin->ConnectTo(pA);
	if (fanO==false)
	{
		DstPin->setIPnotconnected(!(DstPin->getIPnotconnected()));
		delete pA;
		return;
	}
	pManager->AddComponent(pA);
}

void AddConnection::Label()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	NameTag = pIn->GetSrting(pOut);
}

GraphicsInfo AddConnection::ChangeSource(Component* SourceC)
{
	GraphicsInfo SourceInfo;
	int a1 = 0, b1 = 0, a2 = 0, b2 = 0;
	SourceC->getGInfo(a1, b1, a2, b2);
	SourceInfo.x1 = a1 + UI.AND2_Width;

	if (Component* C = dynamic_cast<Gate*>(SourceC))
	{	
		SourceInfo.y1 = b1 + (0.5 * UI.AND2_Height);
	}
	else if (Component* C = dynamic_cast<SWITCH*>(SourceC))
	{
		SourceInfo.y1 = b1 + (0.5 * UI.AND2_Height) + 14;
	}

	return SourceInfo;
}

GraphicsInfo AddConnection::ChangeDestination(Component* DstC, int PinNo)
{
	GraphicsInfo DstInfo;
	int d1 = 0, e1 = 0, d2 = 0, e2 = 0;
	DstC->getGInfo(d1, e1, d2, e2);

	if (Component* C = dynamic_cast<LED*>(DstC))
	{
		DstInfo.x2 = d1 + UI.AND2_Width / 2;
		DstInfo.y2 = e1 + UI.AND2_Height;		
		return DstInfo;
	}
	if (Component* C = dynamic_cast<Gate*>(DstC))
	{
		
		if (PinNo == 1 && ((((Gate*)DstC)->getNoIpins() == 3) || (((Gate*)DstC)->getNoIpins() == 2)))
		{
			
			DstInfo.x2 = d1;
			DstInfo.y2 = e1 + 12;
			return DstInfo;

		}
		else if ( ((PinNo == 2 && (((Gate*)DstC)->getNoIpins() == 3))) || ((PinNo == 1) && (((Gate*)DstC)->getNoIpins() == 1)) )
		{
			
			DstInfo.x2 = d1;
			DstInfo.y2 = e1 + UI.AND2_Height / 2;
			return DstInfo;
			
		}
		
		else if (((PinNo == 3) && (((Gate*)DstC)->getNoIpins() == 3)) || ((PinNo == 2) && ((Gate*)DstC)->getNoIpins() == 2))
		{
			
			DstInfo.x2 = d1;
			DstInfo.y2 = e1 + UI.AND2_Height - 10;
			return DstInfo;

		}
	}
}

bool AddConnection::CheckArea(int x1, int x2, int y1, int y2, bool Components)
{
	return true;
}
void AddConnection::Undo()
{}

void AddConnection::Redo()
{}