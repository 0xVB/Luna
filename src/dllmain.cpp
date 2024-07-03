#include "Luna/Luna.h"
#include "Luna/Application.hpp"
#include "Lunacy/Lunacy.hpp"

using Luna::Application;

BOOL APIENTRY DllMain(
    HMODULE ModuleHandle,
    DWORD  CallReason,
    LPVOID Reserved
)
{
    if (CallReason != DLL_PROCESS_ATTACH)
        return TRUE;

    Application app = Application();
    try {
        if (!app.initialize()) return FALSE;
    }
    catch (const std::exception& e) {
        // TODO: Exception Handler & Logger
        std::cerr << e.what() << std::endl;
        return FALSE;
    };

    app.getLogger()->log(LogLevel::none, "Luna %s has been initialized.", LUNA_VERSION);

    /*auto pvzApp = LawnApp::GetApp();
    pvzApp->mEasyPlantingCheat = true;

    using namespace Sexy;
    IVector2 I = IVector2();
    FRect F = I;
    */

    return TRUE;
}