#include "Game.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "LineDrawer.h"
#include <iostream>
#include "DebugDrawer.h"

std::vector<CCheckpoint> CGame::myCheckpoints;
CGoal CGame::myGoal;
bool CGame::myWonGame;

CGame::CGame(bool & aIsRunning)
	:myShouldRun(aIsRunning)
{
	myWindow = new sf::RenderWindow();
	
	sf::VideoMode vm;
	vm.width = 1600;
	vm.height = 900;

	myWindow->create(vm, "Scripting Labb", sf::Style::Close | sf::Style::Titlebar);

	CLineDrawer::SetWindow(myWindow);
}

void CGame::Init()
{
	myCheckpoints.reserve(100);
	
	myGoal.Init();
	CDebugDrawer::GetInstance().Init(*myWindow);
	CScriptManager::GetInstance().Init();
	CScriptManager::GetInstance().UseScript("script\\script.lua");
	RegisterExternalFunctions();
	CScriptManager::GetInstance().CallFunction("Init");
	myPlayer.Init({ 800, 450 });

	myWonGameTexture.loadFromFile("sprites/win.png");
	myWonGameSprite.setTexture(myWonGameTexture);
	myWonGameSprite.setPosition(800 - 360, 450 - 256);
	myWonGame = false;
}

#include <SFML\Window\Event.hpp>
void CGame::Update()
{
	if (myWonGame)
		return;

	float dt = myDeltaTimer.getElapsedTime().asSeconds();
	myDeltaTimer.restart();

	//CScriptManager::GetInstance().CallFunction("Update");
	CScriptManager::GetInstance().Update();
	myPlayer.Update(dt);


	sf::Event e;

	while (myWindow->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			myShouldRun = false;
		}
	}

}

void CGame::Render()
{
	myWindow->clear({ 50,50,50,255 });

	CDebugDrawer::GetInstance().Render();
	myPlayer.Render(myWindow);

	for (CCheckpoint& cp : myCheckpoints)
	{
		cp.Render(*myWindow);
		cp.RunPlayerVsCheckpointCollision(myPlayer.GetCollisionRect());
		myGoal.CheckPlayerVsGoalCollision(myPlayer.GetCollisionRect());
	}

	myGoal.Render(*myWindow);

	if (myWonGame)
	{
		myWindow->draw(myWonGameSprite);
	}

	myWindow->display();
}

int CGame::Print(lua_State * aLuaState)
{
	PrintInternal(aLuaState);
	return 0;
}

int CGame::DrawLine(lua_State * aLuaState)
{
	DrawLineInternal(aLuaState);
	return 0;
}

int CGame::DrawText(lua_State * aLuaState)
{
	DrawTextInternal(aLuaState);
	return 0;
}

int CGame::AddCheckpoint(lua_State* aLuaState)
{
	AddCheckpointInternal(aLuaState);

	return 0;
}

int CGame::RegisterTriggerCallback(lua_State* aLuaState)
{
	std::string callbackLuaFunc = lua_tostring(aLuaState, 1);
	int callbackId = lua_tonumber(aLuaState, 2);

	if (myCheckpoints.size() == 0)
	{
		myGoal.SetTriggerCallback(sf::String(callbackLuaFunc), callbackId);
		return 0;
	}

	myCheckpoints.back().SetTriggerCallback(sf::String(callbackLuaFunc), callbackId);
}

int CGame::SetGoalPosition(lua_State* aLuaState)
{
	myGoal.SetPosition(lua_tonumber(aLuaState, 1), lua_tonumber(aLuaState, 2));
	return 0;
}

int CGame::UnregisterCallback(lua_State * aLuaState)
{
	int index = lua_tonumber(aLuaState, 1);
	index--;

	if (index == -1)
	{
		myGoal.Unregister();
		return 0;
	}
	
	myCheckpoints[index].Unregister();

}

int CGame::UnlockGoal(lua_State* aLuaState)
{
	myGoal.Unlock();
	return 0;
}

int CGame::Win(lua_State* aLuaState)
{
	myWonGame = true;

	return 0;
}

void CGame::RegisterExternalFunctions()
{
	CScriptManager& SM = CScriptManager::GetInstance();
	SM.RegisterFunction("Print", Print, "Prints to console.");
	SM.RegisterFunction("DrawLine", DrawLine, "Draws a line.");
	SM.RegisterFunction("DrawText", DrawText, "Draws text on screen.");
	SM.RegisterFunction("AddCheckpoint", AddCheckpoint, "Adds a checkpoint at position");
	SM.RegisterFunction("RegisterTriggerCallback", RegisterTriggerCallback, "Registers a trigger callback");
	SM.RegisterFunction("SetGoalPosition", SetGoalPosition, "Sets goal position");
	SM.RegisterFunction("UnregisterTriggerCallback", UnregisterCallback, "Unregisters a callback");
	SM.RegisterFunction("UnlockGoal", UnlockGoal, "Unlocks the goal");
	SM.RegisterFunction("Win", Win, "Wins the game");
}

int CGame::PrintInternal(lua_State * aLuaState)
{
	int args = lua_gettop(aLuaState);

	std::string string = "";
	for (int i = 1; i <= args; ++i)
	{
		string += lua_tostring(aLuaState, i) == NULL ? "" : lua_tostring(aLuaState, i);
	}

		int result = lua_checkstack(aLuaState, 0);

	lua_pop(aLuaState, args + 1);

	std::cout << string << std::endl;
	return 0;
}

int CGame::DrawLineInternal(lua_State * aLuaState)
{
	float x1 = lua_tonumber(aLuaState, 1);
	float y1 = lua_tonumber(aLuaState, 2);
	float x2 = lua_tonumber(aLuaState, 3);
	float y2 = lua_tonumber(aLuaState, 4);

	sf::Vector2f from(x1, y1);
	sf::Vector2f to(x2, y2);

	lua_pop(aLuaState, 5);

	CDebugDrawer::GetInstance().DrawLine(from, to);

	return 0;
}

int CGame::DrawTextInternal(lua_State * aLuaState)
{
	std::string text = lua_tostring(aLuaState, 1);
	float x = lua_tonumber(aLuaState, 2);
	float y = lua_tonumber(aLuaState, 3);

	sf::Vector2f position(x, y);

	CDebugDrawer::GetInstance().DrawTextAt(text, position);

	return 0;
}

int CGame::AddCheckpointInternal(lua_State* aLuaState)
{
	float x = lua_tonumber(aLuaState, 1);
	float y = lua_tonumber(aLuaState, 2);

	sf::Vector2f position(x, y);

	myCheckpoints.push_back(CCheckpoint());
	myCheckpoints.back().Create(position);
	return 0;
}
