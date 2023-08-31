#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"

class LoadCircuits : public Action
{
private:
	
	int Cx, Cy;	
	int x1, y1, x2, y2;
public:
	LoadCircuits(ApplicationManager* pApp);
	virtual ~LoadCircuits(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
	virtual void Label();
	virtual bool CheckArea(int, int, int, int, bool);


};

