#pragma once
#include "Action.h"
#include "..\Components\NOR3.h"
class AddNORgate3: public Action
{
private:
	int Cx, Cy;
	int x1, y1, x2, y2;
protected:
	string NameTag;
public:
	AddNORgate3(ApplicationManager* pApp);
	virtual ~AddNORgate3(void);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
	virtual void Label();
	virtual bool CheckArea(int, int, int, int, bool);
};

