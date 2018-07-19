#include "Game.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "LineDrawer.h"
#include <iostream>
#include "DebugDrawer.h"

std::vector<CCheckpoint> CGame::myCheckpoints;

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
	CDebugDrawer::GetInstance().Init(*myWindow);
	CScriptManager::GetInstance().Init();
	CScriptManager::GetInstance().UseScript("script\\script.lua");
	RegisterExternalFunctions();
	CScriptManager::GetInstance().CallFunction("Init");
	myPlayer.Init({ 800, 450 });
}

void CGame::Update()
{
	float dt = myDeltaTimer.getElapsedTime().asSeconds();
	myDeltaTimer.restart();

	//CScriptManager::GetInstance().CallFunction("Update");
	CScriptManager::GetInstance().Update();
	myPlayer.Update(dt);
}

void CGame::Render()
{
	myWindow->clear({ 50,50,50,255 });

	CDebugDrawer::GetInstance().Render();
	myPlayer.Render(myWindow);

	for (CCheckpoint& cp : myCheckpoints)
	{
		cp.Render(*myWindow);
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

void CGame::RegisterExternalFunctions()
{
	CScriptManager& SM = CScriptManager::GetInstance();
	SM.RegisterFunction("Print", Print, "Prints to console.");
	SM.RegisterFunction("DrawLine", DrawLine, "Draws a line.");
	SM.RegisterFunction("DrawText", DrawText, "Draws text on screen.");
	SM.RegisterFunction("AddCheckpoint", AddCheckpoint, "Adds a checkpoint at position");
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
