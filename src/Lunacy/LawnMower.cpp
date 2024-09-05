#include "Lunacy/LawnMower.h"

LawnMower::LawnMower(int Lane)
{
	Init(Lane);
}

__declspec(naked) void LawnMower::Init(int)
{
	__asm
	{
		pop edx// Ret
		pop eax// Lane
		push ecx
		push edx
		mov ecx, 0x458000
		jmp ecx
	}
}

__declspec(naked) void LawnMower::Update()
{
	__asm
	{
		pop eax// Ret
		push ecx
		push eax
		mov ecx, 0x4586E0
		jmp ecx
	}
}

__declspec(naked) void LawnMower::UpdatePoolCleaner()
{
	__asm
	{
		push edi
		mov edi, ecx
		mov ecx, 0x4581E0
		call ecx
		pop edi
		ret
	}
}

__declspec(naked) void LawnMower::Draw(Sexy::Graphics*)
{
	__asm
	{
		mov edx, ecx// this*
		pop eax// Ret
		pop ecx// G
		push eax// Ret
		mov eax, 0x458A80
		jmp eax
	}
}

__declspec(naked) void LawnMower::Die()
{
	__asm
	{
		mov eax, ecx// this*
		mov ecx, 0x458D10
		jmp eax
	}
}

__declspec(naked) void LawnMower::MowZombie(Zombie*)
{
	__asm
	{
		mov eax, ecx// this*
		mov ecx, 0x458540
		jmp ecx
	}
}

__declspec(naked) void LawnMower::StartMower()
{
	__asm
	{
		push esi
		mov esi, ecx
		mov ecx, 0x458DA0
		call ecx
		pop esi
		ret
	}
}

__declspec(naked) void LawnMower::SquishMower()
{
	__asm
	{
		mov eax, 0x458EB0
		jmp eax
	}
}

__declspec(naked) void LawnMower::EnableSuperMower()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x458F60
		jmp ecx
	}
}

LawnMower* TryToGet(LawnMowerID ID)
{
	return LawnApp::GetApp()->mLawn->mLawnMowers.Fetch(ID);
}