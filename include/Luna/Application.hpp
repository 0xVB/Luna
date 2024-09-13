#pragma once

#include "IO/ILogger.hpp"
#include "Luna/Hook/LunaHook.hpp"
#include "Mod/LocalModExplorer.hpp"
#include "Mod/ModHandler.hpp"
#include <memory>

namespace Luna
{
    extern LunaHookThread* gLunaThread;
    class Application {
    public:
        Application();
        virtual ~Application();

        std::shared_ptr<IO::ILogger> getLogger();

        static Application* getSingleton();
        static void __stdcall onLawnAppInitialized();
        static void __stdcall onGameUpdate();
        bool initialize();

        std::vector<ModParserPtr> getLoadedMods();
    private:
        std::shared_ptr<ModHandler> modHandler;
        std::shared_ptr<ModExplorer> localModExplorer;
        std::shared_ptr<IO::ILogger> logger;
    };
}