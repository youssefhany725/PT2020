#pragma once
#include "action.h"
#include "..\Components\Component.h"
#include "..\Components\Connection.h"
#include "..\Components\Gate.h"
#include "..\Components\SWITCH.h"
#include "..\Components\LED.h"
#include "..\Components\AND2.h"
#include "..\Components\AND3.h"
#include "..\Components\OR2.h"
#include "..\Components\NOR2.h"
#include "..\Components\BUFF.h"
#include "..\Components\NAND.h"
#include "..\Components\NOR3.h"
#include "..\Components\NOT.h"
#include "..\Components\XNOR2.h"
#include "..\Components\XOR2.h"
#include "..\Components\XOR3.h"


class PasteC : public Action
{
private:
	int Cx, Cy;	//Center point of the gate
	Component* Comp;
protected:
	string NameTag;
public:
	PasteC(ApplicationManager* pApp);
	virtual ~PasteC(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Label();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
	virtual bool CheckArea(int, int, int, int, bool);
};