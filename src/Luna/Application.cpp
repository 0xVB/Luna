#include "Luna/Application.hpp"
#include "Luna/IO/ConsoleLogger.hpp"
#include "Luna/IO/FileLogger.hpp"
#include "Luna/LocalModExplorer.hpp"
#include "Luna/Lua/ScriptContext.hpp"
#include <MinHook.h>

using namespace Luna;


Application::Application()
{
    #ifdef _DEBUG
    logger = std::make_shared<IO::ConsoleLogger>();
    #else
    logger = std::make_shared<IO::FileLogger>("luna.log");
    #endif
    localModExplorer = std::make_shared<LocalModExplorer>("mods");
}

Application::~Application()
{
}

std::shared_ptr<IO::ILogger> Application::getLogger()
{
    return logger;
}

bool Application::initialize()
{
    if (MH_Initialize() != MH_OK) {
        logger->log(LogLevel::error, "Failed to initialize MinHook");
        return false;
    }
    const auto sc = Lua::ScriptContext::getSingleton();
    if (!sc->initialize()) {
        logger->log(LogLevel::error, "Failed to initialize ScriptContext");
        return false;
    }
    logger->log(LogLevel::info, "Luna global state %p", sc->getGlobalState());
    return true;
}
