#pragma once
#include "Action.h"
#include "..\Components\OR2.h"
class AddORgate2: public Action
{
private:
	int Cx, Cy;
	int x1, y1, x2, y2;
protected:
	string NameTag;
public:
	AddORgate2(ApplicationManager* pApp);
	virtual ~AddORgate2(void);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
	virtual void Label();
	virtual bool CheckArea(int, int, int, int, bool);
};

