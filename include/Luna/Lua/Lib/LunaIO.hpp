#pragma once
#include "Luna/IO/ConsoleLogger.hpp"
#include "Luna/IO/FileLogger.hpp"
#include <lua.h>


namespace Luna::Lua::Lib::IO
{
	void init(lua_State* state);
}