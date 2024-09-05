#include <Windows.h>
#include "Luna/Lua/Lib/General.hpp"

int lua_delay(lua_State* L)
{
	int del = LuaToNum(L, 1);
	del = (del <= 0) ? 1 : del;
	Sleep(del);
	return 0;
}

int o_typeof;
int lua_typeof(lua_State* L)
{
	closure_header();
	if (ltop <= 0)
	{
		lua_pushstring(L, "nil");
		return 1;
	}

	if (!lua_getmetatable(L, 1))
	{
	otype:
		lua_getref(L, o_typeof);
		lua_pushvalue(L, 1);
		lua_call(L, 1, 1);
		return 1;
	}

	lua_pushstring(L, "__typeof");

}

void Luna::Lib::General::openStatic(lua_State* L)
{
	closure_header();

	lua_getglobal(L, "coroutine");
	lua_pushstring(L, "yield");
	lua_gettable(L, -2);
	lua_setglobal(L, "wait");

	lua_pushcclosure(L, lua_delay, "delay", 0);
	lua_setglobal(L, "delay");

	resetltop();
}

void Luna::Lib::General::openDynamic(lua_State* L)
{

}