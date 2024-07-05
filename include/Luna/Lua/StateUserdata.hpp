#pragma once
#include "ScriptIdentity.hpp"
#include "Luna/ModInfo.hpp"

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