#include "Luna/Lua/Lib/Class/LunaClass.hpp"
#include "Luna/Lua/Utils.hpp"

using namespace Luna::Lib::Class;

void LunaClass::AddField(BaseField* Field)
{
	fields[Field->fieldName] = Field;
}

void LunaClass::NewInstance(lua_State* L, void* Ptr)
{
	// Check if instance with same data already exists
	if (instances.contains((unsigned int)Ptr))
	{
		lua_getref(L, instances[(unsigned int)Ptr]);
		return;
	}

	LunaInstance* New = (LunaInstance*)lua_newuserdata(L, sizeof(LunaInstance));
	instances[(unsigned int)Ptr] = lua_ref(L, -1);

	New->Revive();
	New->iClass = this;
	New->iPtr = Ptr;

	if (customFields)
	{
		// Create field table
		lua_newtable(L);
		New->iExtraFields = lua_ref(L, -1);
		lua_pop(L, 1);
	}

	lua_getref(L, __mt);
	lua_setmetatable(L, -2);
}

void LunaClass::NewInstance(lua_State* L, unsigned int Data)
{
	// Check if instance with same data already exists
	if (instances.contains(Data))
	{
		lua_getref(L, instances[Data]);
		return;
	}

	LunaInstance* New = (LunaInstance*)lua_newuserdata(L, sizeof(LunaInstance));
	instances[Data] = lua_ref(L, -1);

	New->Revive();
	New->iClass = this;
	New->iData = Data;

	if (customFields)
	{
		// Create field table
		lua_newtable(L);
		New->iExtraFields = lua_ref(L, -1);
		lua_pop(L, 1);
	}

	lua_getref(L, __mt);
	lua_setmetatable(L, -2);
}

void LunaClass::AddSubClass(std::string SubClassName)
{
	subClasses[SubClassName] = true;
}

#define inheritmt(mt) if (!mt) mt = From->mt;
void LunaClass::Inherit(LunaClass* From)
{
#pragma region Inherit Metamethods
	inheritmt(__index);
	inheritmt(__newindex);
	inheritmt(__tostring);
	inheritmt(__tonumber);
	inheritmt(__typeof);
	inheritmt(__is);

	inheritmt(__concat);
	inheritmt(__iter);
	inheritmt(__call);
	inheritmt(__idiv);

	inheritmt(__unm);
	inheritmt(__add);
	inheritmt(__sub);
	inheritmt(__mul);
	inheritmt(__div);
	inheritmt(__mod);
	inheritmt(__pow);
	inheritmt(__len);

	inheritmt(__eq);
	inheritmt(__lt);
	inheritmt(__le);
	inheritmt(__gc);

	inheritmt(__metatable);
	inheritmt(__mt);
#pragma endregion
	
	// Inherit SubClasses
	for (auto classPair : From->subClasses)
		subClasses[classPair.first] = classPair.second;

	// Inherit Fields
	for (auto fieldPair : From->fields)
		if (!fields.contains(fieldPair.first))
			fields[fieldPair.first] = fieldPair.second;
	
	inheritance.push_back(From);
}

LunaClass::LunaClass(lua_State* L, std::string Name, int _mtlock)
{
	closure_header();

	if (_mtlock == -2)
	{
		lua_pushstring(L, "This metatable is locked.");
		__metatable = lua_ref(L, -1);
		resetltop();
	}
	else
		__metatable = _mtlock;

	className = Name;
	inheritance = std::vector<LunaClass*>();
	subClasses = std::map<std::string, bool>();
	fields = std::map<std::string, BaseField*>();
	instances = std::map<unsigned int, int>();
	customFields = false;

	__index = default_index;
	__newindex = default_newindex;
	__tostring = default_tostring;
	__tonumber = default_tonumber;
	__typeof = default_typeof;
	__is = default_is;

	__concat = default_concat;
	__iter = default_iter;
	__call = default_call;
	__idiv = default_idiv;

	__unm = default_unm;
	__add = default_add;
	__sub = default_sub;
	__mul = default_mul;
	__div = default_div;
	__mod = default_mod;
	__pow = default_pow;
	__len = default_len;

	__eq = default_eq;
	__lt = default_lt;
	__le = default_le;
	__gc = default_gc;

	lua_newtable(L);
	__mt = lua_ref(L, -1);

	resetltop();
}

#define setmt(mt) if (mt) {  lua_pushstring(L, #mt); lua_pushcclosure(L, mt, #mt, 0); lua_settable(L, -3); }
void LunaClass::Finalize(lua_State* L)
{
	closure_header();

	lua_getref(L, __mt);
	
	setmt(__index);
	setmt(__newindex);
	setmt(__tostring);
	setmt(__tonumber);
	setmt(__typeof);
	setmt(__is);

	setmt(__concat);
	setmt(__iter);
	setmt(__call);
	setmt(__idiv);

	setmt(__unm);
	setmt(__add);
	setmt(__sub);
	setmt(__mul);
	setmt(__div);
	setmt(__mod);
	setmt(__pow);
	setmt(__len);

	setmt(__eq);
	setmt(__lt);
	setmt(__le);
	setmt(__gc);

	lua_pushstring(L, "__metatable");
	lua_getref(L, __metatable);
	lua_settable(L, -3);

	resetltop();
}

std::map<std::string, LunaClass*> Classes::InitiatedClasses = std::map<std::string, LunaClass*>();
void Luna::Lib::Class::openDynamic(lua_State* L)
{
	closure_header();

	Classes::initLawnApp(L);

	resetltop();
}

void LunaInstance::Revive() { _alive = true; }
bool LunaInstance::IsAlive() { return _alive; }
void LunaInstance::Destroy(lua_State* L)
{
	iClass->instances.erase(iData);
	lua_unref(L, iExtraFields);
	_alive = false;
}