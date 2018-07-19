#include "ScriptManager.h"
#include <iostream>
#include <fstream>
#include <fileapi.h>

CScriptManager & CScriptManager::GetInstance()
{
	static CScriptManager me;
	return me;
}

void CScriptManager::Init()
{
	myLuaState = luaL_newstate();
	luaL_openlibs(myLuaState);

	HANDLE fileH = CreateFile("exposedScriptFunctions.txt", GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle(fileH);

	std::ofstream docFile;

	docFile.open("exposedScriptFunctions.txt", std::ios::trunc);
	docFile << "Exposed Functions:" << std::endl << std::endl;
	docFile.close();
}

void CScriptManager::RegisterFunction(const std::string & aFunctionName, int aFunction(lua_State*), const std::string & aHelpText)
{
	lua_register(myLuaState, aFunctionName.c_str(), aFunction);


	std::ofstream docFile;
	
	docFile.open("exposedScriptFunctions.txt", std::ios::app);

	docFile << aFunctionName << " : " << aHelpText << std::endl;

	docFile.close();
}

void CScriptManager::Update()
{
	myFileWatcher.FlushChanges();
}

bool CScriptManager::UseScript(const std::string & aPath)
{
	if (int fel = luaL_dofile(myLuaState, aPath.c_str()) != 0)
	{
		std::cout << "Could not open file " << aPath << std::endl;
		std::cout << lua_tostring(myLuaState, -1);

		return false;
	}//Failcheck this. If file is not found go into "fix" state

	myFilePath = aPath;

	std::wstring wPath(aPath.begin(), aPath.end());
	bool didStartFileWatch = myFileWatcher.WatchFileChangeWithDependencies(wPath, 
		[&](const std::wstring& aWStr)->void {
		luaL_dofile(myLuaState, myFilePath.c_str()); 
	});
	return true;
}

CScriptManager::CScriptManager()
{
}


CScriptManager::~CScriptManager()
{
}

int CScriptManager::GetFunction(const std::string & aFunctionName)
{
	int result = lua_getglobal(myLuaState, aFunctionName.c_str());
	return result;
}



int CScriptManager::EvaluateAndPushValueToLua(float* aFloat)
{
	if (aFloat == nullptr)
		return 0;

	lua_pushnumber(myLuaState, *aFloat);
	return 1;
}

int CScriptManager::EvaluateAndPushValueToLua(int* aInt)
{
	if (aInt == nullptr)
		return 0;

	lua_pushnumber(myLuaState, *aInt);
	return 1;
}

int CScriptManager::EvaluateAndPushValueToLua(const char* aString)
{
	if (aString == nullptr)
		return 0;

	lua_pushstring(myLuaState, aString);
	return 1;
}

int CScriptManager::EvaluateAndPushValueToLua(bool* aBool)
{
	if (aBool == nullptr)
		return 0;

	lua_pushboolean(myLuaState, *aBool);
	return 1;
}

int CScriptManager::EvaluateAndPushValueToLua(void** aNothing)
{
	return 0;
}