#pragma once
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

class CGoal
{
public:
	void Init();
	void SetPosition(float aX, float aY);
	void Unlock();
	void Render(sf::RenderWindow& aWindow);
private:
	sf::Texture myTexture;
	sf::Sprite mySprite;

	bool myIsLocked : 1;

};