#pragma once

#include "ModParserInterface.hpp"
#include <filesystem>
#include <memory>

namespace Luna {
    class ModParserDetector {
    public:
        static std::shared_ptr<ModParserInterface> detect(std::filesystem::path path);
    };
}