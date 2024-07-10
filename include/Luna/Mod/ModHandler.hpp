#pragma once

#include <vector>
#include <filesystem>
#include "ModInfo.hpp"

namespace Luna {
    class ModHandler {
        private:
        std::vector<ModInfoPtr> mods;

        public:
        ModHandler() = default;

        void addMod(ModInfoPtr mod);
        void removeMod(ModInfoPtr mod);
        void addMods(std::vector<ModInfoPtr> mods);

        std::vector<ModInfoPtr> getMods();

    };
}