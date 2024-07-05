#pragma once

#include "ModInfo.hpp"

namespace Luna {
    class ModParserInterface {
        public:
        virtual bool isMod(std::string path) = 0;
        virtual ModInfo parse(std::string path) = 0;
    };
}