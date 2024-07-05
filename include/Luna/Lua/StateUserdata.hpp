#pragma once
#include "ScriptIdentity.hpp"
#include "Luna/Mod/ModInfo.hpp"

namespace Luna::Lua {
    class StateUserdata {
    public:
        StateUserdata();
        ~StateUserdata();
    private:
        ScriptIdentity identity;
        ModInfoPtr modInfo;
    };
}