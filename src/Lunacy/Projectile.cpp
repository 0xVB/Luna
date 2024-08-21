#include "Lunacy/Projectile.h"
#include "Lunacy/Attachment.h"
#include "Lunacy/Zombie.h"

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

__declspec(naked) void Projectile::UpdateMotion()
{
	__asm
	{
		push esi
		mov esi, ecx
		mov ecx, 0x46DC70
		call ecx
		pop esi
		ret
	}
}

__declspec(naked) void Projectile::DrawShadow(Sexy::Graphics*)
{
	__asm
	{
		push esi
		mov esi, ecx
		push [esp + 0x8]
		mov ecx, 0x46E8C0
		call ecx
		pop esi
		ret 0x4
	}
}

// X, Y, Lane, RenderOrder
__declspec(naked) void Projectile::Init(ProjectileType, int, int, int, int)
{
	__asm
	{
		mov eax, [esp + 0xC]// Lane
		push [esp + 0x4]// ProjType
		push [esp + 0x18]// RenderOrder
		push [esp + 0x14]// Y
		push [esp + 0x14]// X
		push ecx// this*
		mov ecx, 0x46C730
		call ecx
		ret 0x14
	}
}

__declspec(naked) bool Projectile::IsPeaInTorchwood()
{
	__asm
	{
		push edi
		mov edi, ecx
		mov ecx, 0x46CC30
		call ecx
		pop edi
		ret
	}
}

__declspec(naked) DamageFlag Projectile::GetDamageFlags(Zombie*)
{
	__asm
	{
		push edi
		mov edi, ecx
		mov eax, [esp + 0x8]
		mov ecx, 0x46D230
		call ecx
		pop edi
		ret 0x4
	}
}

__declspec(naked) bool Projectile::IsZombieHitBySplash(Zombie*)
{
	__asm
	{
		pop edx// Ret
		pop eax// Zombie*
		push ecx
		push edx
		mov ecx, 0x46D2B0
		jmp ecx
	}
}

__declspec(naked) bool Projectile::DoesSplashDamage(Zombie*)
{
	__asm
	{
		mov eax, ecx
		pop edx// Ret
		pop ecx
		push edx
		mov edx, 0x46D1F0
		jmp edx
	}
}

__declspec(naked) void Projectile::PlayImpactSound(Zombie*)
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x46DD30
		jmp ecx
	}
}

__declspec(naked) void Projectile::DoSplashDamage(Zombie*)
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x46D390
		jmp ecx
	}
}

__declspec(naked) void Projectile::UpdateLobMotion()
{
	__asm
	{
		pop eax// Ret
		push ecx
		push eax
		mov eax, 0x46D490
		jmp eax
	}
}

__declspec(naked) void Projectile::UpdateNormalMotion()
{
	__asm
	{
		pop eax// Ret
		push ecx
		push eax
		mov ecx, 0x46D890
		jmp ecx
	}
}

__declspec(naked) void Projectile::ToPea(int)
{
	__asm
	{
		push ebx
		mov ebx, [esp + 0x8]
		mov eax, ecx
		mov ecx, 0x46EE00
		call ecx
		pop ebx
		ret 0x4
	}
}

__declspec(naked) bool Projectile::CantHitHighGround()
{
	__asm
	{
		mov eax, 0x46D090
		jmp eax
	}
}

__declspec(naked) void Projectile::CheckForHighGround()
{
	__asm
	{
		push esi
		mov esi, ecx
		mov ecx, 0x46D0D0
		call ecx
		pop esi
		ret 0x4
	}
}

void Projectile::RemoveEffects()
{
	TryToGet(mAttachmentID)->Die();
}

bool Projectile::BlockedByHighGround()
{
	return not CantHitHighGround();
}

Sexy::IRect Projectile::GetHitbox()
{
	Sexy::IRect Out = Sexy::IRect();
	GETPRECT(this, &Out);
	return Out;
}

void Projectile::SetupLobbedProjectile()
{
	mMotionType = MOTION_LOBBED;
	mVelY = 0;
	mAccZ = 0.115f;
	mVelZ = 12.0f;
}

void Projectile::AimLobAt(Zombie* aZombie, bool AccountForSpeed)
{
	if (!AccountForSpeed || aZombie->mIceTrapCounter)
	{
		AimLobAt(aZombie->mPosX);
		return;
	}

	float aSpeed = aZombie->mVelX / (1 + (aZombie->mChilledCounter > 1));
	int Ticks = GetTicksToTarget(0, 1, mVelZ, mAccZ);
	float zPos = aZombie->mPosX - aSpeed * Ticks;
	float xDelta = zPos - mPosX;
	mVelX = xDelta / Ticks;
}

void Projectile::AimLobAt(int X)
{
	int Ticks = GetTicksToTarget(0, 1, mVelZ, mAccZ);
	float xDelta = X - mPosX;
	mVelX = xDelta / Ticks;
}