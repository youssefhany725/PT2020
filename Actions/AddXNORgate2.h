#ifndef _ADD_XNOR_GATE_H
#define _ADD_XNOR_GATE_H

#include "action.h"
#include "..\Components\XNOR2.h"

class AddXNORgate2 : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
protected:
	string NameTag;
public:
	AddXNORgate2(ApplicationManager* pApp);
	virtual ~AddXNORgate2(void);

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