#pragma once

#include "ModInfo.hpp"
#include <filesystem>

namespace Luna {
    class ModParserInterface {
        protected:
        std::filesystem::path path;
        public:
        ModParserInterface(std::filesystem::path path) : path(path) {};
        virtual ModInfoPtr parse() = 0;
    };
}