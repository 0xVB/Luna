#pragma once
#include "Luna/IO/ConsoleLogger.hpp"
#include "Luna/IO/FileLogger.hpp"
#include <lua.h>


namespace Luna::Lib::IO
{
	void openStatic(lua_State* L);
}