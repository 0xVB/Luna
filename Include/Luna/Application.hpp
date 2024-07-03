#pragma once

#include "IO/ILogger.hpp"
#include "ModExplorer.hpp"
#include <memory>

namespace Luna
{
    class Application {
    public:
        Application();
        virtual ~Application();

        std::shared_ptr<IO::ILogger> getLogger();

        bool initialize();
    private:
        std::shared_ptr<IO::ILogger> logger;
        std::shared_ptr<ModExplorer> localModExplorer;
    };
}