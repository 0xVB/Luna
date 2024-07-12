#pragma once

#include <memory>
#include "ModParserInterface.hpp"

namespace Luna {
    class FolderModParser : public ModParserInterface, public std::enable_shared_from_this<FolderModParser> {
        public:
        FolderModParser(std::filesystem::path path) : ModParserInterface(path) {};

        static bool isMod(std::filesystem::path path);
        ModInfoPtr parseInfo() override;
        LunaScriptPtr parseMainScript() override;
    };
}