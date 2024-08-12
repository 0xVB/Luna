#include "Lunacy/EffectSystem.h"
#include "Lunacy/LawnApp.h"
#include "Lunacy/Zombie.h"
#include "Lunacy/Lawn.h"

CONST DWORD UPDATE = 0x52AE60;
__declspec(naked) void Zombie::Update()
{
	__asm
	{
		mov eax, ecx
		jmp UPDATE
	}
}

CONST DWORD DRAW = 0x52E2E0;
__declspec(naked) void Zombie::Draw(Sexy::Graphics*)
{
	__asm
	{
		push ebx
		mov ebx, ecx
		push [esp + 0x8]
		call DRAW
		pop ebx
		ret 0x4
	}
}

Zombie::Zombie()
{
	mApp = LawnApp::GetApp();
	mLawn = mApp->mLawn;
	mHitbox = Sexy::IRect();
	mVisible = true;
	mRenderOrder = 400000;
	mRow = -1;
}

CONST DWORD INIT = 0x522580;
__declspec(naked) void Zombie::Init(int, ZombieType, unsigned char, Zombie*, int)
{
	__asm
	{
		mov eax, [esp + 0x4]
		push [esp + 0x14]
		push [esp + 0x14]
		push [esp + 0x14]
		push [esp + 0x14]
		push ecx
		call INIT
		ret 0x14
	}
}

CONST DWORD PICKRAND = 0x524A70;
__declspec(naked) void Zombie::PickRandomSpeed()
{
	__asm
	{
		mov eax, ecx
		jmp PICKRAND
	}
}

CONST DWORD LOADREANIM = 0x524470;
__declspec(naked) Reanimation* Zombie::LoadReanimUnsafe(ReanimationType)
{
	__asm
	{
		mov eax, ecx
		jmp LOADREANIM
	}
}

CONST DWORD DROPLOOT = 0x530170;
__declspec(naked) void Zombie::DropLoot()
{
	__asm
	{
		mov eax, ecx
		jmp DROPLOOT
	}
}

CONST DWORD DIELOOT = 0x5302F0;
__declspec(naked) void Zombie::DieLoot()
{
	__asm
	{
		jmp DIELOOT
	}
}

CONST DWORD DIENOLOOT = 0x530510;
__declspec(naked) void Zombie::DieNoLoot()
{
	__asm
	{
		jmp DIENOLOOT
	}
}

CONST DWORD BOSSDIE = 0x5366D0;
__declspec(naked) void Zombie::BossDie()
{
	__asm
	{
		jmp BOSSDIE
	}
}

CONST DWORD SETF = 0x536D90;
__declspec(naked) void Zombie::SetFuture(bool)
{
	__asm
	{
		push esi
		mov esi, ecx
		push [esp + 0x8]
		call SETF
		pop esi
		ret 0x4
	}
}

CONST DWORD SETM = 0x536C90;
__declspec(naked) void Zombie::SetMustache(bool)
{
	__asm
	{
		push esi
		mov esi, ecx
		push [esp + 0x8]
		call SETM
		pop esi
		ret 0x4
	}
}

CONST DWORD TAKEDAMAGE = 0x5317C0;
__declspec(naked) void Zombie::TakeDamage(int, DamageFlag)
{
	__asm
	{
		push esi
		mov esi, ecx
		mov eax, [esp + 0xC]
		push [esp + 0x8]
		call TAKEDAMAGE
		pop esi
		ret 0x8
	}
}


CONST DWORD UPDATEANIMSPD = 0x52F050;
__declspec(naked) void Zombie::UpdateAnimSpeed()
{
	__asm
	{
		push esi
		mov esi, ecx
		call UPDATEANIMSPD
		pop esi
		ret
	}
}

CONST DWORD APPLYCHILL = 0x530950;
__declspec(naked) void __stdcall ApplyChill(Zombie*, bool)
{
	__asm
	{
		pop ecx // Ret
		pop eax // Zombie
		push ecx// Ret
		jmp APPLYCHILL
	}
}

CONST DWORD LOADRES = 0x5369E0;
__declspec(naked) void __stdcall Zombie::PreloadResources(ZombieType)
{
	__asm
	{
		pop edx// Ret
		pop eax// Type
		push edx
		jmp LOADRES
	}
}

void Zombie::PreloadResources()
{
	Zombie::PreloadResources(mZombieType);
}

void Zombie::Die(bool DropLoot)
{
	if (DropLoot)
		DieLoot();
	else
		DieNoLoot();
}

Reanimation* Zombie::LoadReanim(ReanimationType Type)
{
	auto Reanim = mApp->mEffectSystem->mReanimationHolder->mReanimations.Fetch(mBodyReanimID);
	if (Reanim)
		Reanim->Die();
	return LoadReanimUnsafe(Type);
}

void Zombie::Init(int Row, ZombieType Type, unsigned char Variant, int FromWave, Zombie* Parent)
{
	Init(Row, Type, Variant, Parent, FromWave);
}

void Zombie::Chill(int Chill, int Freeze)
{
	if (!mHasHead)
	{
		mChilledCounter = Chill;
		return;
	}

	ApplyChill(this, max(Freeze, mIceTrapCounter));
	mIceTrapCounter = max(Freeze, mIceTrapCounter);
	mChilledCounter = max(Chill, mChilledCounter);
	UpdateAnimSpeed();
}

Zombie* TryToGet(ZombieID ID)
{
	return LawnApp::GetApp()->mLawn->mZombies.Fetch((unsigned int)ID);
}