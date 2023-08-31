#include "InputPin.h"

InputPin::InputPin():notConnected(true)
{
	Connected = true;
}

void InputPin::setComponent(Component *pCmp)
{
	this->pComp = pCmp;
}

Component* InputPin::getComponent()
{
	return pComp;
}
void InputPin::setIPnotconnected(bool b)
{
	notConnected = b;
}
bool InputPin::getIPnotconnected()
{
	return notConnected;
}