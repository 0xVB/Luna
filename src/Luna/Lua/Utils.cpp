#include "Luna/Lua/Utils.hpp"

bool LuaTypeCheck(lua_State* L, int Idx, std::string TypeName)
{
	closure_header();
	adjust(Idx);

	lua_getglobal(L, "type");
	lua_pushvalue(L, Idx);
	lua_pcall(L, 1, 1, 0);
	
	auto Type = std::string(lua_tostring(L, -1));
	if (Type == TypeName) return true;
	resetltop();

	if (!lua_getmetatable(L, Idx))
	{
		// No metatable
		resetltop();
		return false;
	}

	lua_pushstring(L, "__is");
	lua_rawget(L, -2);

	if (!lua_isfunction(L, -1))
	{
		// No __is function
		resetltop();
		return false;
	}

	lua_pushvalue(L, Idx);
	lua_pushstring(L, TypeName.c_str());

	int Passed = lua_pcall(L, 2, 1, 0);
	auto Result = lua_toboolean(L, -1);
	resetltop();

	if (Passed == LUA_OK) return Result;
	else return false;
}

#define state(state) if (Success) *Success = state
double LuaToNum(lua_State* L, int Idx, bool* Success)
{
	closure_header();
	adjust(Idx);

	state(true);
	if (lua_isnumber(L, Idx))
		return lua_tonumber(L, Idx);

	if (!lua_getmetatable(L, Idx))
	{
		// No metatable
		state(false);
		resetltop();
		return 0;
	}

	lua_pushstring(L, "__tonumber");
	lua_rawget(L, -2);

	if (!lua_isfunction(L, -1))
	{
		// No __tonumber function
		state(false);
		resetltop();
		return 0;
	}

	lua_pushvalue(L, Idx);
	int Passed = lua_pcall(L, 1, 1, 0);
	double Result = lua_tonumber(L, -1);

	resetltop();
	state(Passed);
	if (Passed) return Result;
	else return 0;
}

std::string LuaToStr(lua_State* L, int Idx, bool* Success)
{
	closure_header();
	adjust(Idx);

	state(true);
	if (lua_isstring(L, Idx))
		return lua_tostring(L, Idx);

	if (!lua_getmetatable(L, Idx))
	{
		// No metatable
		state(false);
		resetltop();
		return "";
	}

	lua_pushstring(L, "__tostring");
	lua_rawget(L, -2);

	if (!lua_isfunction(L, -1))
	{
		// No __tostring function
		state(false);
		resetltop();
		return "";
	}

	lua_pushvalue(L, Idx);
	int Passed = lua_pcall(L, 1, 1, 0);
	auto Result = lua_tostring(L, -1);

	resetltop();
	state(Passed);
	if (Passed) return Result;
	else return "";
}