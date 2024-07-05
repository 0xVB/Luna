#include "Luna/Application.hpp"
#include <windows.h>
#include <iostream>

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
    return TRUE;
}