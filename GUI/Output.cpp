#include "Output.h"

Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode
	UI.ActiveBar = DesignBar;  //Design Bar is the startup bar

	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = BLUE;
	UI.BkGrndColor = WHITE;

	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	ChangeTitle("Programming Techniques Project (Logic Simulator)");

	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar

}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(UI.MsgColor);
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
}

void Output::ClearGate(int x, int y)
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(x, y, x + UI.AND2_Width, y + UI.AND2_Height);
}

void Output::PrintLabelMsg(string msg) const
{
	ClearLabelStatusBar();	//Clear part of the Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25 + 105;
	int MsgY = UI.StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(UI.MsgColor);
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
}

void Output::PrintLabel(int x, int y, string msg) const
{
	PrintMsg("Click anywhere to continue");
	pWind->DrawString(x, y, msg);
}



//////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 22;                                                
	int MsgY = UI.StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);
}

void Output::ClearLabelStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 22 + 105;                                                   
	int MsgY = UI.StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void Output::ClearDrawingArea() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDesignToolBar() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}

//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode

	//You can draw the tool bar icons in any way you want.

	
	string MenuItemImages[ITM_DSN_CNT];

	MenuItemImages[ITM_ADD] = "Images\\Menu\\Menu_ADD.jpg";
	MenuItemImages[ITM_EDIT] = "Images\\Menu\\Menu_EDIT.jpg";
	MenuItemImages[ITM_SAVE] = "Images\\Menu\\Menu_SAVE.jpg";
	MenuItemImages[ITM_LOAD] = "Images\\Menu\\Menu_LOAD.jpg";
	MenuItemImages[ITM_CUT] = "Images\\Menu\\Menu_CUT.jpg";
	MenuItemImages[ITM_COPY] = "Images\\Menu\\Menu_COPY.jpg";
	MenuItemImages[ITM_PASTE] = "Images\\Menu\\Menu_PASTE.jpg";
	MenuItemImages[ITM_SIMULATE] = "Images\\Menu\\Menu_SIMULATE.jpg";
	MenuItemImages[ITM_SELECT] = "Images\\Menu\\Menu_SELECT.jpg";
	MenuItemImages[ITM_CONNECT] = "Images\\Menu\\Menu_CONNECT.jpg";
	MenuItemImages[ITM_Validation] = "Images\\Sim\\Menu_CheckComponents.jpg";
	MenuItemImages[ITM_DELETE] = "Images\\Menu\\Menu_Delete.jpg";
	MenuItemImages[ITM_CLEAR] = "Images\\Menu\\Menu_CLEAR.jpg";
	MenuItemImages[ITM_EXIT] = "Images\\Menu\\Menu_Exit.jpg";
	//Draw menu item one image at a time
	for (int i = 0; i < ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);

	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);


}

void Output::ClearGateToolBar() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

}

void Output::CreateGateToolBar() const
{	//creates toolbar for gates after clicking the add button

	string GateMenuItemImages[ITM_GATE_CNT];
	GateMenuItemImages[ITM_AND2] = "Images\\Menu\\GateMenu\\Menu_AND2.jpg";
	GateMenuItemImages[ITM_AND3] = "Images\\Menu\\GateMenu\\Menu_AND3.jpg";
	GateMenuItemImages[ITM_OR2] = "Images\\Menu\\GateMenu\\Menu_OR2.jpg";
	GateMenuItemImages[ITM_BUFF] = "Images\\Menu\\GateMenu\\Menu_BUFFER.jpg";
	GateMenuItemImages[ITM_INV] = "Images\\Menu\\GateMenu\\Menu_NOT.jpg";
	GateMenuItemImages[ITM_NOR2] = "Images\\Menu\\GateMenu\\Menu_NOR2.jpg";
	GateMenuItemImages[ITM_NOR3] = "Images\\Menu\\GateMenu\\Menu_NOR3.jpg";
	GateMenuItemImages[ITM_NAND2] = "Images\\Menu\\GateMenu\\Menu_NAND2.jpg";
	GateMenuItemImages[ITM_XOR2] = "Images\\Menu\\GateMenu\\Menu_XOR2.jpg";
	GateMenuItemImages[ITM_XOR3] = "Images\\Menu\\GateMenu\\Menu_XOR3.jpg";
	GateMenuItemImages[ITM_XNOR2] = "Images\\Menu\\GateMenu\\Menu_XNOR2.jpg";
	GateMenuItemImages[ITM_LED] = "Images\\Menu\\GateMenu\\Menu_LED.jpg";
	GateMenuItemImages[ITM_SWITCH] = "Images\\Menu\\GateMenu\\Menu_SWITCH.jpg";
	GateMenuItemImages[ITM_Exit] = "Images\\Menu\\Menu_Exit.jpg";
	GateMenuItemImages[ITM_BACK] = "Images\\Menu\\GateMenu\\Menu_BACK.jpg";

	for (int i = 0; i < ITM_GATE_CNT; i++)
		pWind->DrawImage(GateMenuItemImages[i], i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);   

	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}

//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;	//Simulation Mode

	string SimMenuItem[ITM_SIM_CNT];
	SimMenuItem[ITM_SIM] = "Images\\Sim\\Menu_SIMULATE.jpg";
	SimMenuItem[ITM_Design] = "Images\\Menu\\GateMenu\\Menu_BACK.jpg";
	SimMenuItem[ITM_Sav] = "Images\\Sim\\Menu_Save.jpg";
	SimMenuItem[ITM_ChangeSwitch] = "Images\\Sim\\Menu_ChangeSwitch.jpg";
	SimMenuItem[ITM_EX] = "Images\\Menu\\Menu_Exit.jpg";


	for (int i = 0; i < ITM_SIM_CNT; i++)
		pWind->DrawImage(SimMenuItem[i], i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);

	pWind->SetPen(BLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}



void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NAND2_HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NAND2.jpg";

	//Draw NAND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_OR2_HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_OR2.jpg";

	//Draw OR2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR2_HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR2.jpg";

	//Draw NOR2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR2_HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR2.jpg";

	//Draw XOR2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XNOR2_HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XNOR2.jpg";

	//Draw XNOR2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawBUFF(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_Buff_HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_Buff.jpg";

	//Draw BUFF Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOT(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOT_HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOT.jpg";

	//Draw NOT Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND3_HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND3.jpg";

	//Draw AND3 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR3_HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR3.jpg";

	//Draw NOR3 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR3_HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR3.jpg";

	//Draw XOR3 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawLED(GraphicsInfo r_GfxInfo, bool selected, bool ON) const
{
	string GateImage;
	if (ON)
	{
		if (selected)	//use image in the highlighted case
			GateImage = "Images\\Gates\\Gate_LED_ON_HI.jpg";
		else
			GateImage = "Images\\Gates\\Gate_LED_ON.jpg";
	}
	else
	{
		if (selected)	//use image in the highlighted case
			GateImage = "Images\\Gates\\Gate_LED_OFF_HI.jpg";
		else
			GateImage = "Images\\Gates\\Gate_LED_OFF.jpg";
	}
	//Draw LED Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawOpenSWITCH(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_SWITCH_HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_SWITCH.jpg";

	//Draw Switch Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}
void Output::DrawClosedSWITCH(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_SWITCH_Closed_HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_SWITCH_Closed.jpg";

	//Draw Switch Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}


void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool selected) const
{
	if (selected)
	{
		pWind->SetPen(RED, 3);
		int px1 = r_GfxInfo.x1;
		int py1 = r_GfxInfo.y1;
		int px2 = r_GfxInfo.x2;
		int py2 = r_GfxInfo.y2;
		if ((py1 >= py2 && px2 >= px1) || (py2 >= py1 && px2 >= px1)) //to draw only horizontal and vertical lines
		{
			pWind->DrawLine(px1, py1, (px2 - 30), py1);
			pWind->DrawLine((px2 - 30), py1, (px2 - 30), py2);
			pWind->DrawLine((px2 - 30), py2, px2, py2);
		}
		else
		{
			pWind->DrawLine(px1, py1, (px2 + 30), py1);
			pWind->DrawLine((px2 + 30), py1, (px2 + 30), py2);
			pWind->DrawLine((px2 + 30), py2, px2, py2);
		}
	}
	else
	{
		pWind->SetPen(BLUE, 3);
		int px1 = r_GfxInfo.x1;
		int py1 = r_GfxInfo.y1;
		int px2 = r_GfxInfo.x2;
		int py2 = r_GfxInfo.y2;
		if ((py1 >= py2 && px2 >= px1) || (py2 >= py1 && px2 >= px1)) //to draw only horizontal and vertical lines
		{
			pWind->DrawLine(px1, py1, (px2 - 30), py1);
			pWind->DrawLine((px2 - 30), py1, (px2 - 30), py2);
			pWind->DrawLine((px2 - 30), py2, px2, py2);
		}
		else
		{
			pWind->DrawLine(px1, py1, (px2 + 30), py1);
			pWind->DrawLine((px2 + 30), py1, (px2 + 30), py2);
			pWind->DrawLine((px2 + 30), py2, px2, py2);
		}

	}
}


Output::~Output()
{
	delete pWind;
}
