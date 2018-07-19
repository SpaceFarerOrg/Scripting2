#include "Checkpoint.h"
#include "DebugDrawer.h"

void CCheckpoint::Create(const sf::Vector2f & aPosition)
{
	myPosition = aPosition;

	myTexture.loadFromFile("sprites/checkpoint.png");
	mySprite.setTexture(myTexture);
	mySprite.setPosition(myPosition);
}

void CCheckpoint::Render(sf::RenderWindow& aWindow)
{
	aWindow.draw(mySprite);
}
