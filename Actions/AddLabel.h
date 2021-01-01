//E7TMAL KBEER AMSA7 EL CLASS. aw msh hms7o, bs h5leeh by3adel 3la gate mwgooda asln

#ifndef _ADD_Label_H
#define _ADD_Label_H

#include "action.h"
//#include "..\Components\XOR3.h"  // msh m7tag a-inlcude component

class AddLabel : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
public:
	AddLabel(ApplicationManager* pApp);
	virtual ~AddLabel(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
	virtual void Label();

};

#endif