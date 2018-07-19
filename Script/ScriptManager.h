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
	void CallFunction(const std::string& aFunctionName, argOne = nullptr, argTwo = nullptr, argThree = nullptr);
	bool UseScript(const std::string& aPath);

private:
	CScriptManager();
	~CScriptManager();

	int GetFunction(const std::string& aFunctionName);
	template <typename T>
	int EvaluateAndPushValueToLua(T aT);

	void CallFunctionInternal(const std::string& aFunctionName);
	
	std::string myFilePath;

	Tga2D::CFileWatcher myFileWatcher;

	lua_State* myLuaState;
};


template<typename argOne, typename argTwo, typename argThree>
inline void CScriptManager::CallFunction(const std::string & aFunctionName, argOne a1, argTwo a2, argThree a3)
{
	CallFunctionInternal(aFunctionName);
}

template<typename T>
inline int CScriptManager::EvaluateAndPushValueToLua(T aT)
{
	if (aT == nullptr)
		return 0;

	if (typeid(T) == typeid(float) || typeid(T) == typeid(int))
	{
		lua_pushnumber(myLuaState, *reinterpret_cast<float*>(aT));
	}
	else if (typeid(T) == typeid(std::string))
	{
		lua_pushstring(myLuaState, (*reinterpret_cast<std::string*>(aT)).c_str());
	}
	else if (typeid(T) == typeid(bool))
	{
		lua_pushboolean(myLuaState, *reinterpret_cast<bool*>(aT));
	}
	return 1;
}
