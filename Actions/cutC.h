#pragma once
#include "action.h"
#include "..\Components\Connection.h"
#include "..\Components\Gate.h"
#include "..\Components\SWITCH.h"
#include "..\Components\LED.h"
class cutC : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	Component* Comp;
public:
	cutC(ApplicationManager* pApp);
	virtual ~cutC(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	virtual void Label();
	virtual void Undo();
	virtual void Redo();
	virtual bool CheckArea(int, int, int, int, bool);
};