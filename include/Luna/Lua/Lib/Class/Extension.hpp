#pragma once
#include "Base.hpp"

template <>
class Luna::Lib::Class::OffsetField<int> : public BaseField
{
	bool readOnly;
	size_t offset;

public:
	virtual int __index(lua_State* L) override
	{
		LunaInstance* Instance = (LunaInstance*)lua_touserdata(L, 1);
		auto iPtr = (int*)(Instance->iData + offset);
		lua_pushnumber(L, *iPtr);
		return 1;
	}

	virtual int __newindex(lua_State* L) override
	{
		if (readOnly)
		{
			lua_pushstring(L, (fieldName + " is read-only").c_str());
			lua_error(L);
		}

		bool Success = false;
		int num = (int)LuaToNum(L, 3, &Success);
		if (!Success)
		{
			lua_pushstring(L, ("Expected integer for '" + fieldName + "', got " + lua_typename(L, lua_type(L, 3)) + ".").c_str());
			lua_error(L);
		}

		LunaInstance* Instance = (LunaInstance*)lua_touserdata(L, 1);
		auto iPtr = (int*)(Instance->iData + offset);

		*iPtr = num;
		return 0;
	}

	OffsetField(std::string Name, bool ReadOnly, size_t Offset)
	{
		fieldName = Name;
		readOnly = ReadOnly;
		offset = Offset;
	}
};

template <>
class Luna::Lib::Class::OffsetField<unsigned int> : public BaseField
{
	bool readOnly;
	size_t offset;

public:
	virtual int __index(lua_State* L) override
	{
		LunaInstance* Instance = (LunaInstance*)lua_touserdata(L, 1);
		auto iPtr = (unsigned int*)(Instance->iData + offset);
		lua_pushnumber(L, *iPtr);
		return 1;
	}

	virtual int __newindex(lua_State* L) override
	{
		if (readOnly)
		{
			lua_pushstring(L, (fieldName + " is read-only").c_str());
			lua_error(L);
		}

		bool Success = false;
		unsigned int num = (unsigned int)LuaToNum(L, 3, &Success);
		if (!Success)
		{
			lua_pushstring(L, ("Expected unsigned integer for '" + fieldName + "', got " + lua_typename(L, lua_type(L, 3)) + ".").c_str());
			lua_error(L);
		}

		LunaInstance* Instance = (LunaInstance*)lua_touserdata(L, 1);
		auto iPtr = (unsigned int*)(Instance->iData + offset);

		*iPtr = num;
		return 0;
	}

	OffsetField(std::string Name, bool ReadOnly, size_t Offset)
	{
		fieldName = Name;
		readOnly = ReadOnly;
		offset = Offset;
	}
};

#include "Lunacy/PopStructs.h"
template <>
class Luna::Lib::Class::OffsetField<PopString> : public BaseField
{
	bool readOnly;
	size_t offset;

public:
	virtual int __index(lua_State* L) override
	{
		LunaInstance* Instance = (LunaInstance*)lua_touserdata(L, 1);
		auto iPtr = (PopString*)(Instance->iData + offset);
		lua_pushstring(L, iPtr->c_str());
		return 1;
	}

	virtual int __newindex(lua_State* L) override
	{
		if (readOnly)
		{
			lua_pushstring(L, (fieldName + " is read-only").c_str());
			lua_error(L);
		}

		bool Success = false;
		std::string str = LuaToStr(L, 3, &Success);
		if (!Success)
		{
			lua_pushstring(L, ("Expected string for '" + fieldName + "', got " + lua_typename(L, lua_type(L, 3)) + ".").c_str());
			lua_error(L);
		}

		LunaInstance* Instance = (LunaInstance*)lua_touserdata(L, 1);
		auto iPtr = (PopString*)(Instance->iData + offset);

		*iPtr = str;
		return 0;
	}

	OffsetField(std::string Name, bool ReadOnly, size_t Offset)
	{
		fieldName = Name;
		readOnly = ReadOnly;
		offset = Offset;
	}
};

template <>
class Luna::Lib::Class::OffsetField<std::string> : public BaseField
{
	bool readOnly;
	size_t offset;

public:
	virtual int __index(lua_State* L) override
	{
		LunaInstance* Instance = (LunaInstance*)lua_touserdata(L, 1);
		auto iPtr = (std::string*)(Instance->iData + offset);
		lua_pushstring(L, iPtr->c_str());
		return 1;
	}

	virtual int __newindex(lua_State* L) override
	{
		if (readOnly)
		{
			lua_pushstring(L, (fieldName + " is read-only").c_str());
			lua_error(L);
		}

		bool Success = false;
		std::string str = LuaToStr(L, 3, &Success);
		if (!Success)
		{
			lua_pushstring(L, ("Expected string for '" + fieldName + "', got " + lua_typename(L, lua_type(L, 3)) + ".").c_str());
			lua_error(L);
		}

		LunaInstance* Instance = (LunaInstance*)lua_touserdata(L, 1);
		auto iPtr = (std::string*)(Instance->iData + offset);

		*iPtr = str;
		return 0;
	}

	OffsetField(std::string Name, bool ReadOnly, size_t Offset)
	{
		fieldName = Name;
		readOnly = ReadOnly;
		offset = Offset;
	}
};