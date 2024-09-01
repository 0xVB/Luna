#include "Luna/Lua/Lib/General.hpp"

void Luna::Lib::General::openStatic(lua_State* L)
{
	closure_header();

	lua_getglobal(L, "coroutine");
	lua_pushstring(L, "yield");
	lua_gettable(L, -2);
	lua_setglobal(L, "wait");

	resetltop();
}

void Luna::Lib::General::openDynamic(lua_State* L)
{

}