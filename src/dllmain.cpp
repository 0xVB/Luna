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
    Application app = Application();

    try {
        if (!app.initialize()) {
            return FALSE;
        }
    }
    catch (const std::exception& e) {
        // TODO: Exception Handler & Logger
        std::cerr << e.what() << std::endl;
        return FALSE;
    };

    app.getLogger()->log(Luna::IO::LogLevel::info, "What is VB doing under Uniq desk?");

    auto pvzApp = LawnApp::GetApp();
    pvzApp->mEasyPlantingCheat = true;

    using namespace Sexy;
    IVector2 I = IVector2();
    FRect F = I;

    return TRUE;
}