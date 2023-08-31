#include "Component.h"

Component::Component(const GraphicsInfo &r_GfxInfo)
{
	Selected = false;
	MyID = ++ID;
	m_GfxInfo = r_GfxInfo;	
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
	bool connectionlinearea = InConnection(x, y);
	if ( (x >= m_GfxInfo.x1 && x <= m_GfxInfo.x2 && y >= m_GfxInfo.y1 && y <= m_GfxInfo.y2) || (connectionlinearea) )   
	{
		return true;
	}
	else return false;

}

void Component::getGInfo(int& x1, int& y1, int& x2, int& y2)
{
	x1 = m_GfxInfo.x1;
	y1 = m_GfxInfo.y1;
	x2 = m_GfxInfo.x2;
	y2 = m_GfxInfo.y2;
}

bool Component::InConnection(int x, int y)
{

	if (m_GfxInfo.x1 < m_GfxInfo.x2)    
	{
		if (x >= m_GfxInfo.x1 && x <= m_GfxInfo.x2 - 30)
		{
			if (y <= m_GfxInfo.y1 + UI.AND2_Height/2  &&  y >= m_GfxInfo.y1 - UI.AND2_Height/2)
			{
				return true;
			}
		}

		if (x >= m_GfxInfo.x2 - 30 && x <= m_GfxInfo.x2)  
		{
			if (y <= m_GfxInfo.y2 + UI.AND2_Height / 2 && y >= m_GfxInfo.y2 - UI.AND2_Height / 2)
			{
				return true;
			}
		}

		if (y >= m_GfxInfo.y1 && y <= m_GfxInfo.y2  || y <= m_GfxInfo.y1 && y >= m_GfxInfo.y2) 
		{
			if (x <= m_GfxInfo.x2 - 30 + UI.AND2_Width / 2 && x >= m_GfxInfo.x2 - 30 - UI.AND2_Width / 2)
			{
				return true;
			}
		}
		
	}

	else        //draw from right to left
	{
		if (x <= m_GfxInfo.x1 && x >= m_GfxInfo.x2 + 30) 
		{
			if (y <= m_GfxInfo.y1 + UI.AND2_Height / 2 && y >= m_GfxInfo.y1 - UI.AND2_Height / 2)
			{
				return true;
			}
		}

		if (x <= m_GfxInfo.x2 + 30 && x >= m_GfxInfo.x2)    
		{
			if (y <= m_GfxInfo.y2 + UI.AND2_Height / 2 && y >= m_GfxInfo.y2 - UI.AND2_Height / 2)
			{
				return true;
			}
		}

		if (y >= m_GfxInfo.y1 && y <= m_GfxInfo.y2 || y <= m_GfxInfo.y1 && y >= m_GfxInfo.y2)        
		{
			if (x >= m_GfxInfo.x2 + 30 - UI.AND2_Width / 2 && x <= m_GfxInfo.x2 + 30 + UI.AND2_Width / 2)
			{
				return true;
			}
		}
	}
	
	 return false;
}

void Component::SetLabel(string Label)
{
	NameTag = Label;
}

string Component::GetLabel()
{
	return NameTag;
}




int Component::GetmyID()
{
	return MyID;
}


Component::Component()
{}

Component::~Component()
{}

