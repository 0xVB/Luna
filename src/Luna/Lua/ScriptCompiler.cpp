#include "Luna/Lua/ScriptCompiler.hpp"
#include <Luau/Compiler.h>

using namespace Luna;

ProtectedSource ScriptCompiler::compileScript(std::string script) {
    // TODO: encode & compress bytecode
    return ProtectedSource(Luau::compile(script, {}));
}