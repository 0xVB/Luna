#pragma once

#include "IO/ILogger.hpp"
#include "Mod/LocalModExplorer.hpp"
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
        bool initialize();
    private:
        std::shared_ptr<IO::ILogger> logger;
        std::shared_ptr<ModExplorer> localModExplorer;
    };
}