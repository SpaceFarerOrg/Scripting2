#include "Checkpoint.h"
#include "DebugDrawer.h"
#include "../Script/ScriptManager.h"

void CCheckpoint::SetTriggerCallback(sf::String & aCallbackName, int aCallbackId)
{
	myCallbackName = aCallbackName;
	myCallbackId = aCallbackId;
}

void CCheckpoint::Create(const sf::Vector2f & aPosition)
{
	myPosition = aPosition;

	myTexture.loadFromFile("sprites/checkpoint.png");
	mySprite.setTexture(myTexture);
	mySprite.setPosition(myPosition);
	myRenderColor = sf::Color::White;
}

void CCheckpoint::RunPlayerVsCheckpointCollision(const sf::FloatRect & aPlayerCollision)
{
	if (aPlayerCollision.intersects(mySprite.getGlobalBounds()))
	{
		RunLuaCallback();
	}
}

void CCheckpoint::Render(sf::RenderWindow& aWindow)
{
	mySprite.setColor(myRenderColor);
	aWindow.draw(mySprite);
}

void CCheckpoint::RunLuaCallback()
{
	myRenderColor = sf::Color::Green;
	CScriptManager::GetInstance().CallFunction(myCallbackName, &myCallbackId);
}
