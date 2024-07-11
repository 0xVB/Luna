#pragma once

#include "ModParserInterface.hpp"


namespace Luna {
    class FolderModParser : public ModParserInterface {
        public:
        FolderModParser(std::filesystem::path path) : ModParserInterface(path) {};

        static bool isMod(std::filesystem::path path);
        ModInfoPtr parseInfo() override;
        ModDataPtr parseModData() override;
    };
}