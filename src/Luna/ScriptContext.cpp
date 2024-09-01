#include "Luna/ScriptContext.hpp"
#include "Luna/Lua/StateUserdata.hpp"
#include "Luna/Lua/StateUserdata.hpp"
#include "Luna/TaskScheduler.hpp"
#include "Luna/Application.hpp"

#include "Luna/Lua/Lib/LunaIO.hpp"
#include "Luna/Lua/Lib/Class/LunaClass.hpp"

using namespace Luna;

static void* l_alloc(void* ud, void* ptr, size_t osize, size_t nsize)
{
    (void)ud;
    (void)osize;
    if (nsize == 0)
    {
        free(ptr);
        return NULL;
    }
    else
        return realloc(ptr, nsize);
}

bool ScriptContext::initialize()
{
    _gL =  lua_newstate(l_alloc, NULL);
    if (_gL == nullptr) return false;
    openStatic(_gL);
    return true;
}

ScriptContext* ScriptContext::getSingleton() {
    static ScriptContext sc;
    return &sc;
}

#include <iostream>
int ScriptContext::startScript(LunaScriptPtr script)
{
    // make new thread with StateUserdata
    auto LT = lua_newthread(_gL);
    auto mod = script->getMod();
    lua_setthreaddata(LT, new StateUserdata(Luna::ScriptIdentity::MOD_ID, mod));

    // deserialize
    const auto chunkName = mod->getInfo()->getName() + "@main";
    auto bytecode = script->getBytecode().decompress();
    if (luau_load(LT, chunkName.c_str(), bytecode.data(), bytecode.size(), 0) != LUA_OK) {
        if (lua_isstring(LT, -1)) {
            const char* error = lua_tostring(LT, -1);
            Application::getSingleton()->getLogger()->log(LogLevel::error, "Error deserializing script: %s", error);
        }
        lua_close(LT);
        return LUA_ERRSYNTAX;
    }

    // open dynamic libs on thread
    openDynamic(LT);

    // run script
    auto state = lua_pcall(LT, 0, 0, 0);
    std::cout << "State: " << state << "\n";
    if (state == LUA_YIELD)
    {
        TaskScheduler::getSingleton()->registerJob(new Luna::BasicLuaJob(_gL, LT, chunkName.c_str()));
        Application::getSingleton()->getLogger()->log(LogLevel::info, "Scheduled.");
    }
    else if (state != LUA_OK) {
		if (lua_isstring(LT, -1)) {
			const char* error = lua_tostring(LT, -1);
			Application::getSingleton()->getLogger()->log(LogLevel::error, "Error running script: %s", error);
		}
		lua_close(LT);
		return LUA_ERRRUN;
	}
    
   return LUA_OK;
}

int lua_wait(lua_State* L)
{
    closure_header();
    int tdelta = LuaToNum(L, 1);
    tdelta = (tdelta <= 0) ? 1 : tdelta;

    while (tdelta > 0)
    {
        lua_yield(L, 0);
        tdelta--;
    }

    return 0;
}

void Luna::ScriptContext::openStatic(lua_State* L) {
    luaL_openlibs(L);
    Lib::IO::openStatic(L);

    lua_pushcclosure(L, lua_wait, "wait", 0);
    lua_setglobal(L, "wait");
}

void Luna::ScriptContext::openDynamic(lua_State* L) {
    Application::getSingleton()->getLogger()->log(LogLevel::info, "Loading Dynamic Libraries");
    Lib::Class::openDynamic(L);
}