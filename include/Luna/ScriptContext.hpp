#pragma once

#include <lua.h>
#include <lualib.h>
#include "Lua/LunaScript.hpp"

namespace Luna {
    class ScriptContext {
    public:
        ScriptContext() = default;

        static ScriptContext* getSingleton();
        bool initialize();

        inline lua_State* getGlobalState() { return _gL; }

        int startScript(LunaScriptPtr script);
    private:
        // global lua state
        lua_State* _gL;
    };
}