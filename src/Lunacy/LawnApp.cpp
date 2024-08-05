#include "Lunacy/LawnApp.h"

LawnApp* LawnApp::GetApp()
{
	return *(LawnApp**)0x6A9EC0;
}

CONST DWORD ADDPARTICLE = 0x453C80;
__declspec(naked) ParticleSystem* LawnApp::AddParticles(ParticleEffect, float, float, int)
{
	__asm
	{
		mov edx, ecx
		mov eax, [esp + 0x4]
		mov ecx, [esp + 0x10]
		push [esp + 0xC]
		push [esp + 0xC]
		call ADDPARTICLE
		ret 0x10
	}
}

CONST DWORD LMBX = 0x4504B0;
__declspec(naked) int LawnApp::LawnMessageBox(int, const char*, const char*, const char*, const char*, int)
{
	__asm
	{
		pop eax// Return addr
		push ecx// this
		push eax
		jmp LMBX
	}
}

CONST DWORD ADDREANIM = 0x453C30;
__declspec(naked) Reanimation* LawnApp::AddReanim(ReanimationType, float, float, int)
{
	__asm
	{
		push ebx
		mov eax, ecx
		mov ebx, [esp + 0x8]
		push [esp + 0x14]
		push [esp + 0x14]
		push [esp + 0x14]
		call ADDREANIM
		pop ebx
		ret 0x10
	}
}