#pragma once

#include "ProtectedSource.hpp"

namespace Luna {
    class ScriptCompiler {
        public:
        static ProtectedSource compileScript(std::string script);
    };
}