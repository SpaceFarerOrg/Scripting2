#pragma once
#include "SFML/Graphics/CircleShape.hpp"
#include "LineDrawer.h"
#include "../Script/include/LuaHeader.h"
#include "../Script/ScriptManager.h"
#include "Player.h"
#include <vector>
#include "Checkpoint.h"
#include "SFML/System/Clock.hpp"
#include "Goal.h"

#pragma comment(lib, "../bin/lib/Script")

namespace sf
{
	class RenderWindow;
}

class CGame
{
public:
	CGame(bool& aIsRunning);
	void Init();
	void Update();
	void Render();

	static int Print(lua_State* aLuaState);
	static int DrawLine(lua_State* aLuaState);
	static int DrawText(lua_State* aLuaState);
	static int AddCheckpoint(lua_State* aLuaState);
	static int RegisterTriggerCallback(lua_State* aLuaState);
	static int SetGoalPosition(lua_State* aLuaState);

	void RegisterExternalFunctions();
private:
	sf::Clock myDeltaTimer;

	static int PrintInternal(lua_State* aLuaState);
	static int DrawLineInternal(lua_State* aLuaState);
	static int DrawTextInternal(lua_State* aLuaState);
	static int AddCheckpointInternal(lua_State* aLuaState);


	static std::vector<CCheckpoint> myCheckpoints;
	static CGoal myGoal;

	bool& myShouldRun;
	sf::RenderWindow* myWindow;
	CLineDrawer myLineDrawer;
	CPlayer myPlayer;
};