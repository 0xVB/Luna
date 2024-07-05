#pragma once
#include <string>
#include <memory>

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

        // TODO: must return the ModSource object (it can be a RemoteMod or LocalMod object, both inheriting from ModSource)
        void getModSource(); 
    };
    typedef std::shared_ptr<ModInfo> ModInfoPtr;
}