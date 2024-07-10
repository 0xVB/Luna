#pragma once

#include <memory>
#include <vector>
#include "Luna/Lua/LunaScript.hpp"
#include "Luna/Lua/LunaModule.hpp"

namespace Luna {
    class ModData {
        public:
        virtual LunaScriptPtr getMainScript() = 0;
        virtual std::vector<LunaModulePtr> getModules() = 0;
    };
    typedef std::shared_ptr<ModData> ModDataPtr;
}