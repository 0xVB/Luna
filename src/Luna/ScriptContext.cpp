#include "Luna/ScriptContext.hpp"
#include "Luna/Lua/StateUserdata.hpp"
#include "Luna/Lua/StateUserdata.hpp"
#include "Luna/TaskScheduler.hpp"
#include "Luna/Application.hpp"

#include "Luna/Lua/Lib/LunaIO.hpp"
#include "Luna/Lua/Lib/General.hpp"
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
    auto state = lua_resume(LT, nullptr, 0);
    if (state == LUA_YIELD)
    {
        int delay = LuaToNum(LT, -1);
        delay = (delay < 0) ? 0 : delay;
        TaskScheduler::getSingleton()->registerJob(new Luna::BasicLuaJob(_gL, LT, delay, chunkName.c_str()));
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

void Luna::ScriptContext::openStatic(lua_State* L) {
    closure_header();

    luaL_openlibs(L);
    Lib::IO::openStatic(L);
    Lib::General::openStatic(L);

    resetltop();
}

void Luna::ScriptContext::openDynamic(lua_State* L) {
    Application::getSingleton()->getLogger()->log(LogLevel::info, "Loading Dynamic Libraries");
    Lib::Class::openDynamic(L);
}