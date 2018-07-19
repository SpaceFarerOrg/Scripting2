#include "DebugDrawer.h"
#include "SFML/Graphics/RenderWindow.hpp"


CDebugDrawer & CDebugDrawer::GetInstance()
{
	static CDebugDrawer instance;
	return instance;
}

void CDebugDrawer::Init(sf::RenderWindow & aWindowToRenderTo)
{
	myLineDrawer.SetWindow(&aWindowToRenderTo);
	myTextDrawer.SetWindow(&aWindowToRenderTo);
}

void CDebugDrawer::Render()
{
	for (int i = 0; i < myLineCommands.size(); ++i)
	{
		myLineDrawer.DrawLine(myLineCommands[i].myFrom, myLineCommands[i].myTo);
	}
	myLineCommands.clear();

	for (int i = 0; i < myTextCommands.size(); ++i)
	{
		myTextDrawer.DrawTextAt(myTextCommands[i].myText, myTextCommands[i].myPosition);
	}
	myTextCommands.clear();
}

void CDebugDrawer::DrawLine(const sf::Vector2f & aFrom, const sf::Vector2f & aTo)
{
	myLineCommands.push_back({ aFrom, aTo });
}

void CDebugDrawer::DrawTextAt(const std::string & aText, const sf::Vector2f & aPosition)
{
	myTextCommands.push_back({ aText, aPosition });
}

CDebugDrawer::CDebugDrawer()
{
}


CDebugDrawer::~CDebugDrawer()
{
}
