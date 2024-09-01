#pragma once
#include "Extension.hpp"

/* Luna Class
* 
* Convenient tool to wrap C++ classes into lua compatible proxies.
* Version 3.0
* - 0xVB
* 
* Base.hpp: Contains all the basic definitions & some forward definitions
* Extension.hpp: Contains template definitions
*/

namespace Luna::Lib::Class::Classes
{
	extern std::map<std::string, LunaClass*> InitiatedClasses;

	// Classes
	void initLawnApp(lua_State* L);
}

#define ImportLunaField(BaseClass, mField, Field, ReadOnly) self->AddField(new OffsetField<decltype(BaseClass::mField)>(Field, ReadOnly, offsetof(BaseClass, mField)))