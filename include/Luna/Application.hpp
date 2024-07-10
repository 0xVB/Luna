#pragma once

#include "IO/ILogger.hpp"
#include "Mod/LocalModExplorer.hpp"
#include "Mod/ModHandler.hpp"
#include <memory>

namespace Luna
{
    class Application {
    public:
        Application();
        virtual ~Application();

        std::shared_ptr<IO::ILogger> getLogger();

        static Application* getSingleton();
        static void onLawnAppInitialized();
        static void onGameUpdate();
        bool initialize();

        std::vector<ModInfoPtr> getLoadedMods();
    private:
        std::shared_ptr<ModHandler> modHandler;
        std::shared_ptr<ModExplorer> localModExplorer;
        std::shared_ptr<IO::ILogger> logger;
    };
}