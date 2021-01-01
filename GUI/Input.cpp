//#include "Input.h"
#include "Output.h"

Input::Input(window* pW)
{
	pWind = pW;                     //point to the passed window
}

void Input::GetPointClicked(int& x, int& y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click and get (x,y) coordinates
}

string Input::GetSrting(Output* pOut)
{
	///TODO: Implement this Function                                                        // Done
	//Read a complete string from the user until the user presses "ENTER".                  // Done
	//If the user presses "ESCAPE". This function should return an empty string.            // Done
	//"BACKSPACE" should be also supported												    // Done
	//User should see what he is typing at the status bar							        // Done


	string msg;                //\\ momkn hena n2ool msg ="enter a label mthln aw kda" w nzawed pOut->PrintMsg(msg);
	char c;
	keytype k;                                            // Checks special types of keys entered
	pWind->FlushKeyQueue();                               // Deletes old entries of keys
	pOut->PrintMsg("Enter a label: ");
	while (true)
	{
		//pOut->PrintMsg(msg);                              // Clears status bar initially, then prints new messages
		k = pWind->WaitKeyPress(c);                       // Takes input from user through GUI window

		if (k == ESCAPE)
		{
			msg.clear();                                  // Clears message and empties the status bar
			pOut->PrintMsg(msg);
			break;
		}

		else
		{
			if (c == '\r')								  // Detects the enter key
			{
				pOut->PrintMsg("");                       // Empties the status bar
				break;
			}

			else if (c == '\b')                           // Detects the backspace
			{
				if (msg.length() > 0)
				{
					msg.erase(msg.length() - 1, 1);       // Deletes one letter
					pOut->PrintLabelMsg(msg);
				}

			}

			else
			{
				msg += c;                                 // Adds one letter
				pOut->PrintLabelMsg(msg);
			}
		}
	}

	// Printing the message at the coordinates taken from the user
	int x, y;
	pWind->FlushMouseQueue();               // Deleting old entries of mouse clicks

	//if (k != ESCAPE)                        // Skips these steps if escape key was pressed
	//{
	//	pOut->PrintMsg("Click anywhere to place the label");
	//	GetPointClicked(x, y);
	//	pWind->DrawString(x, y, msg);
	//}
	return msg;
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() //shlna const w zwdna add flag
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && UI.ActiveBar==GateBar && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			switch (ClickedItemOrder)
			{
			case ITM_AND2:	 return ADD_AND_GATE_2;
			case ITM_AND3:	 return ADD_AND_GATE_3;
			case ITM_OR2:	 return ADD_OR_GATE_2;
			case ITM_NAND2:	 return ADD_NAND_GATE_2;
			case ITM_NOR2:	 return ADD_NOR_GATE_2;
			case ITM_NOR3:	 return ADD_NOR_GATE_3;
			case ITM_XOR2:	 return ADD_XOR_GATE_2;
			case ITM_XOR3:	 return ADD_XOR_GATE_3;
			case ITM_XNOR2:	 return ADD_XNOR_GATE_2;
			case ITM_INV:	 return ADD_INV;
			case ITM_BUFF:	 return ADD_Buff;
			case ITM_LED:	 return ADD_LED;
			case ITM_SWITCH: return ADD_Switch;
			case ITM_Exit:   return EXIT;
			case ITM_BACK: 	 return Go_Back;
			}
		}
		if (y >= 0 && UI.ActiveBar==DesignBar && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_ADD:		return ADD_GATE;
			case ITM_EDIT:		return EDIT_Label;
			case ITM_SAVE:		return SAVE;
			case ITM_LOAD:		return LOAD;
			case ITM_CUT:		return CUT;
			case ITM_COPY:		return COPY;
			case ITM_PASTE:		return PASTE;
			case ITM_SELECT:	return SELECT;
			case ITM_MSELECT:	return Multiple_SELECT;
			case ITM_SIMULATE:	return SIM_MODE;
			case ITM_CONNECT:	return ADD_CONNECTION;
			case ITM_MOVE:		return MOVE;
			case ITM_LABEL:		return ADD_Label;
			case ITM_CLEAR:		return CLEAR;
			case ITM_EXIT:		return EXIT;

			default:			return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}



		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a component
		}



		//[3] User clicks on the status bar
		return STATUS_BAR;
	}

	else	//Application is in Simulation mode //3alaaamaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			switch (ClickedItemOrder)
			{
			case ITM_EX:		   return EXIT;
			case ITM_TRUTH:		   return Create_TruthTable;
			case ITM_Design:	   return DSN_MODE;
			case ITM_Sav:		   return SAVE;
			case ITM_Validation:   return Validate_Circuit;
			case ITM_Probe:		   return Probing_tool;
			case ITM_ChangeSwitch: return Change_Switch;
			case ITM_SIM:		   return SimulateCircuit;

			default:			   return DSN_TOOL;

			}

		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a component
		}

		//[3] User clicks on the status bar
		return STATUS_BAR;



		//return SIM_MODE;	//This should be changed after creating the compelete simulation bar 
	}

}

Input::~Input()
{
}
