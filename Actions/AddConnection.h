#pragma once
#include "action.h"
#include "..\Components\Connection.h"
#include "..\Components\Gate.h"
#include "..\Components\SWITCH.h"
#include "..\Components\LED.h"


class AddConnection : public Action
{
private:

	Component* Comp1;
	Component* Comp2;
	OutputPin* SrcPin;
	InputPin* DstPin;

	int Cx1, Cy1, Cx2, Cy2;// points clicked 
	int x1, y1, x2, y2;	//points to draw between
protected:
	string NameTag;
public:
	AddConnection(ApplicationManager* pApp);
	virtual ~AddConnection(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
	virtual void Label();
	virtual bool CheckArea(int, int, int, int, bool);
	GraphicsInfo ChangeSource(Component* SourceC);
	GraphicsInfo ChangeDestination(Component* DstC, int PinNo);


};
