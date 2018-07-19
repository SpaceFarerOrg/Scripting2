#pragma once
#include "LineDrawer.h"
#include "TextDrawer.h"
#include "SFML/System/Vector2.hpp"

class CDebugDrawer
{
public:

	struct SLineCommand
	{
		sf::Vector2f myFrom;
		sf::Vector2f myTo;
	};

	struct STextCommand
	{
		std::string myText;
		sf::Vector2f myPosition;
	};

	static CDebugDrawer& GetInstance();

	void Init(sf::RenderWindow& aWindowToRenderTo);

	void Render();

	void DrawLine(const sf::Vector2f& aFrom, const sf::Vector2f& aTo);
	void DrawTextAt(const std::string& aText, const sf::Vector2f& aPosition);

private:
	CDebugDrawer();
	~CDebugDrawer();

	CLineDrawer myLineDrawer;
	std::vector<SLineCommand> myLineCommands;

	CTextDrawer myTextDrawer;
	std::vector<STextCommand> myTextCommands;
};

