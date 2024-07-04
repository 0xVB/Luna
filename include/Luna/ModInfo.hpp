#pragma once
#include <string>

namespace Luna {
    class ModInfo {
        public:
        std::string name;
        std::string icon; // url or path
        struct ModVersion {
            int major;
            int minor;
            int patch;
        } version;
        std::string author;
        std::string description;
    };
}