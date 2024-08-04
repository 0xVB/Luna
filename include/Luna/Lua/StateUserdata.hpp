#pragma once
#include "ScriptIdentity.hpp"
#include "Luna/Mod/ModParserInterface.hpp"

namespace Luna {
    class StateUserdata {
    public:
        StateUserdata(ScriptIdentity identity, ModParserPtr mod);
        ~StateUserdata();
        ScriptIdentity getIdentity() { return _identity; }
        ModParserPtr getMod() { return _mod; }
    private:
        ScriptIdentity _identity;
        ModParserPtr _mod;
    };
}