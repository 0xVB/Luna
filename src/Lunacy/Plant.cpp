#pragma once
#include "Lunacy/CGeometry.h"
#include "Lunacy/Plant.h"
#include "Lunacy/Lawn.h"

CONST DWORD UPDATE = 0x463E40;
__declspec(naked) void Plant::Update()
{
    __asm
    {
        mov eax, ecx
        jmp UPDATE
    }
}

CONST DWORD DRAW = 0x465A90;
__declspec(naked) void Plant::Draw(Sexy::Graphics*)
{
    __asm
    {
        pop edx// Ret
        push ecx
        push edx
        jmp DRAW
    }
}

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

CONST DWORD PLANTINIT = 0x45DB60;
__declspec(naked) void Plant::Initialize(int, int, SeedType, SeedType)
{
    __asm
    {
        push [esp + 0x10]
        push [esp + 0x10]
        push ecx
        mov eax, [esp + 0x14]
        mov ecx, [esp + 0x10]
        call PLANTINIT
        ret 0x10
    }
}

CONST DWORD RENDORD = 0x45E7C0;
__declspec(naked) int Plant::GetRenderOrder()
{
    __asm
    {
        push esi
        mov esi, ecx
        call RENDORD
        pop esi
        ret
    }
}

CONST DWORD ATTACH = 0x45EEA0;
__declspec(naked) ParticleSystem* Plant::AttachParticle(int, int, int, ParticleEffect)
{
    __asm
    {
        push edi
        mov edi, ecx
        push [esp + 0x14]
        push [esp + 0x14]
        push [esp + 0x14]
        push [esp + 0x14]
        call ATTACH
        pop edi
        ret 0x10
    }
}

CONST DWORD REMEFF = 0x4629F0;
__declspec(naked) void Plant::RemoveEffects()
{
    __asm
    {
        push esi
        mov esi, ecx
        call REMEFF
        pop esi
        ret
    }
}

CONST DWORD SQUISH = 0x462B80;
__declspec(naked) void Plant::Squish()
{
    __asm
    {
        push ecx
        call SQUISH
        ret
    }
}

CONST DWORD DSHADOW = 0x465680;
__declspec(naked) void Plant::DrawShadow(Sexy::Graphics*, float, float)
{
    __asm
    {
        mov eax, ecx
        jmp DSHADOW
    }
}

CONST DWORD FINDTARGET = 0x4675C0;
__declspec(naked) Zombie* Plant::FindTargetZombie(int, bool)
{
    __asm
    {
        push ecx
        push [esp + 0x8]
        mov ecx, [esp + 0x10]
        call FINDTARGET
        ret 0x8
    }
}

void Plant::Initialize()
{
    Initialize(mColumn, mRow, mType, mImitaterType);
}

Zombie* Plant::FindTargetZombie(bool A)
{
    return FindTargetZombie(mRow, A);
}

void Plant::DoPlantingEffects()
{
    mLawn->DoPlantingEffects(mColumn, mRow, this);
}

Plant::Plant(SeedType Type)
{
    ConstructGameObject();
    mVisible = true;
    mRenderOrder = 400000;
    mTicksPerFrame = 10;
    mType = Type;
}

Plant::MagnetItem::MagnetItem(MagnetItemType Type)
{
    mItemType = Type;
    mX = 0;
    mY = 0;
    mDestOffsetX = 0;
    mDestOffsetY = 0;
}

CONST DWORD ISNOCT = 0x467E60;
CONST DWORD ISAQUA = 0x467EA0;
CONST DWORD ISUPGD = 0x467EC0;
__declspec(naked) bool __stdcall Plant::IsNocturnal(SeedType)
{
    __asm
    {
        pop edx// Ret
        pop eax
        push edx

        jmp ISNOCT
    }
}
__declspec(naked) bool __stdcall Plant::IsAquatic(SeedType)
{
    __asm
    {
        pop edx// Ret
        pop eax
        push edx

        jmp ISAQUA
    }
}
__declspec(naked) bool __stdcall Plant::IsUpgrade(SeedType)
{
    __asm
    {
        pop edx// Ret
        pop eax
        push edx

        jmp ISUPGD
    }
}