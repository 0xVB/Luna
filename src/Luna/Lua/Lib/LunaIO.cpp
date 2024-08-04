#include "Luna/Lua/Lib/LunaIO.hpp"
#include "Luna/Application.hpp"

#include <lualib.h>
#include <string>

int printOut(lua_State* L, LogLevel level) {
	int T = lua_gettop(L);
	auto app = Luna::Application::getSingleton();
	if (T == 0) {
		app->getLogger()->log(level, "");
		return 0;
	}

	std::string out = "";
	for (int i = 1; i <= T; i++)
	{
		out += lua_tostring(L, i);
	}
	app->getLogger()->log(level, out.c_str());

	return 0;
}

int luaPrint(lua_State* L)
{
	return printOut(L, LogLevel::none);
}

int luaWarn(lua_State* L)
{
	return printOut(L, LogLevel::warn);
}

int luaInfo(lua_State* L)
{
	return printOut(L, LogLevel::info);
}

luaL_Reg IOFuncs[] = {
	{"print", luaPrint},
	{"warn",  luaWarn},
	{"info",  luaInfo},
	{NULL, NULL},
};


void Luna::Lib::IO::openStatic(lua_State* L)
{
	luaL_register(L, "_G", IOFuncs);
}