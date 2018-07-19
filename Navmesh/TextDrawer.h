#pragma once
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/Text.hpp"

namespace sf
{
	class RenderWindow;
}

class CTextDrawer
{
public:
	CTextDrawer();

	static void SetWindow(sf::RenderWindow* aWindow);

	void DrawTextAt(const std::string& aText, const sf::Vector2f& aPosition, sf::Color aColor = { 0,255,0,255 });
private:
	static sf::RenderWindow* ourWindow;

	sf::Text myText;
	sf::Font myFont;
};
