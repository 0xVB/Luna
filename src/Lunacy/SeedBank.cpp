#include "Lunacy/SeedBank.h"

SeedPacket::SeedPacket(SeedType Type, SeedType Imitater) : GameObject()
{
	mRefreshCounter = 0;
	mRefreshTime = 0;
	mIndex = 0;
	mOffsetX = 0;
	mPacketType = Type;
	mImitaterType = Imitater;
	mSlotMachineCountDown = 0;
	mSlotMachiningNextSeed = SEED_NONE;
	mSlotMachiningPosition = 0;
	mActive = false;
	mRefreshing = false;
	mTimesUsed = 0;
}

SeedBank::SeedBank() : GameObject()
{
	mNumPackets = 0;
	mCutSceneDarken = 0;
	mConveyorBeltCounter = 0;
}

#pragma region SeedPacket Functions
__declspec(naked) void SeedPacket::PickNextSlotMachineSeed()
{
	__asm
	{
		pop eax
		push ecx
		pop eax
		mov ecx, 0x487070
		jmp ecx
	}
}
__declspec(naked) void SeedPacket::FlashIfReady()
{
	__asm
	{
		push esi
		mov esi, ecx
		mov ecx, 0x487190
		call ecx
		pop esi
		ret
	}
}
__declspec(naked) void SeedPacket::Update()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x487250
		jmp ecx
	}
}
__declspec(naked) void SeedPacket::Draw(Sexy::Graphics*)
{
	__asm
	{
		pop eax
		push ecx
		push eax
		mov ecx, 0x488220
		jmp ecx
	}
}
__declspec(naked) bool SeedPacket::CanPickUp()
{
	__asm
	{
		push esi
		mov esi, ecx
		mov ecx, 0x488500
		call ecx
		pop esi
		ret
	}
}
__declspec(naked) void SeedPacket::MouseDown()
{
	__asm
	{
		pop eax
		push ecx
		push eax
		mov ecx, 0x488590
		jmp ecx
	}
}
__declspec(naked) void SeedPacket::OnPlanted()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x488EC0
		jmp ecx
	}
}
__declspec(naked) bool SeedPacket::MouseHitTest(int, int, HitResult*)
{
	__asm
	{
		push edi
		push ebx
		push esi

		mov eax, ecx
		mov esi, [esp + 0x10]
		mov ebx, [esp + 0x14]
		mov edi, [esp + 0x18]

		pop esi
		pop ebx
		pop edi
		ret 0xC
	}
}
__declspec(naked) void SeedPacket::SetPacketType(SeedType, SeedType)
{
	__asm
	{
		push esi
		push edi

		mov esi, ecx
		mov edi, [esp + 0x0C]
		mov edx, [esp + 0x10]
		mov ecx, 0x489B50
		call ecx

		pop edi
		pop esi
		ret 0x8
	}
}
__declspec(naked) void __stdcall SeedPacket::DrawSeed(Sexy::Graphics*, float, float, SeedType, SeedType, float, float, float)
{
	__asm
	{
		push esi
		push ebx

		mov esi, [esp + 0x0C]
		mov ebx, [esp + 0x1C]
		push [esp + 0x28]// Scale
		push [esp + 0x28]// OffsetY
		push [esp + 0x28]// OffsetX
		push [esp + 0x24]// SeedType
		push [esp + 0x24]// Y
		push [esp + 0x24]// X
		mov ecx, 0x487380
		call ecx

		pop ebx
		pop esi
		ret 0x20
	}
}
__declspec(naked) void __cdecl SeedPacket::DrawSeedPacket(Sexy::Graphics*, float, float, SeedType, SeedType, float, int, bool, bool)
{
	__asm
	{
		mov eax, 0x4876F0
		jmp eax
	}
}
#pragma endregion

#pragma region SeedBank Functions
__declspec(naked) void SeedBank::Draw(Sexy::Graphics*)
{
	__asm
	{
		pop eax
		push ecx
		push eax
		mov ecx, 0x489630
		jmp ecx
	}
}
__declspec(naked) bool SeedBank::MouseHitTest(int, int, HitResult*)
{
	__asm
	{
		mov eax, [esp + 0x0C]
		push [esp + 0x08]
		push [esp + 0x08]
		push ecx
		mov ecx, 0x489970
		call ecx
		ret 0x0C
	}
}
__declspec(naked) bool SeedBank::ContainsPoint(int, int)
{
	__asm
	{
		push esi

		mov eax, ecx
		mov edx, [esp + 0x8]
		mov esi, [esp + 0xC]
		mov ecx, 0x489A20
		call ecx

		pop esi
		ret 0x8
	}
}
__declspec(naked) void SeedBank::AddSeed(SeedType)
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x489A50
		jmp ecx
	}
}
__declspec(naked) void SeedBank::RemoveSeed(int)
{
	__asm
	{
		push esi

		mov esi, ecx
		mov edx, [esp + 0x8]
		mov ecx, 0x489AC0
		call ecx

		pop esi
		ret 0x4
	}
}
__declspec(naked) int SeedBank::GetNumSeedsOnConveyorBelt()
{
	__asm
	{
		mov eax, 0x489B20
		jmp eax
	}
}
__declspec(naked) void SeedBank::UpdateConveyorBelt()
{
	__asm
	{
		push esi

		mov esi, ecx
		mov ecx, 0x489C70
		call ecx

		pop esi
		ret
	}
}
__declspec(naked) void SeedBank::UpdateWidth()
{
	__asm
	{
		push esi

		mov esi, ecx
		mov ecx, 0x489CD0
		call ecx

		pop esi
		ret
	}
}
__declspec(naked) void SeedBank::RefreshAllPackets()
{
	__asm
	{
		pop eax
		push ecx
		push eax
		mov ecx, 0x489D50
		jmp ecx
	}
}
#pragma endregion
