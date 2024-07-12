#pragma once

#include <memory>
#include <string>
#include "ProtectedSource.hpp"

namespace Luna {
    class ModParserInterface;
    class LunaScript {
    public:
        LunaScript(std::shared_ptr<ModParserInterface> mod, ProtectedSource source) : _mod(mod), _source(source) {};
        inline std::shared_ptr<ModParserInterface> getMod() { return _mod; }
        inline ProtectedSource getSource() { return _source; }
    private:
        std::string _name;
        ProtectedSource _source;
        std::shared_ptr<ModParserInterface> _mod;
    };
    typedef std::shared_ptr<LunaScript> LunaScriptPtr;
}