#include "Luna/ScriptContext.hpp"
#include "Luna/Lua/StateUserdata.hpp"

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
    return true;
}

ScriptContext* ScriptContext::getSingleton() {
    static ScriptContext sc;
    return &sc;
}

int ScriptContext::startScript(LunaScriptPtr script)
{
    // TODO: get appropriate state based on script authority
    // TODO: make new thread with LunaUserdata
    // TODO: luau_load script
    
   return LUA_OK;
}