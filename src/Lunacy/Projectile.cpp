#include "Lunacy/Projectile.h"

CONST DWORD UPDATE = 0x46E460;
__declspec(naked) void Projectile::Update()
{
	__asm
	{
		mov eax, ecx
		jmp UPDATE
	}
}

CONST DWORD DRAW = 0x46E540;
__declspec(naked) void Projectile::Draw(Sexy::Graphics*)
{
	__asm
	{
		pop edx// Ret
		push ecx
		push edx
		jmp DRAW
	}
}

Projectile::Projectile(ProjectileType T)
{
	mPos = Sexy::FVector2();
	mVel = Sexy::FVector2();
	mProjectileType = T;
	mMotionType = MOTION_STRAIGHT;
	mAttachmentID = ATTACHMENTID_NULL;
	mTargetZombieID = ZOMBIEID_NULL;
}

CONST DWORD DIE = 0x46EB20;
__declspec(naked) void Projectile::Die()
{
	__asm
	{
		mov eax, ecx
		jmp DIE
	}
}

CONST DWORD PTARG = 0x46CAA0;
__declspec(naked) Plant* Projectile::FindTargetPlant()
{
	__asm
	{
		pop eax// Ret
		push ecx
		push eax
		jmp PTARG
	}
}

CONST DWORD ZTARG = 0x46CD40;
__declspec(naked) Zombie* Projectile::FindTargetZombie()
{
	__asm
	{
		pop eax// Ret
		push ecx
		push eax
		jmp ZTARG
	}
}

CONST DWORD GETRECT = 0x46EBC0;
__declspec(naked) void __stdcall GETPRECT(Projectile*, Sexy::IRect*)
{
	__asm
	{
		push esi
		mov esi, [esp + 0x8]
		mov ecx, [esp + 0xC]
		call GETRECT
		pop esi
		ret 0x8
	}
}

CONST DWORD COLLIDE = 0x46E000;
__declspec(naked) void Projectile::Collide(Zombie*)
{
	__asm
	{
		pop edx// Ret
		pop eax
		push edx
		jmp COLLIDE
	}
}

CONST DWORD FIREBALL = 0x46ECB0;
__declspec(naked) void Projectile::ToFireball(int)
{
	__asm
	{
		pop edx// Ret
		pop eax
		push edx
		jmp FIREBALL
	}
}

Sexy::IRect Projectile::GetHitbox()
{
	Sexy::IRect Out = Sexy::IRect();
	GETPRECT(this, &Out);
	return Out;
}