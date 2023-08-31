#pragma once
#include "action.h"
#include "..\Components\Connection.h"
#include "..\Components\Gate.h"
#include "..\Components\SWITCH.h"
#include "..\Components\LED.h"
class copyC : public Action
{
private:
	
	int Cx, Cy;

	Component* Comp;
public:
	copyC(ApplicationManager* pApp);
	virtual ~copyC(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Label();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
	virtual bool CheckArea(int, int, int, int, bool);
};