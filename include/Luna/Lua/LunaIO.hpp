#pragma once
#include "Luna/IO/ConsoleLogger.hpp"
#include "Luna/IO/FileLogger.hpp"
#include "Luna/Lua/ScriptContext.hpp"

namespace Luna::IO
{
	void init(lua_State*);
}