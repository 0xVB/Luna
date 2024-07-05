#pragma once

#include "Luna/ModInfo.hpp"
#include <string>



namespace Luna::Lua {
    class LunaScript {
    public:
        LunaScript();
        ~LunaScript();
    private:
        std::string _name;
        std::string _bytecode; // TODO: change this with ProtectedSource object
        ModInfoPtr _modInfo;
    };
    typedef std::shared_ptr<LunaScript> LunaScriptPtr;
}