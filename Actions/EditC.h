#ifndef _EDIT_Label_H
#define _EDIT_Label_H

#include "action.h"
#include "..\Components\Connection.h"
#include "..\Components\Gate.h"
#include "..\Components\SWITCH.h"
#include "..\Components\LED.h"


class EditC : public Action
{
private:
	
	int Cx, Cy;	
public:
	EditC(ApplicationManager* pApp);
	virtual ~EditC(void);

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