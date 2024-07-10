#pragma once
#include <string>
#include <memory>
#include "ModData.hpp"

namespace Luna {
    class ModInfo {
        private:
        std::string _source; // url or path
        std::string _name;
        std::string _iconUrl; // url or path
        struct ModVersion {
            int major;
            int minor;
            int patch;
        } _version;
        std::string _author;
        std::string _description;
        public:
        ModInfo(std::string source) : _source(source) {};
        inline std::string getName() { return _name; }
        inline void setName(std::string name) { this->_name = name; }        
        inline std::string get_iconUrl() { return _iconUrl; }
        inline void set_iconUrl(std::string _iconUrl) { this->_iconUrl = _iconUrl; }
        inline ModVersion get_version() { return _version; }
        inline void set_version(int major, int minor, int patch) { _version.major = major; _version.minor = minor; _version.patch = patch; }
        inline std::string get_author() { return _author; }
        inline void set_author(std::string _author) { this->_author = _author; }
        inline std::string get_description() { return _description; }
        inline void set_description(std::string _description) { this->_description = _description; }
        // TODO: must return the ModSource object (it can be a RemoteMod or LocalMod object, both inheriting from ModSource)
        virtual ModDataPtr getModData() = 0; 
    };
    typedef std::shared_ptr<ModInfo> ModInfoPtr;
}