#include "Luna/Application.hpp"
#include "Luna/ScriptContext.hpp"
#include "Luna/IO/ConsoleLogger.hpp"
#include "Luna/IO/FileLogger.hpp"
#include "Luna/Job/TaskScheduler.hpp"
#include "Lunacy/Lunacy.hpp"
#include <MinHook.h>

#define SEXY_FILE_EXISTS (LPVOID)0x5B0820
#define GAME_UPDATE (LPVOID)0x539140

using namespace Luna;

Application::Application()
{
    #ifdef _DEBUG
    logger = std::make_shared<IO::ConsoleLogger>();
    #else
    logger = std::make_shared<IO::FileLogger>("luna.log");
    #endif
    localModExplorer = std::make_shared<LocalModExplorer>("mods");
    modHandler = std::make_shared<ModHandler>();
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


typedef bool (__cdecl* SexyFileExistsCC)(void*);
SexyFileExistsCC sexyFileExists = nullptr;

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
    const auto sc = ScriptContext::getSingleton();
    if (!sc->initialize()) {
        logger->log(LogLevel::error, "Failed to initialize ScriptContext");
        return false;
    }
    logger->log(LogLevel::info, "Luna global state %p", sc->getGlobalState());
    
    TaskScheduler::getSingleton()->initialize();

    modHandler->addMods(localModExplorer->getMods());

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


typedef bool (* gameUpdateCC)(void*);
gameUpdateCC gameUpdate = nullptr;

bool __declspec(naked) onUpdateHook(void* sexyWidgetManager) {
    __asm {
        call Application::onGameUpdate;
        jmp[gameUpdate];
    }
}

void Application::onLawnAppInitialized() {
    const auto app = Application::getSingleton();
    app->getLogger()->log(LogLevel::info, "Lawn application initialized %p", LawnApp::GetApp());
    if (MH_CreateHook(GAME_UPDATE, onUpdateHook, (LPVOID*)&gameUpdate) != MH_OK) {
        app->getLogger()->log(LogLevel::error, "Failed to create game update hook");
        return;
    }
    if (MH_EnableHook(GAME_UPDATE) != MH_OK) {
        app->getLogger()->log(LogLevel::error, "Failed to enable game update hook");
    }
}

void Application::onGameUpdate() {
    //const auto app = getSingleton();
    TaskScheduler::getSingleton()->update();
}

std::vector<ModParserPtr> Application::getLoadedMods()
{
    return modHandler->getMods();
}