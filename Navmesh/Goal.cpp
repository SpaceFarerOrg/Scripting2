#include "Goal.h"
#include "../Script/ScriptManager.h"


void CGoal::SetTriggerCallback(sf::String & aCallbackName, int aCallbackId)
{
	myCallbackName = aCallbackName;
	myCallbackId = aCallbackId;
}

void CGoal::Init()
{
	myTexture.loadFromFile("sprites/goal.png");
	mySprite.setTexture(myTexture);
	myIsLocked = true;
}

void CGoal::SetPosition(float aX, float aY)
{
	mySprite.setPosition(aX, aY);
}

void CGoal::Unlock()
{
	myIsLocked = false;
}

void CGoal::Render(sf::RenderWindow & aWindow)
{
	sf::Color renderColor = sf::Color(155,155,155,255);

	if (myIsLocked == false)
	{
		renderColor = sf::Color::White;
	}

	mySprite.setColor(renderColor);

	aWindow.draw(mySprite);

}

void CGoal::RunLuaCallback()
{
	CScriptManager::GetInstance().CallFunction(myCallbackName, &myCallbackId);
}
