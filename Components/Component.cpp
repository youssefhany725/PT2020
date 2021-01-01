#include "Component.h"

Component::Component(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;
}

int Component::GetCoordsx1() //youssef was here
{
	return m_GfxInfo.x1; 
}

int Component::GetCoordsx2() //youssef was here
{
	return m_GfxInfo.x2;
}

int Component::GetCoordsy1() //youssef was here
{
	return m_GfxInfo.y1;
}

int Component::GetCoordsy2() //youssef was here
{
	return m_GfxInfo.y2;
}

void Component::setSelected(bool s)
{
	Selected = s;
}

bool Component::getSelected()
{
	return Selected;
}

bool Component::Inarea(int x, int y)
{

	if (x >= m_GfxInfo.x1 && x <= m_GfxInfo.x2 && y >= m_GfxInfo.y1 && y < m_GfxInfo.y2)
	{
		return true;
	}
	else return false;

}

Component::Component()
{}

Component::~Component()
{}

