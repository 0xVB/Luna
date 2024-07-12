#pragma once

#include "ModParserInterface.hpp"
#include <filesystem>
#include <memory>

namespace Luna {
    class ModParserDetector {
    public:
        static ModParserPtr detect(std::filesystem::path path);
    };
}