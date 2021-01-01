#include "AddConnection.h"
#include "..\ApplicationManager.h"

AddConnection::AddConnection(ApplicationManager* pApp) :Action(pApp)
{
}

AddConnection::~AddConnection(void)
{
}

void AddConnection::ReadActionParameters()
{
	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	//Input* pIn2= pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("click on the two gate to connect");

	//Wait for User Input
	pIn->GetPointClicked(Cx1, Cy1);
	pIn->GetPointClicked(Cx2, Cy2);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddConnection::Execute()
{

	ReadActionParameters();
	//ApplicationManager* pApm =NULL;
	Comp1 = pManager->IsComponent(Cx1,Cy1);
	Comp2 = pManager->IsComponent(Cx2, Cy2);
	//Comp1 3ayzo yeshawer 3ala el gate el ana mekhtarhhaaa !!!!
	////////////////////////////////////////////////////////////////////////////////
	
	//Connection* Connect;
	
	/// //////////////////////////////////////////////////////////////
	
	GraphicsInfo GInfo; //Gfx info to be used to draw connection
	//SrcPin->setComponent(Conct);
	//DstPin->(Comp2);
	int a1=0, b1=0, a2=0, b2=0; /// coordinates of source component
	Comp1->getGInfo(a1, b1, a2, b2);
	int d1=0, e1=0, d2=0, e2=0; /// coordinates of dst component
	Comp2->getGInfo(d1, e1, d2, e2);
	
	
	
	//if (Comp1->IsComponent()) // kamel dy yastaa
	//{
		//Comp2->getGInfo(d1, e1, d2, e2);
	//}
	
	/*OutputPin* Comp1OP;
	Component* C = dynamic_cast<Gate*>(Comp1); //check if the component is gate 
	if (C) //if gate ba2a khaly el O/P pin ye3mel call le ConnectTo *****
	{
		Comp1OP = &((Gate*)Comp1)->getOP();
		Comp1OP->ConnectTo(Connect);
	}*/
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMsg("Enter pin number");
	int q = 0;
	int k = 0;
	pIn->GetPointClicked(q,k);
	string pinNo = pIn->GetSrting(pOut);
	

	if (Comp1->Inarea(Cx1, Cy1))
	{
		//if (Comp1->GetOutPinStatus() == 1)
		//{
			//SrcPin->setStatus(HIGH);
			///Connect->setSourcePin(Comp1OP); // beta3et el getOP w keda
		//}
		//else
		//{
			//SrcPin->setStatus(LOW);
			//SrcPin->
		//}
		GInfo.x1 = a1 + UI.AND2_Width;
		GInfo.y1 = b1 + (0.5*UI.AND2_Height);
		//GInfo.x1 = Cx1 + UI.AND2_Width;
		//GInfo.y1 = Cy1 - UI.AND2_Height/2;
		
	}
	//DstPin->setStatus(SrcPin->getStatus());
	if (Comp2->Inarea(Cx2, Cy2))
	{
		//add condition to check type of component
		
		for (int i = 1; i <= ((Gate*)Comp2)->getNoIpins(); i++)
		{
			if (pinNo=="1" && (i == 1)  )//((Gate*)Comp2)->GetInputPinStatus(i) == 0
			{
				//downcast ??
				//Comp2->setInputPinStatus(i, HIGH);

				GInfo.x2 = d1;
				GInfo.y2 = e1+12;
				break;

			}
			else if ( (pinNo =="2"  && (((Gate*)Comp2)->getNoIpins() == 3)) || (pinNo == "1")&& (((Gate*)Comp2)->getNoIpins() == 1))//((Gate*)Comp2)->GetInputPinStatus(i) == 0  && (i == 2) 
			{
				//Comp2->setInputPinStatus(i, DstPin->getStatus());
				GInfo.x2 = d1;
				GInfo.y2 = e1 + UI.AND2_Height / 2;
				break;
			
			}

			else if ( (pinNo =="3") || ((pinNo=="2") && ((Gate*)Comp2)->getNoIpins() == 2))//((Gate*)Comp2)->GetInputPinStatus(i) == 0   && ((i == 3) || ( i== 2)))
			{
				//Comp2->setInputPinStatus(i, DstPin->getStatus());
				GInfo.x2 = d1;
				GInfo.y2 = e1 + UI.AND2_Height -10;
				break;
			
			}

		}
	}
	Connection * pA = new Connection(GInfo, SrcPin, DstPin );
	pManager->AddComponent(pA);
}

void AddConnection::Undo()
{}

void AddConnection::Redo()
{}
