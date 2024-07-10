#pragma once

#include <memory>
#include <string>


namespace Luna {
    class ModInfo;
    class LunaScript {
    public:
        LunaScript();
        ~LunaScript();
    private:
        std::string _name;
        std::string _bytecode; // TODO: change this with ProtectedSource object
        std::shared_ptr<ModInfo> _modInfo;
    };
    typedef std::shared_ptr<LunaScript> LunaScriptPtr;
}