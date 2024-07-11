#pragma once

#include "ModInfo.hpp"
#include <filesystem>

namespace Luna {
    class ModParserInterface {
        protected:
        std::filesystem::path path;
        public:
        ModParserInterface(std::filesystem::path path) : path(path) {};
        ModInfoPtr getInfo();
        ModDataPtr getModData();
        private:
        virtual ModInfoPtr parseInfo() = 0;
        virtual ModDataPtr parseModData() = 0;
    };
    typedef std::shared_ptr<ModParserInterface> ModParserPtr;
}