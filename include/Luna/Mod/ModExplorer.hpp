#pragma once

#include "ModParserInterface.hpp"
#include <vector>


namespace Luna {
    class ModExplorer {
        public: 
        ModExplorer() = default;

        virtual std::vector<ModParserPtr> getMods() = 0;
    };
}