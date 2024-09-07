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

// Cant guarantee these functions will work or are optimized. They were auto generated.
#pragma region Autogen functions
constexpr unsigned int ZOMBIE_ISTANGLEKELPTARGET = 0x526190;
__declspec(naked) bool Zombie::IsTangleKelpTarget()
{
	__asm
	{
		push edi

		mov edi, ecx
		call ZOMBIE_ISTANGLEKELPTARGET

		pop edi
		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_DROPFLAG = 0x529870;
__declspec(naked) void Zombie::DropFlag()
{
	__asm
	{
		push ebx

		mov ebx, ecx
		call ZOMBIE_DROPFLAG

		pop ebx
		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_DROPPOLE = 0x529970;
__declspec(naked) void Zombie::DropPole()
{
	__asm
	{
		push esi

		mov esi, ecx
		call ZOMBIE_DROPPOLE

		pop esi
		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_DROPHEAD = 0x529A30;
__declspec(naked) void Zombie::DropHead(DamageFlag)
{
	__asm
	{

		push[esp + 0x4]
		push ecx
		call ZOMBIE_DROPHEAD

		ret 0x4
	}
}

constexpr unsigned int ZOMBIE_DROPARM = 0x529EF0;
__declspec(naked) void Zombie::DropArm(DamageFlag)
{
	__asm
	{
		push ebx

		push[esp + 0x8]
		mov ebx, ecx
		call ZOMBIE_DROPARM

		pop ebx
		ret 0x4
	}
}

constexpr unsigned int ZOMBIE_UPDATEDAMAGESTATES = 0x52A470;
__declspec(naked) void Zombie::UpdateDamageStates(DamageFlag)
{
	__asm
	{
		push edi

		mov edi, [esp + 0x8]
		mov eax, ecx
		call ZOMBIE_UPDATEDAMAGESTATES

		pop edi
		ret 0x4
	}
}

constexpr unsigned int ZOMBIE_UPDATEACTIONS = 0x52B110;
__declspec(naked) void Zombie::UpdateActions()
{
	__asm
	{

		mov eax, ecx
		call ZOMBIE_UPDATEACTIONS

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_CHECKFORLAWNEDGE = 0x52B280;
__declspec(naked) void Zombie::CheckForLawnEdge()
{
	__asm
	{

		mov eax, ecx
		call ZOMBIE_CHECKFORLAWNEDGE

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_ISWALKINGBACKWARDS = 0x52BEE0;
__declspec(naked) bool Zombie::IsWalkingBackwards()
{
	__asm
	{

		mov ecx, ecx
		call ZOMBIE_ISWALKINGBACKWARDS

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_CANTARGETPLANT = 0x52E4C0;
__declspec(naked) bool Zombie::CanTargetPlant(Plant*, ZombieAttackType)
{
	__asm
	{

		push[esp + 0x8]
		push[esp + 0x8]
		mov ecx, ecx
		call ZOMBIE_CANTARGETPLANT

		ret 0x8
	}
}

constexpr unsigned int ZOMBIE_FINDPLANTTARGET = 0x52E780;
__declspec(naked) Plant* Zombie::FindPlantTarget(ZombieAttackType)
{
	__asm
	{

		push[esp + 0x4]
		push ecx
		call ZOMBIE_FINDPLANTTARGET

		ret 0x4
	}
}

constexpr unsigned int ZOMBIE_FINDZOMBIETARGET = 0x52E840;
__declspec(naked) Zombie* Zombie::FindZombieTarget()
{
	__asm
	{

		push ecx
		call ZOMBIE_FINDZOMBIETARGET

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_ZAMBONIDEATH = 0x52E9A0;
__declspec(naked) void Zombie::ZamboniDeath(DamageFlag)
{
	__asm
	{

		push[esp + 0x4]
		mov eax, ecx
		call ZOMBIE_ZAMBONIDEATH

		ret 0x4
	}
}

constexpr unsigned int ZOMBIE_CATAPULTDEATH = 0x52EC00;
__declspec(naked) void Zombie::CatapultDeath(DamageFlag)
{
	__asm
	{

		push[esp + 0x4]
		mov eax, ecx
		call ZOMBIE_CATAPULTDEATH

		ret 0x4
	}
}

constexpr unsigned int ZOMBIE_ISIMMOBILIZED = 0x52EEF0;
__declspec(naked) bool Zombie::IsImmobilized()
{
	__asm
	{

		mov eax, ecx
		call ZOMBIE_ISIMMOBILIZED

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_ISMOVINGATCHILLEDSPEED = 0x52EF10;
__declspec(naked) bool Zombie::IsChilled()
{
	__asm
	{

		mov eax, ecx
		call ZOMBIE_ISMOVINGATCHILLEDSPEED

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_SETANIMRATE = 0x52EFD0;
__declspec(naked) void Zombie::SetFPS(float)
{
	__asm
	{

		push[esp + 0x4]
		mov eax, ecx
		call ZOMBIE_SETANIMRATE

		ret 0x4
	}
}

constexpr unsigned int ZOMBIE_APPLYANIMRATE = 0x52EFF0;
__declspec(naked) void Zombie::ApplyFPS(float)
{
	__asm
	{

		push[esp + 0x4]
		mov eax, ecx
		call ZOMBIE_APPLYANIMRATE

		ret 0x4
	}
}

constexpr unsigned int ZOMBIE_STARTEATING = 0x52F250;
__declspec(naked) void Zombie::StartEating()
{
	__asm
	{

		mov eax, ecx
		call ZOMBIE_STARTEATING

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_STARTWALKANIM = 0x52F2E0;
__declspec(naked) void Zombie::StartWalking(int)
{
	__asm
	{
		push esi

		mov esi, [esp + 0x8]
		mov eax, ecx
		call ZOMBIE_STARTWALKANIM

		pop esi
		ret 0x4
	}
}

constexpr unsigned int ZOMBIE_STOPEATING = 0x52F440;
__declspec(naked) void Zombie::StopEating()
{
	__asm
	{
		push edi

		mov edi, ecx
		call ZOMBIE_STOPEATING

		pop edi
		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_POOLSPLASH = 0x52F6D0;
__declspec(naked) void Zombie::PoolSplash(bool)
{
	__asm
	{

		push[esp + 0x4]
		mov eax, ecx
		call ZOMBIE_POOLSPLASH

		ret 0x4
	}
}

constexpr unsigned int ZOMBIE_EATPLANT = 0x52FB40;
__declspec(naked) void Zombie::EatPlant(Plant*)
{
	__asm
	{

		push ecx
		mov ecx, [esp + 0x4]
		call ZOMBIE_EATPLANT

		ret 0x4
	}
}

constexpr unsigned int ZOMBIE_EATZOMBIE = 0x52FE10;
__declspec(naked) void Zombie::EatZombie(Zombie*)
{
	__asm
	{
		push edi

		mov eax, [esp + 0x8]
		mov edi, ecx
		call ZOMBIE_EATZOMBIE

		pop edi
		ret 0x4
	}
}

constexpr unsigned int ZOMBIE_TRYSPAWNLEVELAWARD = 0x52FE50;
__declspec(naked) void Zombie::TrySpawnLevelAward()
{
	__asm
	{

		push ecx
		call ZOMBIE_TRYSPAWNLEVELAWARD

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_DROPSHIELD = 0x530A00;
__declspec(naked) void Zombie::DropShield(DamageFlag)
{
	__asm
	{

		push[esp + 0x4]
		push ecx
		call ZOMBIE_DROPSHIELD

		ret 0x4
	}
}

constexpr unsigned int ZOMBIE_DROPHELM = 0x530E30;
__declspec(naked) void Zombie::DropHelm(DamageFlag)
{
	__asm
	{

		push[esp + 0x4]
		mov eax, ecx
		call ZOMBIE_DROPHELM

		ret 0x4
	}
}

constexpr unsigned int ZOMBIE_GETPOSYBASEDONROW = 0x531880;
__declspec(naked) float Zombie::GetZombieYPos(int)
{
	__asm
	{

		push[esp + 0x4]
		mov eax, ecx
		call ZOMBIE_GETPOSYBASEDONROW

		ret 0x4
	}
}

constexpr unsigned int ZOMBIE_RISEFROMGRAVE = 0x531C90;
__declspec(naked) void Zombie::RiseFromGrave(int, int)
{
	__asm
	{
		push ebx

		push[esp + 0xC]
		mov eax, [esp + 0xC]
		mov ebx, ecx
		call ZOMBIE_RISEFROMGRAVE

		pop ebx
		ret 0x8
	}
}

constexpr unsigned int ZOMBIE_REMOVEICETRAP = 0x532350;
__declspec(naked) void Zombie::RemoveIceTrap()
{
	__asm
	{

		mov eax, ecx
		call ZOMBIE_REMOVEICETRAP

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_HITICETRAP = 0x5323C0;
__declspec(naked) void Zombie::HitIceTrap()
{
	__asm
	{

		mov eax, ecx
		call ZOMBIE_HITICETRAP

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_REMOVEBUTTER = 0x532570;
__declspec(naked) void Zombie::RemoveButter()
{
	__asm
	{

		mov eax, ecx
		call ZOMBIE_REMOVEBUTTER

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_APPLYBUTTER = 0x5326D0;
__declspec(naked) void Zombie::ApplyButter()
{
	__asm
	{

		mov eax, ecx
		call ZOMBIE_APPLYBUTTER

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_MOWDOWN = 0x5327E0;
__declspec(naked) void Zombie::MowDown()
{
	__asm
	{
		push edi

		mov edi, ecx
		call ZOMBIE_MOWDOWN

		pop edi
		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_REMOVECOLDEFFECTS = 0x532B40;
__declspec(naked) void Zombie::RemoveCold()
{
	__asm
	{

		mov eax, ecx
		call ZOMBIE_REMOVECOLDEFFECTS

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_APPLYBURN = 0x532B70;
__declspec(naked) void Zombie::ApplyBurn()
{
	__asm
	{

		mov ecx, ecx
		call ZOMBIE_APPLYBURN

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_ATTACHSHIELD = 0x533000;
__declspec(naked) void Zombie::AttachShield()
{
	__asm
	{

		mov eax, ecx
		call ZOMBIE_ATTACHSHIELD

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_DETACHSHIELD = 0x5330E0;
__declspec(naked) void Zombie::DetachShield()
{
	__asm
	{

		mov eax, ecx
		call ZOMBIE_DETACHSHIELD

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_DODAISIES = 0x5335A0;
__declspec(naked) void Zombie::DoDaisies()
{
	__asm
	{
		push esi

		mov esi, ecx
		call ZOMBIE_DODAISIES

		pop esi
		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_HASSHADOW = 0x533F70;
__declspec(naked) bool Zombie::HasShadow()
{
	__asm
	{

		mov ecx, ecx
		call ZOMBIE_HASSHADOW

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_ISFLYING = 0x534680;
__declspec(naked) bool Zombie::IsFlying()
{
	__asm
	{

		mov eax, ecx
		call ZOMBIE_ISFLYING

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_GETBOBSLEDPOSITION = 0x5346A0;
__declspec(naked) int Zombie::GetBobsledPosition()
{
	__asm
	{

		mov ecx, ecx
		call ZOMBIE_GETBOBSLEDPOSITION

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_ISDEADORDYING = 0x534700;
__declspec(naked) bool Zombie::IsDeadOrDying()
{
	__asm
	{

		mov eax, ecx
		call ZOMBIE_ISDEADORDYING

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_UPDATEZOMBIECHIMNEY = 0x534730;
__declspec(naked) void Zombie::UpdateZombieChimney()
{
	__asm
	{
		push esi

		mov esi, ecx
		call ZOMBIE_UPDATEZOMBIECHIMNEY

		pop esi
		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_WALKINTOHOUSE = 0x534780;
__declspec(naked) void Zombie::WalkIntoHouse()
{
	__asm
	{

		mov eax, ecx
		call ZOMBIE_WALKINTOHOUSE

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_BOSSPLAYIDLE = 0x534920;
__declspec(naked) void Zombie::BossPlayIdle()
{
	__asm
	{

		mov eax, ecx
		call ZOMBIE_BOSSPLAYIDLE

		ret 0x0
	}
}

constexpr unsigned int ZOMBIE_DRAWBOSSFIREBALL = 0x534960;
__declspec(naked) void Zombie::DrawBossFireBall(Sexy::Graphics*)
{
	__asm
	{
		push esi

		mov esi, [esp + 0x8]
		mov eax, ecx
		call ZOMBIE_DRAWBOSSFIREBALL

		pop esi
		ret 0x4
	}
}
#pragma endregion