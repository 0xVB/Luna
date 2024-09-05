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
	auto Reanim = mApp->mEffectSystem->mReanimationHolder->Fetch(mBodyReanimID);
	if (Reanim)
		Reanim->Die();
	return LoadReanimUnsafe(Type);
}

void Zombie::UpdateReanim()
{
	auto aReanim = TryToGet(mBodyReanimID);
	if (aReanim) aReanim->Update();
	
	aReanim = TryToGet(mSpecialHeadReanimID);
	if (aReanim) aReanim->Update();

	aReanim = TryToGet(mMoweredReanimID);
	if (aReanim) aReanim->Update();

	aReanim = TryToGet(mBossFireBallReanimID);
	if (aReanim) aReanim->Update();
}

__declspec(naked) void Zombie::DrawShadow(Sexy::Graphics*)
{
	__asm
	{
		push edi
		mov edi, ecx
		push [esp + 0x8]
		mov ecx, 0x5340C0
		call ecx
		pop edi
		ret 0x4
	}
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

__declspec(naked) void Zombie::PlayReanimTrack(const char*, ReanimLoopType, int, float)
{
	__asm
	{
		push edi

		mov edi, ecx
		push [esp + 0x14]
		push [esp + 0x14]
		push [esp + 0x14]
		push [esp + 0x14]
		mov ecx, 0x528B00
		call ecx

		pop edi
		ret 0x10
	}
}

__declspec(naked) void Zombie::GetTrackPosition(const char*, float&, float&)
{
	__asm
	{
		push esi
		push edi

		mov esi, ecx
		mov edi, [esp + 0x14]
		push [esp + 0x10]
		push [esp + 0x10]

		pop edi
		pop esi
		ret 0xC
	}
}

void Zombie::BungeeDropZombie(ZombieType Type, int Col, int Row)
{
	auto aZombie = mLawn->NewZombie(Type, Row, 0);
	BungeeDropZombie(aZombie, Col, Row);
}

Zombie* TryToGet(ZombieID ID)
{
	return LawnApp::GetApp()->mLawn->mZombies.Fetch((unsigned int)ID);
}

#pragma region Base Functions
__declspec(naked) void Zombie::SquishPlantsInCell(int, int, ZombieAttackType)
{
	__asm
	{
		push edi

		mov edi, ecx
		push [esp + 0x10]
		push [esp + 0x10]
		push [esp + 0x10]
		mov ecx, 0x52E920
		call ecx

		pop edi
		ret 0xC
	}
}
__declspec(naked) void __stdcall Zombie::SetupDoorArms(Reanimation*, bool)
{
	__asm
	{
		push ebx

		mov ebx, [esp + 0x8]
		push [esp + 0xC]
		mov ecx, 0x524040
		call ecx

		pop ebx
		ret 0x8
	}
}
__declspec(naked) void __stdcall Zombie::SetupReanimLayers(Reanimation*, ZombieType)
{
	__asm
	{
		push esi

		mov esi, [esp + 0xC]
		mov eax, [esp + 0x8]
		mov ecx, 0x5240B0
		call ecx

		pop esi
		ret 0x8
	}
}
__declspec(naked) void Zombie::ReanimIgnoreClipRect(const char*, bool)
{
	__asm
	{
		mov eax, 0x524280
		jmp eax
	}
}
__declspec(naked) void Zombie::EnableClipping()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x524310
		jmp ecx
	}
}
__declspec(naked) void Zombie::LoadPlainZombieReanim()
{
	__asm
	{
		push edi

		mov edi, ecx
		mov ecx, 0x524370
		call ecx

		pop edi
		ret
	}
}
__declspec(naked) void Zombie::PickBungeeZombieTarget(int)
{
	__asm
	{
		pop eax
		push ecx
		push eax
		mov eax, 0x5246A0
		jmp eax
	}
}
__declspec(naked) void Zombie::BungeeDropZombie(Zombie*, int, int)
{
	__asm
	{
		push ebx

		mov ebx, ecx
		mov eax, [esp + 0x10]
		mov ecx, [esp + 0x0C]
		push [esp + 0x08]
		mov edx, 0x524970
		call edx

		pop ebx
		ret 0xC
	}
}
__declspec(naked) void Zombie::BungeeStealTarget()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x524C70
		jmp ecx
	}
}
__declspec(naked) void Zombie::BungeeLiftTarget()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x524D70
		jmp ecx
	}
}
__declspec(naked) void Zombie::BungeeLanding()
{
	__asm
	{
		pop eax
		push ecx
		push eax
		mov eax, 0x524EF0
		jmp eax
	}
}
__declspec(naked) void Zombie::UpdateBungee()
{
	__asm
	{
		push edi

		mov edi, ecx
		mov ecx, 0x525180
		call ecx

		pop edi
		ret
	}
}
__declspec(naked) void Zombie::PogoBreak(DamageFlag)
{
	__asm
	{
		pop eax
		push ecx
		push eax
		mov eax, 0x525350
		jmp eax
	}
}
__declspec(naked) bool Zombie::IsPogoBouncing()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x525460
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdatePogo()
{
	__asm
	{
		push edi

		mov edi, ecx
		mov ecx, 0x525480
		call ecx

		pop edi
		ret
	}
}
__declspec(naked) void Zombie::CatapultFire(Plant*)
{
	__asm
	{
		pop edx
		pop eax
		push edx
		mov edx, 0x525730
		jmp edx
	}
}
__declspec(naked) Plant* Zombie::FindCatapultTarget()
{
	__asm
	{
		pop eax
		push ecx
		push eax
		mov ecx, 0x525890
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdateCatapult()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x5259D0
		jmp ecx
	}
}
__declspec(naked) void Zombie::LandFlyer(DamageFlag)
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x525B60
		jmp ecx
	}
}
__declspec(naked) void Zombie::SetPropellerHatSpin(bool)
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x532510
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdateFlyingZombie()
{
	__asm
	{
		push edi

		mov edi, ecx
		mov ecx, 0x525BE0
		call ecx

		pop edi
		ret
	}
}
__declspec(naked) void Zombie::BobseldCrash()
{
	__asm
	{
		push ebx

		mov ebx, ecx
		mov ecx, 0x527F20
		call ecx

		pop ebx
		ret
	}
}
__declspec(naked) void Zombie::UpdateBobsled()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x528050
		jmp ecx
	}
}
__declspec(naked) void Zombie::DiggerLoseAxe()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x528240
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdateDigger()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x528310
		jmp ecx
	}
}
__declspec(naked) void Zombie::SummonBackupDancer(int, int)
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x528760
		jmp ecx
	}
}
__declspec(naked) void Zombie::SummonBackupDancers()
{
	__asm
	{
		push esi

		mov esi, ecx
		mov ecx, 0x528970
		call ecx

		pop esi
		ret
	}
}
__declspec(naked) bool Zombie::NeedsBackupDancers()
{
	__asm
	{
		push edi

		mov edi, ecx
		mov ecx, 0x528A50
		call ecx

		pop edi
		ret
	}
}
__declspec(naked) void Zombie::UpdateGraveRise()
{
	__asm
	{
		push esi

		mov esi, ecx
		mov ecx, 0x528EC0
		call ecx

		pop esi
		ret
	}
}
__declspec(naked) void Zombie::UpdateBackupDancer()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x528B80
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdateDancer()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x528CA0
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdateDolphinRider()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x5261E0
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdateSnorkel()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x526720
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdateJackInTheBox()
{
	__asm
	{
		pop eax
		push ecx
		push eax
		mov ecx, 0x526AE0
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdateGargantuar()
{
	__asm
	{
		pop eax
		push ecx
		push eax
		mov ecx, 0x526D10
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdateImp()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x5272E0
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdatePeaHead()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x5273D0
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdateJalapenoHead()
{
	__asm
	{
		push edi

		mov edi, ecx
		mov ecx, 0x5275C0
		jmp ecx

		pop edi
		ret
	}
}
__declspec(naked) void Zombie::UpdateGatlingHead()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x527750
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdateSquashHead()
{
	__asm
	{
		pop eax
		push ecx
		push eax
		mov ecx, 0x527AA0
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdateZombaquarium()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x5291E0
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdatePoolZombie()
{
	__asm
	{
		push edi

		mov edi, ecx
		mov ecx, 0x5295F0
		call ecx

		pop edi
		ret
	}
}
__declspec(naked) void Zombie::UpdateZombieHighGround()
{
	__asm
	{
		mov eax, 0x5296E0
		jmp eax
	}
}
__declspec(naked) void Zombie::UpdateZombieFalling()
{
	__asm
	{
		push esi

		mov esi, ecx
		mov ecx, 0x529770
		call ecx

		pop esi
		ret
	}
}
__declspec(naked) void Zombie::UpdateZamboni()
{
	__asm
	{
		push esi

		mov esi, ecx
		mov ecx, 0x52A7B0
		call ecx

		pop esi
		ret
	}
}
__declspec(naked) void Zombie::UpdateYeti()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x52A8E0
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdateLadder()
{
	__asm
	{
		push ebx

		mov ebx, ecx
		mov ecx, 0x52A930
		call ecx

		pop ebx
		ret
	}
}
__declspec(naked) void Zombie::UpdateZombieMovement()
{
	__asm
	{
		push esi

		mov esi, ecx
		mov ecx, 0x52AA40
		call ecx

		pop esi
		ret
	}
}
__declspec(naked) void Zombie::UpdateZombiePosition()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x52AD30
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdateLadderClimb()
{
	__asm
	{
		push esi

		mov esi, ecx
		mov ecx, 0x52B010
		call ecx

		pop esi
		ret
	}
}
__declspec(naked) void Zombie::UpdatePlaying()
{
	__asm
	{
		push edi

		mov edi, ecx
		mov ecx, 0x52B340
		call ecx

		pop edi
		ret
	}
}
__declspec(naked) void Zombie::UpdateYuckyFace()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x52B6A0
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdateDeath()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x5336B0
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdateMowered()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x533F10
		jmp ecx
	}
}
__declspec(naked) void Zombie::UpdateZombieInChimney()
{
	__asm
	{
		push esi

		mov esi, ecx
		mov ecx, 0x534730
		call ecx

		pop esi
		ret
	}
}
__declspec(naked) void Zombie::UpdateBossFireball()
{
	__asm
	{
		push ebx

		mov ebx, ecx
		mov ecx, 0x535C60
		call ecx

		pop ebx
		ret
	}
}
__declspec(naked) void Zombie::UpdateZomboss()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x536080
		jmp ecx
	}
}
#pragma endregion