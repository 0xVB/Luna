#pragma once

#include "ModInfo.hpp"

namespace Luna {
    class LocalModInfo : public ModInfo {
        public:
        LocalModInfo(std::string path) : ModInfo(path) {};
    };
    typedef std::shared_ptr<LocalModInfo> LocalModInfoPtr;
}