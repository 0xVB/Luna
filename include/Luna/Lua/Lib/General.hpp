#pragma once
#include "Luna/Lua/Utils.hpp"

namespace Luna::Lib::General
{
	void openStatic(lua_State*);
	void openDynamic(lua_State*);
}