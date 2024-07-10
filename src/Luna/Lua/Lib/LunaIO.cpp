#include "Luna/Lua/Lib/LunaIO.hpp"

int lua_print(lua_State* L)
{
	
	return 0;
}

void Luna::Lua::Lib::IO::init(lua_State* L)
{
	lua_pushcfunction(L, lua_print, "print");
	lua_setglobal(L, "print");
}