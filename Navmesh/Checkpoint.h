#pragma once
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

class CCheckpoint
{
public:
	void Create(const sf::Vector2f& aPosition);
	void Render(sf::RenderWindow& aWindow);
private:
	sf::Texture myTexture;
	sf::Sprite mySprite;

	sf::Vector2f myPosition;
};