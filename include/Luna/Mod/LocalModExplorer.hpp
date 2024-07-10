#pragma once

#include "ModExplorer.hpp"
#include <filesystem>
#include <vector>

namespace Luna {
    class LocalModExplorer : public ModExplorer {
        public:
        LocalModExplorer(std::filesystem::path modsPath);

        std::vector<ModInfoPtr> getMods() override;
        private:
        std::filesystem::path modsPath;
    };
}