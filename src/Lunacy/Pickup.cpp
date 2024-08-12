#pragma once
#include "Lunacy/LawnApp.h"
#include "Lunacy/Pickup.h"

CONST DWORD UPDATE = 0x431500;
__declspec(naked) void Pickup::Update()
{
	__asm
	{
		mov eax, ecx
		jmp UPDATE
	}
}

CONST DWORD DRAW = 0x431810;
__declspec(naked) void Pickup::Draw(Sexy::Graphics*)
{
	__asm
	{
		pop eax// Ret
		push ecx
		push eax
		jmp DRAW
	}
}

Pickup::Pickup(PickupType T)
{
	mApp = LawnApp::GetApp();
	mLawn = mApp->mLawn;
	mRow = 0;
	mRenderOrder = 400000;
	mVisible = true;
	mDisappearCounter = 1000;
	mType = T;
}

CONST DWORD DIE = 0x432DD0;
__declspec(naked) void Pickup::Die()
{
	__asm
	{
		push esi
		mov esi, ecx
		call DIE
		pop esi
		ret
	}
}

CONST DWORD COLLECT = 0x432060;
__declspec(naked) void Pickup::Collect()
{
	__asm
	{
		jmp COLLECT
	}
}