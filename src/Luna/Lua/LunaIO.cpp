#include "Luna/Lua/LunaIO.hpp"

Luna::Lua::ScriptContext* gContext;
int lua_print(lua_State* L)
{
	
	return 0;
}

void Luna::IO::init(lua_State* L)
{
	gContext = Luna::Lua::ScriptContext::getSingleton();
	lua_pushcfunction(L, lua_print, "print");
	lua_setglobal(L, "print");
}