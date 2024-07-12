#pragma once

#include <vector>
#include <filesystem>
#include "ModInfo.hpp"
#include "ModParserInterface.hpp"

namespace Luna {
    class ModHandler {
        private:
        std::vector<ModParserPtr> mods;

        public:
        ModHandler() = default;

        void addMod(ModParserPtr mod);
        void removeMod(ModParserPtr mod);
        void addMods(std::vector<ModParserPtr> mods);

        std::vector<ModParserPtr> getMods();

    };
}