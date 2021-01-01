#pragma once
#pragma once
#include "Action.h"
#include "..\Components\NOT.h"
class AddNOTgate : public Action
{
private:
	int Cx, Cy;
	int x1, y1, x2, y2;
public:
	AddNOTgate(ApplicationManager* pApp);
	virtual ~AddNOTgate(void);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};