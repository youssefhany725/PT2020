#include "EditC.h"
#include "..\ApplicationManager.h"

EditC::EditC(ApplicationManager* pApp) :Action(pApp)
{
	Cx = 0;
	Cy = 0;
}

EditC::~EditC(void)
{
}

void EditC::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click on a component to edit it.");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void EditC::Execute()
{
	ReadActionParameters();

	Component* MainComp, * SecondaryComp;
	// The main component is the connection
	// the secondary component is the component the user clicks on. it is either a source or a destination
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	InputPin* IP;

	MainComp = pManager->IsComponent(Cx, Cy);    // Checks if it's a component

	Component* C1, * C2;
	if (MainComp)   // Checks that the user clicked on a component to edit it
	{
		if (C1 = dynamic_cast<Connection*>(MainComp))     // checks if it's a connection
		{
			string msg;
			pOut->PrintMsg("To edit the label, enter 1. To change the source pin, enter 2. To change the destination pin, enter 3. Click anywhere to continue.");
			pIn->GetPointClicked(Cx, Cy);
			pOut->PrintMsg("Enter choice: ");
			msg = pIn->GetInt(pOut);
			if (msg == "1")
			{
				msg = pIn->GetSrting(pOut);

				pManager->EditLabel(MainComp, msg);
			}
			else if (msg == "2")
			{
				pOut->PrintMsg("Changing source pin. Click on the new desired source component.");
				pIn->GetPointClicked(Cx, Cy);


				SecondaryComp = pManager->IsComponent(Cx, Cy); // checks that the user clicked on a component, not a free space
				C1 = dynamic_cast<LED*>(SecondaryComp);
				C2 = dynamic_cast<Connection*>(SecondaryComp);
				if (SecondaryComp && !C1 && !C2)    // checks if its a gate or a switch (cannot be a led nor a connection)
				{

					if (Component* C = dynamic_cast<Gate*>(SecondaryComp))
					{
						bool FanO = (((Gate*)SecondaryComp)->getOP())->ConnectTo((Connection*)MainComp) ;//checks that we can add more connections
						if (FanO == true)
						{
							((Connection*)MainComp)->getSourcePin()->DisconnectOP();
							((Connection*)MainComp)->setSourcePin(((Gate*)SecondaryComp)->getOP());  // changed the source pin	
							pManager->EditSource(MainComp, SecondaryComp);      // changed the GfxInfo of the connection
						}
					}
					else if (Component* C = dynamic_cast<SWITCH*>(SecondaryComp))
					{
						bool FanO = (((SWITCH*)SecondaryComp)->getOP())->ConnectTo((Connection*)MainComp);
						if (FanO == true)
						{
							((Connection*)MainComp)->getSourcePin()->DisconnectOP();
							((Connection*)MainComp)->setSourcePin(((SWITCH*)SecondaryComp)->getOP());
							pManager->EditSource(MainComp, SecondaryComp);      // changed the GfxInfo of the connection
						}
					}
				}
				else    // did not click on a valid component
				{
					pOut->PrintMsg("Invalid! Please only select a gate or a switch as the source component.");
				}
			}
			else if (msg == "3")
			{
				pOut->PrintMsg("Changing destination pin. Click on the new desired destination component.");
				pIn->GetPointClicked(Cx, Cy);

				SecondaryComp = pManager->IsComponent(Cx, Cy);                // checks that the user clicked on a component
				C1 = dynamic_cast<SWITCH*>(SecondaryComp);
				C2 = dynamic_cast<Connection*>(SecondaryComp);
				if (SecondaryComp && !C1 && !C2)        // checks if it's a gate or led (cannot be a switch or connection)
				{
					if (Component* C = dynamic_cast<LED*>(SecondaryComp))
					{
						if (((LED*)SecondaryComp)->IPnotConnected())
						{
							// frees the previous input pin
							(((Connection*)MainComp)->getDestPin())->setIPnotconnected(!((((Connection*)MainComp)->getDestPin())->getIPnotconnected()));

							(((LED*)SecondaryComp)->getIP())->setIPnotconnected(!((((LED*)SecondaryComp)->getIP())->getIPnotconnected())); // sets the new pin as occupied (connected)
							
							pManager->EditDst(MainComp, SecondaryComp, 1 );      // changes the x2 & y2 of the connection
						}
						else
						{
							return;
						}
					}
					
					// handling each pin in each gate
					if (Component* C = dynamic_cast<Gate*>(SecondaryComp))
					{
						pOut->PrintMsg("Enter pin #: ");
						string pinNo = pIn->GetInt(pOut);
						if (pinNo == "1" && ((((Gate*)SecondaryComp)->getNoIpins() == 3) || (((Gate*)SecondaryComp)->getNoIpins() == 2)))
						{
							if (((Gate*)SecondaryComp)->IPnotConnected(1))
							{	
								// Does as mentioned above
								(((Connection*)MainComp)->getDestPin())->setIPnotconnected(!((((Connection*)MainComp)->getDestPin())->getIPnotconnected()));


								(((Gate*)SecondaryComp)->getIP(1))->setIPnotconnected(!((((Gate*)SecondaryComp)->getIP(1))->getIPnotconnected()));
								pManager->EditDst(MainComp, SecondaryComp, 1);
							}
							else  // didn't press on a gate
							{
								return;
							}

						}
						else if ((pinNo == "2" && (((Gate*)SecondaryComp)->getNoIpins() == 3)))
						{
							if (((Gate*)SecondaryComp)->IPnotConnected(2))
							{
								(((Connection*)MainComp)->getDestPin())->setIPnotconnected(!((((Connection*)MainComp)->getDestPin())->getIPnotconnected()));

								(((Gate*)SecondaryComp)->getIP(2))->setIPnotconnected(!((((Gate*)SecondaryComp)->getIP(2))->getIPnotconnected()));
								pManager->EditDst(MainComp, SecondaryComp, 2);
							}
							else
							{
								return;
							}
						}
						else if ((pinNo == "1") && (((Gate*)SecondaryComp)->getNoIpins() == 1))
						{
							if (((Gate*)SecondaryComp)->IPnotConnected(1))
							{
								(((Connection*)MainComp)->getDestPin())->setIPnotconnected(!((((Connection*)MainComp)->getDestPin())->getIPnotconnected()));


								(((Gate*)SecondaryComp)->getIP(1))->setIPnotconnected(!((((Gate*)SecondaryComp)->getIP(1))->getIPnotconnected()));
								pManager->EditDst(MainComp, SecondaryComp, 1);
							}
							else
							{
								return;
							}
						}

						else if (((pinNo == "3") && (((Gate*)SecondaryComp)->getNoIpins() == 3)) || ((pinNo == "2") && ((Gate*)SecondaryComp)->getNoIpins() == 2))
						{
							if (pinNo == "3")
							{

								if (((Gate*)SecondaryComp)->IPnotConnected(3))
								{
									(((Connection*)MainComp)->getDestPin())->setIPnotconnected(!((((Connection*)MainComp)->getDestPin())->getIPnotconnected()));


									(((Gate*)SecondaryComp)->getIP(3))->setIPnotconnected(!((((Gate*)SecondaryComp)->getIP(3))->getIPnotconnected()));
									pManager->EditDst(MainComp, SecondaryComp, 3);
								}
								else
								{
									return;
								}
							}
							else   // Chose pin no.2 and no. of pins = 2
							{
								if (((Gate*)SecondaryComp)->IPnotConnected(2))
								{
									(((Connection*)MainComp)->getDestPin())->setIPnotconnected(!((((Connection*)MainComp)->getDestPin())->getIPnotconnected()));


									(((Gate*)SecondaryComp)->getIP(2))->setIPnotconnected(!((((Gate*)SecondaryComp)->getIP(2))->getIPnotconnected()));
									pManager->EditDst(MainComp, SecondaryComp, 2);

								}
								else
								{
									return;
								}
							}
						}

						else
						{
							return;
						}
					}

				}
			}
		}
		else     // if he clicked on a component not a connection
		{
			string msg;
			msg = pIn->GetSrting(pOut);

			pManager->EditLabel(MainComp, msg);
		}

	}
	else        // Didn't click on any component
	{
		pOut->PrintMsg("Invalid action! Did not click on a component");
		int x, y;
		pIn->GetPointClicked(x, y);
	}
}

void EditC::Label()
{}

bool EditC::CheckArea(int x1, int x2, int y1, int y2, bool Components)
{
	return true;
}

void EditC::Undo()
{}

void EditC::Redo()
{}

