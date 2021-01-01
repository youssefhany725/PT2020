#include "Component.h"

Component::Component(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;	
}

Component::Component()
{}

Component::~Component()
{}

bool Component::Inarea(int x,int y)
{

	if (x >= m_GfxInfo.x1 && x <= m_GfxInfo.x2 && y >= m_GfxInfo.y1 && y < m_GfxInfo.y2)
	{
		return true;
	}
	else return false;

}
void Component::getGInfo(int& x1,int& y1, int& x2, int& y2)
{
	x1 = m_GfxInfo.x1;
	y1 = m_GfxInfo.y1;
	x2 = m_GfxInfo.x2;
	y2 = m_GfxInfo.y2;
}