#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>

#include "Luna/Application.hpp"
#include "Lunacy/Lunacy.hpp"

#include "lua.h"
#include "lualib.h"
#include "Luau/Compiler.h"
#define LUNA_STATE Luna::gLuaState

namespace Luna
{
	class LunaMod;

	extern bool debugMode;
	extern lua_State* gLuaState;
	extern LawnApp* gApp;
	extern Luau::CompileOptions compileOptions;
	extern std::vector<LunaMod*> gLoadedMods;

	class LunaMod
	{
	public:
		std::string modName;
		std::string modDesc;
		std::string modAuthor;
		Sexy::DDImage* modIcon;

		std::string GetVersionString();
		std::string GetProperty();
		bool IsCompiled();

		static LunaMod* LoadLuna(std::filesystem::path ModFolder);
		static LunaMod* LoadLunacy(std::filesystem::path CompiledMod);

	private:
		LunaMod();
		unsigned char majorVer;
		unsigned char minorVer;
		unsigned char patchVer;
		bool isCompiled;

		lua_State* modState;
		const char* modChunk;

		std::map<std::string, std::string> modProperties;
	};

	// Setup gLuaState and, add API functions
	void InitiateLunaState();
	// Setup compileOptions
	void InitializeCompileOptions();

	void LoadScript(lua_State*, std::filesystem::path ScriptPath);
	void LoadLuna(lua_State*, std::filesystem::path LunaPath);
	void LoadMods();

	void DebugMain();


	bool LoadFile(lua_State*, std::filesystem::path ModPath);
	void Setup(bool debugMode = false);
}