#pragma once
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

class CGoal
{
public:
	void SetTriggerCallback(sf::String& aCallbackName, int aCallbackId);
	void Init();
	void SetPosition(float aX, float aY);
	void Unlock();

	void Unregister() { myHasCallback = false; }

	void CheckPlayerVsGoalCollision(const sf::FloatRect& aPlayerCollision);

	void Render(sf::RenderWindow& aWindow);
private:
	void RunLuaCallback();
	sf::Texture myTexture;
	sf::Sprite mySprite;

	bool myIsLocked : 1;

	bool myHasCallback;

	sf::String myCallbackName;
	int myCallbackId;
};