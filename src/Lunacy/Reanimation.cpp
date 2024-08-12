#include "Lunacy/Reanimation.h"

CONST DWORD CONSTRUCT = 0x471920;
__declspec(naked) void __stdcall Reanimation::CreateReanim(Reanimation*)
{
	__asm
	{
		pop eax// Ret
		pop edx// Reanim
		push eax
		jmp CONSTRUCT
	}
}

Reanimation::Reanimation()
{
	Reanimation::CreateReanim(this);
}

Reanimation::~Reanimation()
{
	Die();
}

CONST DWORD INITTYPE = 0x471A60;
__declspec(naked) void Reanimation::Initialize(float, float, ReanimationType)
{
	__asm
	{
		push edi
		push esi
		mov edi, ecx
		mov esi, [esp + 0x14]
		push [esp + 0x10]
		push [esp + 0x10]
		call INITTYPE
		pop esi
		pop edi
		ret 0xC
	}
}

CONST DWORD INITDEF = 0x471B00;
__declspec(naked) void Reanimation::Initialize(float, float, ReanimatorDefinition*)
{
	__asm
	{
		mov eax, [esp + 0xC]
		push [esp + 0x8]
		push [esp + 0x8]
		push ecx
		call INITDEF
		ret 0xC
	}
}

CONST DWORD UPDATE = 0x471BC0;
__declspec(naked) void Reanimation::Update()
{
	__asm
	{
		jmp UPDATE
	}
}

CONST DWORD DIE = 0x4733F0;
__declspec(naked) void Reanimation::Die()
{
	__asm
	{
		jmp DIE
	}
}

CONST DWORD ATTANIM = 0x472F80;
__declspec(naked) void Reanimation::AttachToAnotherReanim(Reanimation*, const char*)
{
	__asm
	{
		push esi
		mov esi, ecx
		mov eax, [esp + 0x8]
		mov edx, [esp + 0xC]
		call ATTANIM
		pop esi
		ret 0x8
	}
}

CONST DWORD OVERRIDE = 0x473490;
__declspec(naked) void Reanimation::SetImageOverride(const char*, Sexy::Image*)
{
	__asm
	{
		pop edx// Ret
		pop eax// TrackName
		push edx
		jmp OVERRIDE
	}
}

CONST DWORD GETOVER = 0x473470;
__declspec(naked) Sexy::Image* Reanimation::GetImageOverride(const char*)
{
	__asm
	{
		pop edx// Ret
		pop eax// TrackName
		push edx
		jmp GETOVER
	}
}

CONST DWORD ATTPART = 0x473070;
__declspec(naked) AttachEffect* Reanimation::AttachParticleToTrack(const char*, ParticleSystem*, float, float)
{
	__asm
	{
		pop edx// Ret
		pop eax// TrackName
		push edx
		jmp ATTPART
	}
}