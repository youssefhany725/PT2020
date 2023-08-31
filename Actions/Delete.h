#ifndef _DELETE_H
#define _DELETE_H

#include "Action.h"
#include "..\ApplicationManager.h"

class Delete : public Action
{
private:
	
	int Cx, Cy;	
public:
	Delete(ApplicationManager* pApp);
	virtual ~Delete();

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
	virtual void Label();
	virtual bool CheckArea(int, int, int, int, bool);

};

#endif