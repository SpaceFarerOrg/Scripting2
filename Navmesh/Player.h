#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace sf
{
	class RenderWindow;
}

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

	void Init(const sf::Vector2f& aPos);void Update(float aDT);void Render(sf::RenderWindow* aRW);

private:
	sf::Vector2f myPosition;
	sf::Sprite mySprite;
	sf::Texture myTexture;

	float mySpeed;
	sf::Vector2f myVelocity;
	float myRotation;
};

