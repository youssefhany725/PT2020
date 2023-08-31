#pragma once
#include "action.h"
#include "..\Components\SWITCH.h"

class ChangeSwitch : public Action
{
private:
	int Cx, Cy;	
	Component* Comp;
public:
	ChangeSwitch(ApplicationManager* pApp);
	virtual ~ChangeSwitch(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
	virtual void Label();
	virtual bool CheckArea(int, int, int, int, bool);

};
