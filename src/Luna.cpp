#include "Luna.h"
#include "Lunacy.hpp"

BOOL APIENTRY DllMain(
    HMODULE ModuleHandle,
    DWORD  CallReason,
    LPVOID Reserved
)
{
    auto App = LawnApp::GetApp();
    App->mEasyPlantingCheat = true;
    return TRUE;
}