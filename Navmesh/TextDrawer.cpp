#include "TextDrawer.h"
#include "SFML/Graphics/RenderWindow.hpp"


sf::RenderWindow* CTextDrawer::ourWindow;

CTextDrawer::CTextDrawer()
{
	myFont.loadFromFile("fonts/arial.ttf");
	myText.setFont(myFont);
}

void CTextDrawer::SetWindow(sf::RenderWindow * aWindow)
{
	ourWindow = aWindow;
}

void CTextDrawer::DrawTextAt(const std::string & aText, const sf::Vector2f & aPosition, sf::Color aColor)
{
	myText.setString(aText);
	myText.setPosition(aPosition);
	myText.setFillColor(aColor);
	ourWindow->draw(myText);
}
