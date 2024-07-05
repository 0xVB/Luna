#pragma once

#include "ModInfo.hpp"
#include <vector>


namespace Luna {
    class ModExplorer {
        public: 
        ModExplorer() = default;

        virtual std::vector<ModInfo> getMods() = 0;
    };
}