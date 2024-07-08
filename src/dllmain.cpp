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

    const auto app = Application::getSingleton();
    if (!app->initialize()) return FALSE;

    app->getLogger()->log(LogLevel::none, "Luna %s has been initialized.", LUNA_VERSION);
    
    return TRUE;
}