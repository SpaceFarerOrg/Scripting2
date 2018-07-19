#include "Player.h"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Init(const sf::Vector2f & aPos)
{
	myPosition = aPos;
	myTexture.loadFromFile("sprites/playerCar.png");
	mySprite.setTexture(myTexture);
	mySprite.setOrigin(mySprite.getGlobalBounds().width * .5f, mySprite.getGlobalBounds().height / 2.f);
	mySpeed = 0.f;
}

void CPlayer::Update(float aDT)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		myRotation -= 10.f * aDT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		myRotation += 10.f * aDT;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		mySpeed += 500.f * aDT;
	}
	else
	{
		mySpeed *= 0.9995f;
	}

	myVelocity = mySpeed * sf::Vector2f(cosf(myRotation), sinf(myRotation));

	myPosition += myVelocity * aDT;
}

void CPlayer::Render(sf::RenderWindow * aRW)
{
	mySprite.setPosition(myPosition);
	mySprite.setRotation(myRotation * (180.f / 3.14f));

	aRW->draw(mySprite);
}
