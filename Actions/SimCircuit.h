#pragma once
#include "action.h"
class SimCircuit : public Action
{
private:
public:
	SimCircuit(ApplicationManager* pApp);
	virtual ~SimCircuit(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
	virtual void Label();
	virtual bool CheckArea(int, int, int, int, bool);

};
