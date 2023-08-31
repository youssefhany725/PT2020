#ifndef SAVE_H
#define Save_H

#include "action.h"

#include <fstream>


class Save : public Action
{
private:
	
	int Cx, Cy;
public:
	Save(ApplicationManager* pApp);
	virtual ~Save();

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