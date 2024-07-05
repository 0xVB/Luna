#pragma once

#include "ModParserInterface.hpp"


namespace Luna {
    class FolderModParser : public ModParserInterface {
        public:
        FolderModParser() = default;

        ModInfo parse(std::string path) override;
        bool isMod(std::string path) override;
    };
}