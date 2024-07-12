#pragma once

#include "ModInfo.hpp"
#include "Luna/Lua/LunaScript.hpp"
#include "Luna/Lua/LunaModule.hpp"
#include <filesystem>

namespace Luna {
    class ModParserInterface {
        protected:
        std::filesystem::path path;
        public:
        ModParserInterface(std::filesystem::path path) : path(path) {};
        ModInfoPtr getInfo();
        LunaScriptPtr getMainScript();
        private:
        virtual ModInfoPtr parseInfo() = 0;
        virtual LunaScriptPtr parseMainScript() = 0;
    };
    typedef std::shared_ptr<ModParserInterface> ModParserPtr;
}