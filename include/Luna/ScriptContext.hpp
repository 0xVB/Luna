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

        // lib methods
        void openStatic(lua_State* L);
        void openDynamic(lua_State* L);
    private:
        // global lua state
        lua_State* _gL;
    };
}