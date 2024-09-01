#include "Luna/Lua/Lib/Class/LunaClass.hpp"
#include "Lunacy/LawnApp.h"

using namespace Luna::Lib::Class;

void Classes::initLawnApp(lua_State* L)
{
	auto lua_LawnApp = new LunaClass(L, "LawnApp");
	InitiatedClasses["LawnApp"] = lua_LawnApp;
	auto self = lua_LawnApp;

	ImportLunaField(LawnApp, mRandSeed, "RandSeed", false);
	ImportLunaField(LawnApp, mFrameTime, "FrameTime", false);
	ImportLunaField(LawnApp, mCompanyName, "CompanyName", false);
	ImportLunaField(LawnApp, mFullCompanyName, "FullCompanyName", false);
	ImportLunaField(LawnApp, mProdName, "ProductName", false);
	ImportLunaField(LawnApp, mTitle, "Title", false);
	ImportLunaField(LawnApp, mRegKey, "RegKey", false);
	ImportLunaField(LawnApp, mChangeDirTo, "ChangeDirTo", false);

	ImportLunaField(LawnApp, mWidth, "Width", false);
	ImportLunaField(LawnApp, mHeight, "Height", false);

	// Field Routing
	self->fields["ProdName"] = self->fields["ProductName"];
	self->fields["WindowTitle"] = self->fields["Title"];
	self->fields["RegisteryKey"] = self->fields["RegKey"];

	lua_LawnApp->Finalize(L);
	lua_LawnApp->NewInstance(L, *(void**)0x6A9EC0);
	lua_setglobal(L, "App");
}