#pragma once
#include "Lunacy/Plant.h"

CONST DWORD FIRE = 0x466E00;
__declspec(naked) void __thiscall Plant::Fire(Zombie*, int, bool)
{
    __asm
    {
        push [esp + 0x10] // PlantWeapon
        push [esp + 0x10] // Lane
        push [esp + 0x10] // Zombie
        push ecx // this
        call FIRE
        ret 0xC
    }
}

CONST DWORD SETSLEEPING = 0x45E860;
__declspec(naked) void __thiscall Plant::SetSleeping(bool)
{
    __asm
    {
        push [esp + 0x4]
        mov eax, ecx
        call SETSLEEPING
        ret 0x4
    }
}

CONST DWORD DIE = 0x4679B0;
__declspec(naked) void __thiscall Plant::Die()
{
    __asm
    {
        push ecx         // push 'this' pointer (Plant* this) onto the stack
        call DIE         // call the DIE function
        ret 0            // return, no stack cleanup needed since no additional parameters
    }
}

CONST DWORD MAKESUN = 0x45F980;
__declspec(naked) bool __thiscall Plant::MakeSun()
{
    __asm
    {
        mov eax, ecx
        call MAKESUN
        ret 0
    }
}

CONST DWORD PLAYBODYREANIM = 0x45FD90;
__declspec(naked) void __thiscall Plant::PlayBodyReanim(const char*, ReanimLoopType, int, float)
{
    __asm
    {
        push [esp + 0x10]
        mov eax, ecx
        mov ecx, [esp + 0x10]
        push [esp + 0x0C]
        push [esp + 0x0C]
        call PLAYBODYREANIM
        ret 0x10
    }
}