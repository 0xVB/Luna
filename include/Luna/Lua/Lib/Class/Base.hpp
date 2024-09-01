#pragma once
#include <lua.h>
#include <string>
#include <vector>
#include <map>

#include "Luna/Lua/Utils.hpp"

namespace Luna::Lib::Class
{
#define GetInstance(idx) (LunaInstance*)lua_touserdata(L, idx)
#define GetSelf() auto self = GetInstance(1)
	// Bases
	class BaseField;// An abstract interface for a field (member of a class)

	// A LunaClass template. Contains all the metamethods and classnames and is used to create the metatable.
	class LunaClass;

	// An instance of a class. Created within heavy userdatas.
	class LunaInstance;

	class BaseField
	{
	public:
		std::string fieldName;
		virtual int __index(lua_State*) = 0;
		virtual int __newindex(lua_State*) = 0;
	};

	template <typename T>
	class OffsetField : public BaseField
	{
		bool readOnly;
		size_t offset;

	public:
		virtual int __index(lua_State*) override = 0;
		virtual int __newindex(lua_State*) override = 0;

		OffsetField(std::string Name, bool ReadOnly, size_t Offset)
		{
			fieldName = Name;
			readOnly = ReadOnly;
			offset = Offset;
		}
	};

	class LunaClass
	{
	public:
		std::string className;
		std::vector<LunaClass*> inheritance;
		std::map<std::string, bool> subClasses;
		std::map<std::string, BaseField*> fields;
		std::map<unsigned int, int> instances;

		lua_CFunction __index;
		lua_CFunction __newindex;
		lua_CFunction __tostring;
		lua_CFunction __tonumber;
		lua_CFunction __typeof;
		lua_CFunction __is;

		lua_CFunction __concat;
		lua_CFunction __iter;
		lua_CFunction __call;
		lua_CFunction __idiv;

		lua_CFunction __unm;
		lua_CFunction __add;
		lua_CFunction __sub;
		lua_CFunction __mul;
		lua_CFunction __div;
		lua_CFunction __mod;
		lua_CFunction __pow;
		lua_CFunction __len;

		lua_CFunction __eq;
		lua_CFunction __lt;
		lua_CFunction __le;
		lua_CFunction __gc;

		bool customFields;
		int __metatable;// __metatable lvalue
		int __mt;// real metatable

		void AddField(BaseField*);

		void NewInstance(lua_State*, void*);
		void NewInstance(lua_State*, unsigned int);

		void AddSubClass(std::string SubClassName);
		void Inherit(LunaClass* From);

		void Finalize(lua_State*);
		LunaClass(lua_State*, std::string Name, int _mtlock = -2);

		static lua_CFunction default_index;
		static lua_CFunction default_newindex;
		static lua_CFunction default_tostring;
		static lua_CFunction default_tonumber;
		static lua_CFunction default_typeof;
		static lua_CFunction default_is;

		static lua_CFunction default_concat;
		static lua_CFunction default_iter;
		static lua_CFunction default_call;
		static lua_CFunction default_idiv;

		static lua_CFunction default_unm;
		static lua_CFunction default_add;
		static lua_CFunction default_sub;
		static lua_CFunction default_mul;
		static lua_CFunction default_div;
		static lua_CFunction default_mod;
		static lua_CFunction default_pow;
		static lua_CFunction default_len;

		static lua_CFunction default_eq;
		static lua_CFunction default_lt;
		static lua_CFunction default_le;
		static lua_CFunction default_gc;
	};

	class LunaInstance
	{
		bool _alive;
	public:
		LunaClass* iClass;

		int iExtraFields;
		union
		{
			unsigned int iData;
			void* iPtr;
		};

		bool IsAlive();
		void Revive();

		void Destroy(lua_State*);
	};

	void openDynamic(lua_State*);
}