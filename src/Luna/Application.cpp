#include "Luna/Application.hpp"
#include "Luna/IO/ConsoleLogger.hpp"
#include "Luna/IO/FileLogger.hpp"
#include "Luna/Lua/ScriptContext.hpp"
#include <MinHook.h>
#include "Lunacy/LawnApp.h"

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

Application* Application::getSingleton()
{
    static Application app;
    return &app;
}

#define SEXY_FILE_EXISTS (LPVOID)0x5B0820
typedef bool (__cdecl* SexyFileExistsCC)(void*);
SexyFileExistsCC sexyFileExists;

bool __cdecl sexyFileExistsHook(void* base) {
    auto res = sexyFileExists(base);
    MH_RemoveHook(SEXY_FILE_EXISTS);
    Application::onLawnAppInitialized();
    return res;
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

    if (!LawnApp::GetApp()) {
        if (MH_CreateHook(SEXY_FILE_EXISTS, sexyFileExistsHook, (LPVOID*)&sexyFileExists) != MH_OK) {
            logger->log(LogLevel::error, "Failed to create LawnApp hook");
            return false;
        }
        if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
            logger->log(LogLevel::error, "Failed to enable LawnApp hook");
            return false;
        }
    } 
    else
        // In this scenario LawnApp is already initialized probably due to luna begin bootstrapped in a non standard way
        onLawnAppInitialized();
    

    return true;
}


void Application::onLawnAppInitialized()
{
    const auto app = Application::getSingleton();
    app->getLogger()->log(LogLevel::info, "Lawn application initialized %p", LawnApp::GetApp());
}