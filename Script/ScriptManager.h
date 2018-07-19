#pragma once
extern "C"
{
#include "../Script/include/LuaHeader.h"
}

#include "file_watcher.h"

#pragma comment(lib, "..\\bin\\lib\\Lua")

#include <string>
#include <functional>
#include <thread>
#include <iostream>

class CScriptManager
{
public:

	static CScriptManager& GetInstance();

	void Init();
	void RegisterFunction(const std::string& aFunctionName, int aFunction(lua_State*), const std::string& aHelpText);
	void Update();

	template <typename argOne = void*, typename argTwo = void*, typename argThree = void*>
	void CallFunction(const std::string& aFunctionName, argOne* = nullptr, argTwo* = nullptr, argThree* = nullptr);
	bool UseScript(const std::string& aPath);

private:
	CScriptManager();
	~CScriptManager();

	int GetFunction(const std::string& aFunctionName);
	int EvaluateAndPushValueToLua(float* aFloat);
	int EvaluateAndPushValueToLua(int* aInt);
	int EvaluateAndPushValueToLua(const char* aString);
	int EvaluateAndPushValueToLua(bool* aBool);
	int EvaluateAndPushValueToLua(void** aNothing);

	
	std::string myFilePath;

	Tga2D::CFileWatcher myFileWatcher;

	lua_State* myLuaState;
};


template<typename argOne, typename argTwo, typename argThree>
inline void CScriptManager::CallFunction(const std::string & aFunctionName, argOne* a1, argTwo* a2, argThree* a3)
{
	if (GetFunction(aFunctionName) != LUA_TFUNCTION)
	{
		std::cout << "Error in function " << aFunctionName << ", check spelling?" << std::endl;
		system("pause");
		return;
	}

	int argCount = 0;
	argCount += EvaluateAndPushValueToLua(a1);
	argCount += EvaluateAndPushValueToLua(a2);
	argCount += EvaluateAndPushValueToLua(a3);

	if (lua_pcall(myLuaState, argCount, 1, 0) != 0)
	{
		std::cout << lua_tostring(myLuaState, -1) << std::endl;
		//system("pause");
	}
	lua_pop(myLuaState, argCount);
}
