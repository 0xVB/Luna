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

    using namespace Sexy;
    IVector2 I = IVector2();
    FRect F = I;

    return TRUE;
}