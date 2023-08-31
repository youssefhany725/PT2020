#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Component.h"
#include <fstream>

//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount = 200 };	//Max no of Components	

private:
	int CompCount;		//Actual number of Components
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)

	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Clase Interface
	Component* Clipboard; 
	bool ItemCut;   //to know if the item in clipboard is cut or copied
	

	bool IteminClipboard;

public:	
	ApplicationManager(); //constructor

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();
	
	//Creates an action and executes it
	void ExecuteAction(ActionType);
	
	void UpdateInterface();	//Redraws all the drawing window

	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();

	void Load(ifstream&);

	void ClearData();//deletes all
	void Delete1();//deletes selected items
	void Delete2(Component*);//delete only passed component
	
	void Simulate();//simulates circuit

	void setItemCut(bool);
	bool getItemCut();//used to know if the component in clipboard is cut or not

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

	void SetClipboard(Component*);
	Component* GetClipboard();

	//Searches for a component
	Component* IsComponent(int x, int y);//returns the clicked component 
	Component* IsConnection(int x, int y);//returns the clicked connection
	void EditLabel(Component*, string);
	void SaveCircuit( ofstream&);

	void EditSource(Component* ConnectionLine, Component* Source);
	void EditDst(Component* ConnectionLine, Component* Dst, int PinNo);

	bool ValidCir();//validates Circuit

	void Copy();
	void Cut();
	void Paste();


	//destructor
	~ApplicationManager();
};

#endif