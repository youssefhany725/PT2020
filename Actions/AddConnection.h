#pragma once
#include "action.h"
#include "..\Components\Connection.h"
#include "..\Components\Gate.h"


class AddConnection : public Action
{
private:

	Component* Comp1;
	Component* Comp2;
	OutputPin* SrcPin;
	InputPin* DstPin;

	int Cx1, Cy1, Cx2, Cy2;// points clicked 
	int x1, y1, x2, y2;	//points to draw between
public:
	AddConnection(ApplicationManager* pApp);
	virtual ~AddConnection(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};
