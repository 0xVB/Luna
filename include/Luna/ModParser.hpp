#pragma once

#include "ModInfo.hpp"

namespace Luna {
    class ModParser {
        public:
        static ModInfo parse(std::string path);
    };
}