#include "Luna/Lua/ScriptContext.hpp"
#include "Luna/Lua/StateUserdata.hpp"
#include <mutex>

using namespace Luna::Lua;

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
    return true;
}

static std::mutex singleMtx;
ScriptContext* ScriptContext::getSingleton() {
    std::lock_guard<std::mutex> lock(singleMtx);
    static ScriptContext* sc = nullptr;
    if (sc == nullptr) sc = new ScriptContext();
    return sc;
}

int ScriptContext::startScript(LunaScriptPtr script)
{
   return LUA_OK;
}