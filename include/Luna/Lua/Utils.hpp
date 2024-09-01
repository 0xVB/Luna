#pragma once
#include <string>
#include <lua.h>

bool LuaTypeCheck(lua_State* L, int Idx, std::string TypeName);
double LuaToNum(lua_State* L, int Idx, bool* Success = nullptr);
std::string LuaToStr(lua_State* L, int Idx, bool* Success = nullptr);

#define closure_header() int ltop = lua_gettop(L)
#define resetltop() lua_settop(L, ltop)
#define adjust(v) v = (v > 0) ? v : lua_gettop(L) + 1 + v