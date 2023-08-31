#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"

class Select : public Action
{
private:
	int Cx, Cy;	//Center point of the gate
public:
	Select(ApplicationManager* pApp);
	virtual ~Select(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
	virtual void Label();
	virtual bool CheckArea(int, int, int, int, bool);

};

