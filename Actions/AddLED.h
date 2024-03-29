#ifndef _ADD_LED_H
#define _ADD_LED_H

#include "action.h"
#include "..\Components\LED.h"

class AddLED :	public Action
{
private:
	//Parameters for rectangular area to be occupied by the LED
	int Cx, Cy;	//Center point of the LED
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
protected:
	string NameTag;
public:
	AddLED(ApplicationManager *pApp);
	virtual ~AddLED(void);

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