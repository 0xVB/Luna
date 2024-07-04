#include "Luna/Luna.h"

using namespace Luna;

bool Luna::debugMode = false;
lua_State* Luna::gLuaState = nullptr;
LawnApp* Luna::gApp = nullptr;
Luau::CompileOptions Luna::compileOptions = Luau::CompileOptions();
std::vector<LunaMod*> Luna::gLoadedMods = std::vector<LunaMod*>();

void Luna::InitiateLunaState()
{
	if (gLuaState)
		lua_close(gLuaState);
	gLuaState = luaL_newstate();
}