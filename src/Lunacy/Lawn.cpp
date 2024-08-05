#include "Lunacy/CGeometry.h"
#include "Lunacy/Lawn.h"

CONST DWORD ADDLADDER = 0x408F40;
__declspec(naked) GridItem* Lawn::AddLadder(int, int)
{
	__asm
	{
		push edi

		mov eax, ecx
		mov edi, [esp + 0xC]
		push [esp + 0x8]
		call ADDLADDER
		pop edi
		ret 0x8
	}
}

CONST DWORD ADDCRATER = 0x408F80;
__declspec(naked) GridItem* Lawn::AddCrater(int, int)
{
	__asm
	{
		push edi

		mov eax, ecx
		mov edi, [esp + 0xC]
		push[esp + 0x8]
		call ADDCRATER
		pop edi
		ret 0x8
	}
}

CONST DWORD COUNTGRAVES = 0x412850;
__declspec(naked) int Lawn::CountGraves()
{
	__asm
	{
		mov edx, ecx
		call COUNTGRAVES
		ret
	}
}

CONST DWORD SPAWNZOMBIESGRAVE = 0x412CE0;
CONST DWORD SPAWNZOMBIESPOOL = 0x4128F0;
CONST DWORD SPAWNZOMBIESSKY = 0x412C30;

__declspec(naked) void Lawn::SpawnZombiesFromGrave()
{
	__asm
	{
		push edi
		mov edi, ecx
		call SPAWNZOMBIESGRAVE
		pop edi
		ret
	}
}
__declspec(naked) void Lawn::SpawnZombiesFromPool()
{
	__asm
	{
		push ecx
		jmp SPAWNZOMBIESPOOL
	}
}
__declspec(naked) void Lawn::SpawnZombiesFromSky()
{
	__asm
	{
		push ebx
		mov ebx, ecx
		call SpawnZombiesFromSky
		pop ebx
		ret
	}
}

CONST DWORD NEWPLANT = 0x40CE20;
__declspec(naked) Plant* Lawn::NewPlant(int, int, SeedType, SeedType)
{
	__asm
	{
		mov eax, ecx
		jmp NEWPLANT
	}
}

CONST DWORD PLANTEFFECTS = 0x40CE60;
__declspec(naked) void Lawn::DoPlantingEffects(int, int, Plant*)
{
	__asm
	{
		mov edx, ecx
		mov ecx, [esp + 0x4]
		mov eax, [esp + 0x8]
		push [esp + 0xC]
		call PLANTEFFECTS
		ret 0xC
	}
}

CONST DWORD NEWPROJ = 0x40D620;
__declspec(naked) Projectile* Lawn::NewProjectile(int, int, int, int, ProjectileType)
{
	__asm
	{
		mov eax, ecx
		jmp NEWPROJ
	}
}

CONST DWORD PPTGX = 0x41C2D0;
CONST DWORD PPTGY = 0x41C320;
CONST DWORD PTGX = 0x41C4C0;
CONST DWORD PTGY = 0x41C550;
CONST DWORD GTPX = 0x41C680;
CONST DWORD GTPY = 0x41C740;
__declspec(naked) int Lawn::PlantingPixelToGridX(SeedType, int, int)
{
	__asm
	{
		mov eax, [esp + 0x4]
		mov edx, [esp + 0xC]
		push [esp + 0x8]
		call PPTGX
		ret 0xC
	}
}
__declspec(naked) int Lawn::PlantingPixelToGridY(SeedType, int, int)
{
	__asm
	{
		push esi

		mov eax, [esp + 0x8]
		push [esp + 0x10]
		push [esp + 0x10]
		mov esi, ecx
		call PPTGY
		pop esi
		ret 0xC
	}
}
__declspec(naked) int Lawn::PixelToGridX(int, int)
{
	__asm
	{
		push edi
		mov eax, [esp + 0x8]
		mov edi, [esp + 0xC]
		call PTGX
		pop edi
		ret 0x8
	}
}
__declspec(naked) int Lawn::PixelToGridY(int, int)
{
	__asm
	{
		mov edx, ecx
		mov eax, [esp + 0x4]
		mov ecx, [esp + 0x8]
		call PTGY
		ret 0x8
	}
}
__declspec(naked) int Lawn::GridToPixelX(int, int)
{
	__asm
	{
		push esi
		mov eax, [esp + 0x8]
		mov esi, [esp + 0xC]
		call GTPX
		pop esi
		ret 0x8
	}
}
int __declspec(naked) Lawn::GridToPixelY(int, int)
{
	__asm
	{
		push ebx
		mov ebx, ecx
		mov ecx, [esp + 0x8]
		mov eax, [esp + 0xC]
		call GTPY
		pop ebx
		ret 0x8
	}
}

using Sexy::Vector2;
IVector2 Lawn::PlantingPixelToGrid(SeedType T, int X, int Y)
{
	return IVector2(
		PlantingPixelToGridX(T, X, Y),
		PlantingPixelToGridX(T, X, Y)
	);
}
IVector2 Lawn::PixelToGrid(int X, int Y)
{
	return IVector2(
		PixelToGridX(X, Y),
		PixelToGridY(X, Y)
	);
}
IVector2 Lawn::GridToPixel(int C, int L)
{
	return IVector2(
		GridToPixelX(C, L),
		GridToPixelY(C, L)
	);
}