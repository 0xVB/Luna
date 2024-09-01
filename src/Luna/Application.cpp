#include "Luna/Application.hpp"
#include "Luna/ScriptContext.hpp"
#include "Luna/IO/ConsoleLogger.hpp"
#include "Luna/IO/FileLogger.hpp"
#include "Luna/TaskScheduler.hpp"
#include "Luna/Hook/LunaHook.hpp"
#include "Lunacy/Lunacy.hpp"

CONST DWORD INIT_HOOK = 0x44E969;
CONST DWORD GAME_UPDATE = 0x539140;

using namespace Luna;

Application::Application()
{
    //#ifdef _DEBUG
    logger = std::make_shared<IO::ConsoleLogger>();
    //#else
    //logger = std::make_shared<IO::FileLogger>("luna.log");
    //#endif
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

// Call Application::onLawnAppInitialized(); on init

LunaHookThread* HookThread;
bool Application::initialize()
{
    HookThread = LunaHookThread::New();
    const auto sc = ScriptContext::getSingleton();
    if (!sc->initialize()) {
        logger->log(LogLevel::error, "Failed to initialize ScriptContext");
        return false;
    }
    logger->log(LogLevel::info, "Luna global state %p", sc->getGlobalState());
    
    TaskScheduler::getSingleton()->initialize();

    modHandler->addMods(localModExplorer->getMods());

    if (!LawnApp::GetApp()) {
        HookThread->NewFunction(INIT_HOOK)->Finalize(onLawnAppInitialized);
        getLogger()->log(LogLevel::info, "Luna bootstrapped properly.");
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

void __stdcall Application::onLawnAppInitialized() {
    const auto gApp = HookThread->GetRegister(HookThread->EAX);
    const auto app = Application::getSingleton();
    LawnApp::SetApp(gApp);
    HookThread->NewFunction(GAME_UPDATE)->Finalize(onGameUpdate);

    app->getLogger()->log(LogLevel::info, "Lawn application initialized %p", LawnApp::GetApp());
    TaskScheduler::getSingleton()->update();
}

void __stdcall Application::onGameUpdate() {
    TaskScheduler::getSingleton()->update();
}

std::vector<ModParserPtr> Application::getLoadedMods()
{
    return modHandler->getMods();
}