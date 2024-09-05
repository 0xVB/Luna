#include "Luna/Lua/Lib/Class/LunaClass.hpp"
#include "Luna/Lua/Utils.hpp"

using namespace Luna::Lib::Class;

int def_index(lua_State* L)
{
	closure_header();
	GetSelf();
	auto Field = LuaToStr(L, 2);
	auto Class = self->iClass;

	if (Field == "Destroyed")
	{
		lua_pushboolean(L, !self->IsAlive());
		return 1;
	}

	if (!self->IsAlive())
	{
		lua_pushstring(L, ("This " + Class->className + " was destroyed.").c_str());
		lua_error(L);
	}

	if (Class->fields.contains(Field))
		return Class->fields[Field]->__index(L);

	if (!Class->customFields)
	{
		lua_pushstring(L, (Field + " is not a valid member of " + Class->className + ".").c_str());
		lua_error(L);
	}

	// Custom field handling
	lua_getref(L, self->iExtraFields);
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);
	return 1;
}

int def_newindex(lua_State* L)
{
	closure_header();
	GetSelf();
	auto Field = LuaToStr(L, 2);
	auto Class = self->iClass;

	if (Field == "Destroyed")
	{
		lua_pushstring(L, "Destroyed is read-only.");
		lua_error(L);
		return 0;
	}

	if (!self->IsAlive())
	{
		lua_pushstring(L, ("This " + Class->className + " was destroyed.").c_str());
		lua_error(L);
	}

	if (Class->fields.contains(Field))
		return Class->fields[Field]->__newindex(L);

	if (!Class->customFields)
	{
		lua_pushstring(L, (Field + " is not a valid member of " + Class->className + ".").c_str());
		lua_error(L);
	}

	// Custom field handling
	lua_getref(L, self->iExtraFields);
	lua_pushvalue(L, 2);
	lua_pushvalue(L, 3);
	lua_settable(L, -3);
	return 0;
}

int def_tostring(lua_State* L)
{
	closure_header();
	GetSelf();

	lua_pushstring(L, self->iClass->className.c_str());
	return 1;
}

int def_tonumber(lua_State* L)
{
	closure_header();
	GetSelf();

	lua_pushstring(L, (self->iClass->className + " cannot be cast to a number.").c_str());
	lua_error(L);
}

int def_typeof(lua_State* L)
{
	closure_header();
	GetSelf();

	lua_pushstring(L, self->iClass->className.c_str());
	return 1;
}

int def_concat(lua_State* L)
{
	closure_header();
	GetSelf();

	lua_pushstring(L, (self->iClass->className + " cannot be concatenated.").c_str());
	lua_error(L);
}

int def_iter(lua_State* L)
{
	closure_header();
	GetSelf();

	lua_pushstring(L, (self->iClass->className + " cannot be iterated.").c_str());
	lua_error(L);
}

int def_call(lua_State* L)
{
	closure_header();
	GetSelf();

	lua_pushstring(L, (self->iClass->className + " cannot be called.").c_str());
	lua_error(L);
}

int def_is(lua_State* L)
{
	closure_header();
	GetSelf();

	auto cname = LuaToStr(L, 1);
	lua_pushboolean(L, (cname == self->iClass->className || self->iClass->subClasses.contains(cname)));
	return 1;
}

lua_CFunction LunaClass::default_index = def_index;
lua_CFunction LunaClass::default_newindex = def_newindex;
lua_CFunction LunaClass::default_tostring = def_tostring;
lua_CFunction LunaClass::default_tonumber = def_tonumber;
lua_CFunction LunaClass::default_typeof = def_typeof;
lua_CFunction LunaClass::default_concat = def_concat;
lua_CFunction LunaClass::default_iter = def_iter;
lua_CFunction LunaClass::default_call = def_call;
lua_CFunction LunaClass::default_is = def_is;

lua_CFunction LunaClass::default_idiv = def_index;
lua_CFunction LunaClass::default_unm = def_index;
lua_CFunction LunaClass::default_add = def_index;
lua_CFunction LunaClass::default_sub = def_index;
lua_CFunction LunaClass::default_mul = def_index;
lua_CFunction LunaClass::default_div= def_index;
lua_CFunction LunaClass::default_pow = def_index;
lua_CFunction LunaClass::default_mod = def_index;
lua_CFunction LunaClass::default_len = def_index;

lua_CFunction LunaClass::default_eq = def_index;
lua_CFunction LunaClass::default_lt = def_index;
lua_CFunction LunaClass::default_le = def_index;
lua_CFunction LunaClass::default_gc = def_index;