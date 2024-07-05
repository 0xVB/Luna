#pragma once

namespace Luna::Lua {
    enum ScriptIdentity {
        core,   // high api permission level
        mod,    // medium api permission level
        util    // low api permission level
    };
}