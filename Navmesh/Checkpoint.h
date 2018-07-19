#pragma once
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

class CCheckpoint
{
public:
	void SetTriggerCallback(sf::String& aCallbackName, int aCallbackId);

	void Create(const sf::Vector2f& aPosition);

	void RunPlayerVsCheckpointCollision(const sf::FloatRect& aPlayerCollision);

	void Render(sf::RenderWindow& aWindow);
private:
	void RunLuaCallback();

	sf::Texture myTexture;
	sf::Sprite mySprite;

	sf::Vector2f myPosition;

	sf::String myCallbackName;

	sf::Color myRenderColor;
	int myCallbackId;
};