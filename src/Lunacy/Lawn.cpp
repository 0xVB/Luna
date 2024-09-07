#include "Lunacy/Projectile.h"
#include "Lunacy/CGeometry.h"
#include "Lunacy/GridItem.h"
#include "Lunacy/Zombie.h"
#include "Lunacy/Pickup.h"
#include "Lunacy/Plant.h"
#include "Lunacy/Lawn.h"

CONST DWORD UPDATE = 0x415D40;
__declspec(naked) void Lawn::Update()
{
	__asm
	{
		jmp UPDATE
	}
}

CONST DWORD DRAW = 0x41ACF0;
__declspec(naked) void Lawn::Draw(Sexy::Graphics*)
{
	__asm
	{
		jmp DRAW
	}
}

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

CONST DWORD ADDPICK = 0x40CB10;
__declspec(naked) Pickup* Lawn::NewPickup(int, int, PickupType, PickupMotion)
{
	__asm
	{
		jmp ADDPICK
	}
}

CONST DWORD NEWZOMB = 0x40DDC0;
__declspec(naked) Zombie* Lawn::NewZombie(ZombieType, int, int)
{
	__asm
	{
		push ebx
		mov eax, ecx
		mov ebx, [esp + 0x10]
		push [esp + 0xC]
		push [esp + 0xC]
		call NEWZOMB
		pop ebx
		ret 0xC
	}
}
void Lawn::KillAllZombies(int Col, int Row, ZombieType Type, bool DropLoot)
{
	auto aZombie = mZombies.GetNext();
	while (aZombie)
	{
		if (Col != -1 && aZombie->GetColumn() != Col) goto Skip;
		if (Row != -1 && aZombie->mRow != Row) goto Skip;
		if (Type != ZOMBIE_NONE && aZombie->mZombieType != Type) goto Skip;
		aZombie->TakeDamage(aZombie->GetTotalHealth());

	Skip:
		aZombie = mZombies.GetNext(aZombie);
	}
}

GridItem* Lawn::NewGridItem(GridItemType Type, int Lane, int Column)
{
	auto aItem = mGridItems.Allocate();
	aItem->mGridItemType = Type;
	aItem->mRenderOrder = Lane * 10000 + 0x497CB;
	aItem->mCol = Column;
	aItem->mLane = Lane;
	aItem->mGridItemCounter = 0;
	aItem->mTransparentCounter = 500;

	return aItem;
}
Pickup* Lawn::NewPickup(PickupType Type, int X, int Y, PickupMotion M)
{
	return NewPickup(X, Y, Type, M);
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

void Lawn::KillAllPlants(int Col, int Row, SeedType Type)
{
	auto aPlant = mPlants.GetNext();
	while (aPlant)
	{
		if (Col != -1 && aPlant->mCol != Col) goto Skip;
		if (Row != -1 && aPlant->mRow != Row) goto Skip;
		if (Type != SEED_NONE && aPlant->mType != Type) goto Skip;
		aPlant->Die();

	Skip:
		aPlant = mPlants.GetNext(aPlant);
	}
}

GridItem* Lawn::AddGrave(int Col, int Lane, bool DoEffects, bool KillPlants)
{
	mEnableGraveStones = true;

	auto New = mGridItems.Allocate();
	New->mGridItemType = GRIDITEM_GRAVESTONE;
	New->mRenderOrder = Lane * 10000 + 0x497CB;
	New->mGridX = Col;
	New->mGridY = Lane;
	New->mGridItemCounter = 0;
	if (DoEffects) New->DoGraveEffects();
	if (KillPlants) KillAllPlants(Col, Lane);
	return New;
}

Pickup* Lawn::NewPacket(SeedType Type, int X, int Y)
{
	auto Packet = NewPickup(PICKUP_USABLE_SEED_PACKET, X, Y);
	Packet->mUsableSeedType = Type;
	return Packet;
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

using Sexy::Rect;
IRect Lawn::GridToPixelArea(int C, int L, int W, int H)
{
	auto Start = GridToPixel(C, L);
	auto End = GridToPixel(C + W, L + H);
	return IRect(Start, End - Start);
}
IRect Lawn::PixelToGridArea(int X, int Y, int W, int H)
{
	auto Start = PixelToGrid(X, Y);
	auto End = PixelToGrid(X + W, Y + H);
	return IRect(Start, End - Start);
}

Projectile* Lawn::GetNearestProjectile(FVector2 Point, float MinDist, float MaxDist, ProjectileType Filter, bool IsBlacklist)
{
	bool DoFilter = Filter != -1;
	auto aProj = mProjectiles.GetNext();
	float CurrentDist = 0;
	
	Projectile* ClosestProjectile = nullptr;
	float SmallestDist = MaxDist;

	while (aProj)
	{
		if (!DoFilter) goto Qualifies;
		if (IsBlacklist && aProj->mProjectileType == Filter) goto Skip;
		if (!IsBlacklist && aProj->mProjectileType != Filter) goto Skip;

	Qualifies:
		CurrentDist = aProj->DistanceFrom(Point);
		if (CurrentDist > MaxDist) goto Skip;
		if (CurrentDist < MinDist) goto Skip;

		if (!ClosestProjectile || (CurrentDist < SmallestDist))
		{
			ClosestProjectile = aProj;
			SmallestDist = CurrentDist;
		}

	Skip:
		aProj = mProjectiles.GetNext(aProj);
	}

	return ClosestProjectile;
}

GridItem* Lawn::GetNearestGridItem(FVector2 Point, float MinDist, float MaxDist, GridItemType Filter, bool IsBlacklist)
{
	bool DoFilter = Filter != -1;
	auto aItem = mGridItems.GetNext();
	float CurrentDist = 0;

	GridItem* ClosestItem = nullptr;
	float SmallestDist = MaxDist;

	while (aItem)
	{
		if (!DoFilter) goto Qualifies;
		if (IsBlacklist && aItem->mGridItemType == Filter) goto Skip;
		if (!IsBlacklist && aItem->mGridItemType != Filter) goto Skip;

	Qualifies:
		CurrentDist = aItem->mPos.GetDistance(Point);
		if (CurrentDist > MaxDist) goto Skip;
		if (CurrentDist < MinDist) goto Skip;

		if (!ClosestItem || (CurrentDist < SmallestDist))
		{
			ClosestItem = aItem;
			SmallestDist = CurrentDist;
		}

	Skip:
		aItem = mGridItems.GetNext(aItem);
	}

	return ClosestItem;
}

Zombie* Lawn::GetNearestZombie(FVector2 Point, float MinDist, float MaxDist, ZombieType Filter, bool IsBlacklist)
{
	bool DoFilter = Filter != -1;
	auto aZombie = mZombies.GetNext();
	float CurrentDist = 0;

	Zombie* ClosestZombie = nullptr;
	float SmallestDist = MaxDist;

	while (aZombie)
	{
		if (!DoFilter) goto Qualifies;
		if (IsBlacklist && aZombie->mZombieType == Filter) goto Skip;
		if (!IsBlacklist && aZombie->mZombieType != Filter) goto Skip;

	Qualifies:
		CurrentDist = aZombie->DistanceFrom(Point);
		if (CurrentDist > MaxDist) goto Skip;
		if (CurrentDist < MinDist) goto Skip;

		if (!ClosestZombie || (CurrentDist < SmallestDist))
		{
			ClosestZombie = aZombie;
			SmallestDist = CurrentDist;
		}

	Skip:
		aZombie = mZombies.GetNext(aZombie);
	}

	return ClosestZombie;
}

Pickup* Lawn::GetNearestPickup(FVector2 Point, float MinDist, float MaxDist, PickupType Filter, bool IsBlacklist)
{
	bool DoFilter = Filter != -1;
	auto aPickup = mPickups.GetNext();
	float CurrentDist = 0;

	Pickup* ClosestPickup = nullptr;
	float SmallestDist = MaxDist;

	while (aPickup)
	{
		if (!DoFilter) goto Qualifies;
		if (IsBlacklist && aPickup->mType == Filter) goto Skip;
		if (!IsBlacklist && aPickup->mType != Filter) goto Skip;

	Qualifies:
		CurrentDist = aPickup->DistanceFrom(Point);
		if (CurrentDist > MaxDist) goto Skip;
		if (CurrentDist < MinDist) goto Skip;

		if (!ClosestPickup || (CurrentDist < SmallestDist))
		{
			ClosestPickup = aPickup;
			SmallestDist = CurrentDist;
		}

	Skip:
		aPickup = mPickups.GetNext(aPickup);
	}

	return ClosestPickup;
}

Plant* Lawn::GetNearestPlant(FVector2 Point, float MinDist, float MaxDist, SeedType Filter, bool IsBlacklist)
{
	bool DoFilter = Filter != -1;
	auto aPlant = mPlants.GetNext();
	float CurrentDist = 0;

	Plant* ClosestPlant = nullptr;
	float SmallestDist = MaxDist;

	while (aPlant)
	{
		if (!DoFilter) goto Qualifies;
		if (IsBlacklist && aPlant->mType == Filter) goto Skip;
		if (!IsBlacklist && aPlant->mType != Filter) goto Skip;

	Qualifies:
		CurrentDist = aPlant->DistanceFrom(Point);
		if (CurrentDist > MaxDist) goto Skip;
		if (CurrentDist < MinDist) goto Skip;

		if (!ClosestPlant || (CurrentDist < SmallestDist))
		{
			ClosestPlant = aPlant;
			SmallestDist = CurrentDist;
		}

	Skip:
		aPlant = mPlants.GetNext(aPlant);
	}

	return ClosestPlant;
}

std::list<Projectile*> Lawn::GetProjectilesInArea(IRect Area, ProjectileType Type, bool IsBlacklist)
{
	bool DoFilter = Type != -1;
	auto List = std::list<Projectile*>();
	auto aItem = mProjectiles.GetNext();
	while (aItem)
	{
		if (!DoFilter) goto Qualify;
		if (IsBlacklist && aItem->mProjectileType == Type) goto Skip;
		if (!IsBlacklist && aItem->mProjectileType != Type) goto Skip;

	Qualify:
		if (Area.Contains(aItem->mHitbox.GetCenter()))
			List.push_back(aItem);

	Skip:
		aItem = mProjectiles.GetNext(aItem);
	}
	return List;
}

std::list<GridItem*> Lawn::GetGridItemsInArea(IRect Area, GridItemType Type, bool IsBlacklist)
{
	bool DoFilter = Type != -1;
	auto List = std::list<GridItem*>();
	auto aItem = mGridItems.GetNext();
	while (aItem)
	{
		if (!DoFilter) goto Qualify;
		if (IsBlacklist && aItem->mGridItemType == Type) goto Skip;
		if (!IsBlacklist && aItem->mGridItemType != Type) goto Skip;

	Qualify:
		if (Area.Contains(aItem->mPos))
			List.push_back(aItem);

	Skip:
		aItem = mGridItems.GetNext(aItem);
	}
	return List;
}

std::list<Zombie*> Lawn::GetZombiesInArea(IRect Area, ZombieType Type, bool IsBlacklist)
{
	bool DoFilter = Type != -1;
	auto List = std::list<Zombie*>();
	auto aItem = mZombies.GetNext();
	while (aItem)
	{
		if (!DoFilter) goto Qualify;
		if (IsBlacklist && aItem->mZombieType == Type) goto Skip;
		if (!IsBlacklist && aItem->mZombieType != Type) goto Skip;

	Qualify:
		if (Area.Contains(aItem->mHitbox.GetCenter()))
			List.push_back(aItem);

	Skip:
		aItem = mZombies.GetNext(aItem);
	}
	return List;
}

std::list<Pickup*> Lawn::GetPickupsInArea(IRect Area, PickupType Type, bool IsBlacklist)
{
	bool DoFilter = Type != -1;
	auto List = std::list<Pickup*>();
	auto aItem = mPickups.GetNext();
	while (aItem)
	{
		if (!DoFilter) goto Qualify;
		if (IsBlacklist && aItem->mType == Type) goto Skip;
		if (!IsBlacklist && aItem->mType != Type) goto Skip;

	Qualify:
		if (Area.Contains(aItem->mHitbox.GetCenter()))
			List.push_back(aItem);

	Skip:
		aItem = mPickups.GetNext(aItem);
	}
	return List;
}

std::list<Plant*> Lawn::GetPlantsInArea(IRect Area, SeedType Type, bool IsBlacklist)
{
	bool DoFilter = Type != -1;
	auto List = std::list<Plant*>();
	auto aItem = mPlants.GetNext();
	while (aItem)
	{
		if (!DoFilter) goto Qualify;
		if (IsBlacklist && aItem->mType == Type) goto Skip;
		if (!IsBlacklist && aItem->mType != Type) goto Skip;

	Qualify:
		if (Area.Contains(aItem->mHitbox.GetCenter()))
			List.push_back(aItem);

	Skip:
		aItem = mPlants.GetNext(aItem);
	}
	return List;
}

GridItem* Lawn::GetGridItemAt(int Col, int Row, GridItemType Type)
{
	auto aItem = mGridItems.GetNext();
	while (aItem)
	{
		if (aItem->mCol != Col) goto Skip;
		if (aItem->mRow != Row) goto Skip;
		if (Type == GRIDITEM_NONE) return aItem;
		if (aItem->mGridItemType == Type) return aItem;

	Skip:
		aItem = mGridItems.GetNext(aItem);
	}

	return nullptr;
}

Plant* Lawn::GetPlantAt(int Col, int Row, SeedType Type)
{
	auto aPlant = mPlants.GetNext();
	while (aPlant)
	{
		if (aPlant->mCol != Col) goto Skip;
		if (aPlant->mRow != Row) goto Skip;
		if (Type == SEED_NONE) return aPlant;
		if (aPlant->mType == Type) return aPlant;

	Skip:
		aPlant = mPlants.GetNext(aPlant);
	}

	return nullptr;
}

int Lawn::CountPlants(SeedType Filter)
{
	int Count = 0;
	auto aPlant = mPlants.GetNext();
	while (aPlant)
	{
		Count += (Filter == SEED_NONE) || (aPlant->mType == Filter);
		aPlant = mPlants.GetNext(aPlant);
	}
	return Count;
}

Plant* Lawn::PlantHitTest(int X, int Y)
{
	HitResult aRes;
	PlantHitTest(X, Y, &aRes);
	return (Plant*)aRes.aObject;
}

GridItem* Lawn::GridItemHitTest(int X, int Y)
{
	auto aItem = mGridItems.GetNext();
	GridItem* aRes = nullptr;
	int aResRenderOrder = -RENDER_ITEM_GRID_ITEM;
	while (aItem)
	{
		auto aHitbox = GridToPixelArea(aItem->mCol, aItem->mRow, 1, 1);
		if (!aHitbox.Contains(Sexy::IVector2(X, Y))) goto Skip;
		if (aRes == nullptr || (aResRenderOrder < aItem->mRenderOrder))
		{
			aRes = aItem;
			aResRenderOrder = aItem->mRenderOrder;
		}

	Skip:
		aItem = mGridItems.GetNext(aItem);
	}

	return aRes;
}

#pragma region Base Functions
__declspec(naked) void __stdcall ConstructLawn(Lawn*, LawnApp*)
{
	__asm
	{
		mov ecx, [esp + 0x8]
		push [esp + 0x4]
		mov eax, 0x407B50
		call eax
		ret 0x8
	}
}
Lawn::Lawn(LawnApp* aApp)
{
	ConstructLawn(this, aApp);
}

__declspec(naked) void Lawn::Dispose()
{
	__asm
	{
		push esi
		mov esi, ecx
		mov ecx, 0x408A70
		call ecx
		pop esi
		ret
	}
}
__declspec(naked) bool Lawn::AreEnemiesOnScreen()
{
	__asm
	{
		mov edx, ecx
		mov ecx, 0x408B00
		jmp ecx
	}
}
__declspec(naked) int Lawn::CountEnemiesOnScreen()
{
	__asm
	{
		push ebx
		mov ebx, ecx
		mov ecx, 0x408B60
		call ecx
		pop ebx
		ret
	}
}
__declspec(naked) int Lawn::CountLawnMowers()
{
	__asm
	{
		mov edx, ecx
		mov ecx, 0x408BF0
		jmp ecx
	}
}
__declspec(naked) void Lawn::TrySaveGame()
{
	__asm
	{
		pop edx// ret
		push ecx
		push edx
		mov edx, 0x408C30
		jmp edx
	}
}
__declspec(naked) bool Lawn::NeedSaveGame()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x408DA0
		jmp ecx
	}
}
__declspec(naked) bool Lawn::LoadGame(PopString& FileName)
{
	__asm
	{
		push edi
		mov edi, ecx
		mov eax, [esp + 0x8]
		mov ecx, 0x408DE0
		call ecx
		pop edi
		ret 0x4
	}
}
__declspec(naked) GridItem* Lawn::GetRake()
{
	__asm
	{
		mov edx, ecx
		mov ecx, 0x408E90
		jmp ecx
	}
}
__declspec(naked) bool Lawn::CanAddGraveAt(int, int)
{
	__asm
	{
		push ebx
		push edi

		mov edx, ecx
		mov edi, [esp + 0x0C]
		mov ebx, [esp + 0x10]
		mov ecx, 0x408ED0
		call ecx

		pop edi
		pop ebx
		ret 0x8
	}
}
__declspec(naked) int Lawn::GetNumWavesPerFlag()
{
	__asm
	{
		mov eax, 0x409050
		jmp eax
	}
}
__declspec(naked) bool Lawn::IsFlagWave(int)
{
	__asm
	{
		mov edx, ecx
		mov ecx, 0x409080
		jmp ecx
	}
}
__declspec(naked) void Lawn::LoadBackground()
{
	__asm
	{
		push esi
		mov esi, ecx
		mov ecx, 0x40A160
		call ecx
		pop esi
		ret
	}
}
__declspec(naked) void Lawn::PickBackground()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x40A550
		jmp ecx
	}
}
__declspec(naked) void Lawn::InitZombieWavesForLevel(int)
{
	__asm
	{
		push edi
		mov edi, ecx
		mov edx, [esp + 0x8]
		mov ecx, 0x40AB10
		call ecx
		pop edi
		ret 0x4
	}
}
__declspec(naked) void Lawn::InitZombieWaves()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x40ABB0
		jmp ecx
	}
}
__declspec(naked) void Lawn::SetEffectsPlaying(bool)
{
	__asm
	{
		push ebx
		push edi

		mov edi, ecx
		mov ebx, [esp + 0xC]
		mov ecx, 0x40ACB0
		call ecx

		pop edi
		pop ebx
		ret 0x4
	}
}
__declspec(naked) void Lawn::InitSurvivalStage()
{
	__asm
	{
		pop eax
		push ecx
		push eax
		mov ecx, 0x40AD60
		jmp ecx
	}
}
__declspec(naked) int Lawn::GetLevelRandSeed()
{
	__asm
	{
		mov eax, 0x40A110
		jmp eax
	}
}
__declspec(naked) void Lawn::GetShovelButtonRect(Sexy::IRect*)
{
	__asm
	{
		mov edx, ecx
		mov eax, [esp + 0x4]
		mov ecx, 0x40AE70
		jmp ecx
	}
}
__declspec(naked) void Lawn::GetZenButtonRect(GameObjectType, Sexy::IRect*)
{
	__asm
	{
		push edi

		mov edi, [esp + 0xC]
		push [esp + 0x8]
		push ecx
		mov ecx, 0x40AF00
		call ecx

		pop edi
		ret 0x8
	}
}
__declspec(naked) void Lawn::InitLevel()
{
	__asm
	{
		pop eax
		push ecx
		push eax
		mov eax, 0x40AF90
		jmp eax
	}
}
__declspec(naked) void Lawn::PlaceRake()
{
	__asm
	{
		pop eax
		push ecx
		push eax
		mov eax, 0x40B9C0
		jmp eax
	}
}
__declspec(naked) void Lawn::InitLawnMowers()
{
	__asm
	{
		pop eax
		push ecx
		push eax
		mov eax, 0x40BC70
		jmp eax
	}
}
__declspec(naked) bool Lawn::ChooseSeedsForLevel()
{
	__asm
	{
		push edi
		mov edi, ecx
		mov ecx, 0x40BD30
		call ecx
		pop edi
		ret
	}
}
__declspec(naked) void Lawn::StartLevel()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x40BE00
		jmp ecx
	}
}
__declspec(naked) void Lawn::FadeOutLevel()
{
	__asm
	{
		mov eax, 0x40C3E0
		jmp eax
	}
}
__declspec(naked) bool Lawn::IsPlantEquipped()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x40CCE0
		jmp ecx
	}
}
__declspec(naked) SeedType Lawn::GetEquippedPlantType()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x40CD10
		jmp ecx
	}
}
__declspec(naked) void Lawn::RefreshEquippedSeed()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x40CD80
		jmp ecx
	}
}
constexpr unsigned int ISPOOLCELL = 0x40CE00;
__declspec(naked) bool Lawn::IsPoolCell(int, int)
{
	__asm
	{
		mov edx, ecx
		mov eax, [esp + 0x4]
		mov ecx, [esp + 0x8]
		call ISPOOLCELL
		ret 0x8
	}
}
constexpr unsigned int DOPLANTINGEFFECTS = 0x40CE60;
__declspec(naked) bool __stdcall Lawn::CanZombieSpawnOnLevel(ZombieType, int)
{
	__asm
	{
		pop ecx// ret
		pop eax
		pop edx
		push ecx
		mov ecx, 0x40D660
		jmp ecx
	}
}
__declspec(naked) ZombieType Lawn::GetIntroducedZombieType()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x40D6F0
		jmp ecx
	}
}
__declspec(naked) bool Lawn::LaneCanHaveZombie(int, ZombieType)
{
	__asm
	{
		push esi
		mov esi, ecx
		push [esp + 0x8]
		push [esp + 0x8]
		mov ecx, 0x40DB20
		call ecx
		pop esi
		ret 0x8
	}
}
__declspec(naked) int Lawn::PickLaneForNewZombie(ZombieType)
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x40DC50
		jmp ecx
	}
}
__declspec(naked) bool Lawn::CanAddBobsled()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x40DD90
		jmp ecx
	}
}
__declspec(naked) void Lawn::RemoveAllZombies()
{
	__asm
	{
		push edi
		mov edi, ecx
		mov ecx, 0x40DEA0
		call ecx
		pop edi
		ret
	}
}
#pragma endregion

#pragma region Autogen Functions
constexpr unsigned int LAWN_REMOVEZOMBIESFORREPICK = 0x40DF00;
__declspec(naked) void Lawn::RemoveZombiesForRepick()
{
	__asm
	{
		push edi

		mov edi, ecx
		call LAWN_REMOVEZOMBIESFORREPICK

		pop edi
		ret 0x0
	}
}

constexpr unsigned int LAWN_REMOVECUTSCENEZOMBIES = 0x40DF70;
__declspec(naked) void Lawn::RemoveCutsceneZombies()
{
	__asm
	{
		push ebx

		mov ebx, ecx
		call LAWN_REMOVECUTSCENEZOMBIES

		pop ebx
		ret 0x0
	}
}

constexpr unsigned int LAWN_PICKZOMBIEWAVES = 0x4092E0;
__declspec(naked) void Lawn::PickZombieWaves()
{
	__asm
	{
		push edi

		mov edi, ecx
		call LAWN_PICKZOMBIEWAVES

		pop edi
		ret 0x0
	}
}

constexpr unsigned int LAWN_CANPLANTAT = 0x40E020;
__declspec(naked) bool Lawn::CanPlantAt(int, int, SeedType)
{
	__asm
	{

		push[esp + 0xC]
		push[esp + 0xC]
		mov eax, [esp + 0xC]
		push ecx
		call LAWN_CANPLANTAT

		ret 0xC
	}
}

constexpr unsigned int LAWN_ISICEAT = 0x40DFC0;
__declspec(naked) bool Lawn::IsIceCell(int, int)
{
	__asm
	{
		push esi

		mov eax, [esp + 0xC]
		push[esp + 0x8]
		mov esi, ecx
		call LAWN_ISICEAT

		pop esi
		ret 0x8
	}
}

constexpr unsigned int LAWN_ZOMBIEHITTEST = 0x40E780;
__declspec(naked) Zombie* Lawn::ZombieHitTest(int, int)
{
	__asm
	{

		push[esp + 0x8]
		push[esp + 0x8]
		push ecx
		call LAWN_ZOMBIEHITTEST

		ret 0x8
	}
}

constexpr unsigned int LAWN_HIGHLIGHTPLANTSFORMOUSE = 0x40E940;
__declspec(naked) void Lawn::HighlightPlantsForMouse(int, int)
{
	__asm
	{
		push edi

		push[esp + 0xC]
		push[esp + 0xC]
		mov edi, ecx
		call LAWN_HIGHLIGHTPLANTSFORMOUSE

		pop edi
		ret 0x8
	}
}

constexpr unsigned int LAWN_SPECIALPLANTHITTEST = 0x411280;
__declspec(naked) Plant* Lawn::SpecialPlantHitTest(int, int)
{
	__asm
	{
		push edi

		push[esp + 0xC]
		push[esp + 0xC]
		mov edi, ecx
		call LAWN_SPECIALPLANTHITTEST

		pop edi
		ret 0x8
	}
}

constexpr unsigned int LAWN_MOUSEHITTESTPLANT = 0x411470;
__declspec(naked) void Lawn::PlantHitTest(int, int, HitResult*)
{
	__asm
	{
		push esi

		push[esp + 0x10]
		push[esp + 0x10]
		push[esp + 0x10]
		mov esi, ecx
		call LAWN_MOUSEHITTESTPLANT

		pop esi
		ret 0xC
	}
}

constexpr unsigned int LAWN_MOUSEHITTEST = 0x411730;
__declspec(naked) void Lawn::MouseHitTest(int, int, HitResult*)
{
	__asm
	{

		push[esp + 0xC]
		push[esp + 0xC]
		push[esp + 0xC]
		push ecx
		call LAWN_MOUSEHITTEST

		ret 0xC
	}
}

constexpr unsigned int LAWN_PICKUPTOOL = 0x411C10;
__declspec(naked) void Lawn::PickUpTool(GameObjectType)
{
	__asm
	{
		push ebx

		mov edx, [esp + 0x8]
		mov ebx, ecx
		call LAWN_PICKUPTOOL

		pop ebx
		ret 0x4
	}
}

constexpr unsigned int LAWN_CLEARCURSOR = 0x412330;
__declspec(naked) void Lawn::ClearCursor()
{
	__asm
	{
		push edi

		mov edi, ecx
		call LAWN_CLEARCURSOR

		pop edi
		ret 0x0
	}
}

constexpr unsigned int LAWN_CANINTERACTWITHLAWNBUTTONS = 0x412490;
__declspec(naked) bool Lawn::CanInteractWithButtons()
{
	__asm
	{
		push esi

		mov esi, ecx
		call LAWN_CANINTERACTWITHLAWNBUTTONS

		pop esi
		ret 0x0
	}
}

constexpr unsigned int LAWN_PAUSE = 0x4127A0;
__declspec(naked) void Lawn::SetPause(bool)
{
	__asm
	{
		push al

		mov al, [esp + 0x8]
		mov ecx, ecx
		call LAWN_PAUSE

		pop al
		ret 0x4
	}
}

constexpr unsigned int LAWN_PICKSPECIALGRAVESTONE = 0x412890;
__declspec(naked) void Lawn::PickSpecialGraveStone()
{
	__asm
	{

		mov edx, ecx
		call LAWN_PICKSPECIALGRAVESTONE

		ret 0x0
	}
}

constexpr unsigned int LAWN_TOTALZOMBIESHEALTHINWAVE = 0x412E30;
__declspec(naked) int Lawn::GetWaveHealth(int)
{
	__asm
	{
		push ebx

		push[esp + 0x8]
		mov ebx, ecx
		call LAWN_TOTALZOMBIESHEALTHINWAVE

		pop ebx
		ret 0x4
	}
}

constexpr unsigned int LAWN_SPAWNZOMBIEWAVE = 0x412EE0;
__declspec(naked) void Lawn::SpawnNextWave()
{
	__asm
	{
		push edi

		mov edi, ecx
		call LAWN_SPAWNZOMBIEWAVE

		pop edi
		ret 0x0
	}
}

constexpr unsigned int LAWN_STOPALLZOMBIESOUNDS = 0x413220;
__declspec(naked) void Lawn::StopZombieSounds()
{
	__asm
	{
		push edi

		mov edi, ecx
		call LAWN_STOPALLZOMBIESOUNDS

		pop edi
		ret 0x0
	}
}

constexpr unsigned int LAWN_GETSURVIVALFLAGSCOMPLETED = 0x413260;
__declspec(naked) int Lawn::GetSurvivalFlagsCompleted()
{
	__asm
	{
		push esi

		mov esi, ecx
		call LAWN_GETSURVIVALFLAGSCOMPLETED

		pop esi
		ret 0x0
	}
}

constexpr unsigned int LAWN_ZOMBIESWON = 0x413400;
__declspec(naked) void Lawn::ZombiesWon(Zombie*)
{
	__asm
	{
		pop eax
		push ecx
		push eax

		jmp LAWN_ZOMBIESWON
	}
}

constexpr unsigned int LAWN_ISFINALSCARYPOTTERSTAGE = 0x4138D0;
__declspec(naked) bool Lawn::IsFinalScaryPotterStage()
{
	__asm
	{

		mov edx, ecx
		call LAWN_ISFINALSCARYPOTTERSTAGE

		ret 0x0
	}
}

constexpr unsigned int LAWN_ISFINALSURVIVALSTAGE = 0x413920;
__declspec(naked) bool Lawn::IsFinalSurvivalStage()
{
	__asm
	{
		push edi

		mov edi, ecx
		call LAWN_ISFINALSURVIVALSTAGE

		pop edi
		ret 0x0
	}
}

constexpr unsigned int LAWN_ISSURVIVALSTAGEWITHREPICK = 0x4139E0;
__declspec(naked) bool Lawn::IsSurvivalStageWithRepick()
{
	__asm
	{

		mov eax, ecx
		call LAWN_ISSURVIVALSTAGEWITHREPICK

		ret 0x0
	}
}

constexpr unsigned int LAWN_ISLASTSTANDSTAGEWITHREPICK = 0x413A10;
__declspec(naked) bool Lawn::IsLastStandStageWithRepick()
{
	__asm
	{

		mov eax, ecx
		call LAWN_ISLASTSTANDSTAGEWITHREPICK

		ret 0x0
	}
}

constexpr unsigned int LAWN_HASLEVELAWARDDROPPED = 0x413A40;
__declspec(naked) bool Lawn::LevelAwardDropped()
{
	__asm
	{

		mov eax, ecx
		call LAWN_HASLEVELAWARDDROPPED

		ret 0x0
	}
}

constexpr unsigned int LAWN_UPDATESUNSPAWNING = 0x413A70;
__declspec(naked) void Lawn::UpdateSunSkyfall()
{
	__asm
	{
		push esi

		mov esi, ecx
		call LAWN_UPDATESUNSPAWNING

		pop esi
		ret 0x0
	}
}

constexpr unsigned int LAWN_UPDATEZOMBIESPAWNING = 0x413D00;
__declspec(naked) void Lawn::UpdateZombieSpawning()
{
	__asm
	{

		mov ecx, ecx
		call LAWN_UPDATEZOMBIESPAWNING

		ret 0x0
	}
}

constexpr unsigned int LAWN_UPDATEICE = 0x414100;
__declspec(naked) void Lawn::UpdateIce()
{
	__asm
	{

		push ecx
		call LAWN_UPDATEICE

		ret 0x0
	}
}

constexpr unsigned int LAWN_UPDATEPROGRESSMETER = 0x414270;
__declspec(naked) void Lawn::UpdateProgressMeter()
{
	__asm
	{

		mov eax, ecx
		call LAWN_UPDATEPROGRESSMETER

		ret 0x0
	}
}

constexpr unsigned int LAWN_ROWCANHAVEZOMBIES = 0x416110;
__declspec(naked) bool Lawn::CanSpawnZombiesInLane(int)
{
	__asm
	{

		mov eax, [esp + 0x4]
		mov ecx, ecx
		call LAWN_ROWCANHAVEZOMBIES

		ret 0x4
	}
}

constexpr unsigned int LAWN_DRAWICE = 0x416140;
__declspec(naked) void Lawn::DrawIce(Sexy::Graphics*, int)
{
	__asm
	{

		mov eax, [esp + 0x8]
		push[esp + 0x4]
		mov ecx, ecx
		call LAWN_DRAWICE

		ret 0x8
	}
}

constexpr unsigned int LAWN_DRAWBACKDROP = 0x416290;
__declspec(naked) void Lawn::DrawBackground(Sexy::Graphics*)
{
	__asm
	{

		push[esp + 0x4]
		push ecx
		call LAWN_DRAWBACKDROP

		ret 0x4
	}
}

constexpr unsigned int LAWN_HASPROGRESSMETER = 0x4173C0;
__declspec(naked) bool Lawn::HasProgressMeter()
{
	__asm
	{

		mov edx, ecx
		call LAWN_HASPROGRESSMETER

		ret 0x0
	}
}

constexpr unsigned int LAWN_PROGRESSMETERHASFLAGS = 0x417450;
__declspec(naked) bool Lawn::ProgressMeterHasFlags()
{
	__asm
	{

		mov edx, ecx
		call LAWN_PROGRESSMETERHASFLAGS

		ret 0x0
	}
}

constexpr unsigned int LAWN_DRAWPROGRESSMETER = 0x417500;
__declspec(naked) void Lawn::DrawProgressMeter(Sexy::Graphics*)
{
	__asm
	{

		push[esp + 0x4]
		push ecx
		call LAWN_DRAWPROGRESSMETER

		ret 0x4
	}
}

constexpr unsigned int LAWN_DRAWHOUSEDOORBOTTOM = 0x417C80;
__declspec(naked) void Lawn::DrawHouseDoorBottom(Sexy::Graphics*)
{
	__asm
	{

		mov eax, [esp + 0x4]
		mov ecx, ecx
		call LAWN_DRAWHOUSEDOORBOTTOM

		ret 0x4
	}
}

constexpr unsigned int LAWN_DRAWHOUSEDOORTOP = 0x417CF0;
__declspec(naked) void Lawn::DrawHouseDoorTop(Sexy::Graphics*)
{
	__asm
	{

		mov eax, [esp + 0x4]
		mov ecx, ecx
		call LAWN_DRAWHOUSEDOORTOP

		ret 0x4
	}
}

constexpr unsigned int LAWN_DRAWZENWHEELBARROWBUTTON = 0x4182D0;
__declspec(naked) void Lawn::DrawZenWheelBarrowButton(Sexy::Graphics*, int)
{
	__asm
	{

		push[esp + 0x8]
		push[esp + 0x8]
		push ecx
		call LAWN_DRAWZENWHEELBARROWBUTTON

		ret 0x8
	}
}

constexpr unsigned int LAWN_DRAWZENBUTTONS = 0x418500;
__declspec(naked) void Lawn::DrawZenButtons(Sexy::Graphics*)
{
	__asm
	{

		push[esp + 0x4]
		push ecx
		call LAWN_DRAWZENBUTTONS

		ret 0x4
	}
}

constexpr unsigned int LAWN_DRAWSHOVEL = 0x418B70;
__declspec(naked) void Lawn::DrawShovel(Sexy::Graphics*)
{
	__asm
	{

		push[esp + 0x4]
		push ecx
		call LAWN_DRAWSHOVEL

		ret 0x4
	}
}

constexpr unsigned int LAWN_DRAWDEBUGTEXT = 0x418C70;
__declspec(naked) void Lawn::DrawDebugText(Sexy::Graphics*)
{
	__asm
	{
		push edi

		push[esp + 0x8]
		mov edi, ecx
		call LAWN_DRAWDEBUGTEXT

		pop edi
		ret 0x4
	}
}

constexpr unsigned int LAWN_DRAWDEBUGOBJECTRECTS = 0x419AE0;
__declspec(naked) void Lawn::DrawObjectRects(Sexy::Graphics*)
{
	__asm
	{

		push[esp + 0x4]
		push ecx
		call LAWN_DRAWDEBUGOBJECTRECTS

		ret 0x4
	}
}

constexpr unsigned int LAWN_DRAWFADEOUT = 0x419EB0;
__declspec(naked) void Lawn::DrawFadeOut(Sexy::Graphics*)
{
	__asm
	{
		push ebx

		mov ebx, [esp + 0x8]
		mov eax, ecx
		call LAWN_DRAWFADEOUT

		pop ebx
		ret 0x4
	}
}

constexpr unsigned int LAWN_DRAWTOPRIGHTUI = 0x419F60;
__declspec(naked) void Lawn::DrawTopRightUI(Sexy::Graphics*)
{
	__asm
	{
		push ebx

		push[esp + 0x8]
		mov ebx, ecx
		call LAWN_DRAWTOPRIGHTUI

		pop ebx
		ret 0x4
	}
}

constexpr unsigned int LAWN_DRAWUIBOTTOM = 0x41A0A0;
__declspec(naked) void Lawn::DrawBottomUI(Sexy::Graphics*)
{
	__asm
	{
		push edi

		mov edi, [esp + 0x8]
		push ecx
		call LAWN_DRAWUIBOTTOM

		pop edi
		ret 0x4
	}
}

constexpr unsigned int LAWN_DRAWUICOINBANK = 0x41A2A0;
__declspec(naked) void Lawn::DrawCoinBank(Sexy::Graphics*)
{
	__asm
	{
		push edi

		mov edi, [esp + 0x8]
		push ecx
		call LAWN_DRAWUICOINBANK

		pop edi
		ret 0x4
	}
}

constexpr unsigned int LAWN_CLEARFOGAROUNDPLANT = 0x41A430;
__declspec(naked) void Lawn::ClearFogAroundPlant(Plant*, int)
{
	__asm
	{
		push ebx

		mov ebx, [esp + 0xC]
		push[esp + 0x8]
		push ecx
		call LAWN_CLEARFOGAROUNDPLANT

		pop ebx
		ret 0x8
	}
}

constexpr unsigned int LAWN_UPDATEFOG = 0x41A5D0;
__declspec(naked) void Lawn::UpdateFog()
{
	__asm
	{

		push ecx
		call LAWN_UPDATEFOG

		ret 0x0
	}
}

constexpr unsigned int LAWN_DRAWFOG = 0x41A730;
__declspec(naked) void Lawn::DrawFog(Sexy::Graphics*)
{
	__asm
	{

		push [esp + 0x4]
		push ecx
		call LAWN_DRAWFOG

		ret 0x4
	}
}

constexpr unsigned int LAWN_DRAWUITOP = 0x41AA40;
__declspec(naked) void Lawn::DrawTopUI(Sexy::Graphics*)
{
	__asm
	{

		push[esp + 0x4]
		push ecx
		call LAWN_DRAWUITOP

		ret 0x4
	}
}

constexpr unsigned int LAWN_SETMUSTACHEMODE = 0x41AE60;
__declspec(naked) void Lawn::SetMustacheMode(bool)
{
	__asm
	{
		push bl
		push edi

		mov bl, [esp + 0xC]
		mov edi, ecx
		call LAWN_SETMUSTACHEMODE

		pop edi
		pop bl
		ret 0x4
	}
}

constexpr unsigned int LAWN_SETFUTUREMODE = 0x41AF00;
__declspec(naked) void Lawn::SetFutureMode(bool)
{
	__asm
	{
		push bl
		push edi

		mov bl, [esp + 0xC]
		mov edi, ecx
		call LAWN_SETFUTUREMODE

		pop edi
		pop bl
		ret 0x4
	}
}

constexpr unsigned int LAWN_SETPINATAMODE = 0x41AF60;
__declspec(naked) void Lawn::SetPinataMode(bool)
{
	__asm
	{
		push bl
		push esi

		mov bl, [esp + 0xC]
		mov esi, ecx
		call LAWN_SETPINATAMODE

		pop esi
		pop bl
		ret 0x4
	}
}

constexpr unsigned int LAWN_SETDANCEMODE = 0x41AFD0;
__declspec(naked) void Lawn::SetDanceMode(bool)
{
	__asm
	{
		push bl

		mov bl, [esp + 0x8]
		push ecx
		call LAWN_SETDANCEMODE

		pop bl
		ret 0x4
	}
}

constexpr unsigned int LAWN_SETSUPERMOWERMODE = 0x41B0D0;
__declspec(naked) void Lawn::SetSuperMowerMode(bool)
{
	__asm
	{
		push bl
		push edi

		mov bl, [esp + 0xC]
		mov edi, ecx
		call LAWN_SETSUPERMOWERMODE

		pop edi
		pop bl
		ret 0x4
	}
}

constexpr unsigned int LAWN_ADDSUNMONEY = 0x41B960;
__declspec(naked) void Lawn::AddSun(int)
{
	__asm
	{

		mov eax, ecx
		mov ecx, [esp + 0x4]
		call LAWN_ADDSUNMONEY

		ret 0x4
	}
}

constexpr unsigned int LAWN_COUNTSUNBEINGCOLLECTED = 0x41B980;
__declspec(naked) int Lawn::GetSunBeingCollected()
{
	__asm
	{

		mov edx, ecx
		call LAWN_COUNTSUNBEINGCOLLECTED

		ret 0x0
	}
}

constexpr unsigned int LAWN_COUNTCOINSBEINGCOLLECTED = 0x41B9F0;
__declspec(naked) int Lawn::GetCoinsBeingCollected()
{
	__asm
	{

		mov edx, ecx
		call LAWN_COUNTCOINSBEINGCOLLECTED

		ret 0x0
	}
}

constexpr unsigned int LAWN_TAKESUNMONEY = 0x41BA60;
__declspec(naked) bool Lawn::TakeSun(int)
{
	__asm
	{
		push ebx
		push edi

		mov ebx, [esp + 0xC]
		mov edi, ecx
		call LAWN_TAKESUNMONEY

		pop edi
		pop ebx
		ret 0x4
	}
}

constexpr unsigned int LAWN_CANTAKESUNMONEY = 0x41BAB0;
__declspec(naked) bool Lawn::CanTakeSun(int)
{
	__asm
	{

		push[esp + 0x4]
		mov edx, ecx
		call LAWN_CANTAKESUNMONEY

		ret 0x4
	}
}

constexpr unsigned int LAWN_ISCONVEYORBELTLEVEL = 0x41BE50;
__declspec(naked) bool Lawn::IsConveyorBeltLevel()
{
	__asm
	{

		mov eax, ecx
		call LAWN_ISCONVEYORBELTLEVEL

		ret 0x0
	}
}

constexpr unsigned int LAWN_GETNUMSEEDSINBANK = 0x41BEE0;
__declspec(naked) int Lawn::GetNumSeedsInBank()
{
	__asm
	{
		push edi

		mov edi, ecx
		call LAWN_GETNUMSEEDSINBANK

		pop edi
		ret 0x0
	}
}

constexpr unsigned int LAWN_STAGEISNIGHT = 0x41C010;
__declspec(naked) bool Lawn::IsNightStage()
{
	__asm
	{

		mov eax, ecx
		call LAWN_STAGEISNIGHT

		ret 0x0
	}
}

constexpr unsigned int LAWN_STAGEHASGRAVESTONES = 0x41C040;
__declspec(naked) bool Lawn::StageHasGraves()
{
	__asm
	{

		mov edx, ecx
		call LAWN_STAGEHASGRAVESTONES

		ret 0x0
	}
}

constexpr unsigned int LAWN_STAGEHASROOF = 0x41C0B0;
__declspec(naked) bool Lawn::StageHasRoof()
{
	__asm
	{

		mov eax, ecx
		call LAWN_STAGEHASROOF

		ret 0x0
	}
}

constexpr unsigned int LAWN_STAGEHASPOOL = 0x41C0D0;
__declspec(naked) bool Lawn::StageHasPool()
{
	__asm
	{

		mov eax, ecx
		call LAWN_STAGEHASPOOL

		ret 0x0
	}
}

constexpr unsigned int LAWN_STAGEHASZOMBIEWALKINFROMRIGHT = 0x41C0F0;
__declspec(naked) bool Lawn::StageHasZombiesWalkInFromRight()
{
	__asm
	{

		mov eax, ecx
		call LAWN_STAGEHASZOMBIEWALKINFROMRIGHT

		ret 0x0
	}
}

constexpr unsigned int LAWN_STAGEHASFOG = 0x41C170;
__declspec(naked) bool Lawn::StageHasFog()
{
	__asm
	{

		mov edx, ecx
		call LAWN_STAGEHASFOG

		ret 0x0
	}
}

constexpr unsigned int LAWN_LEFTFOGCOLUMN = 0x41C1C0;
__declspec(naked) int Lawn::LeftFogColumn()
{
	__asm
	{

		mov ecx, ecx
		call LAWN_LEFTFOGCOLUMN

		ret 0x0
	}
}

constexpr unsigned int LAWN_GETSEEDPACKETPOSITIONX = 0x41C210;
__declspec(naked) int Lawn::GetSeedPacketXPosition(int)
{
	__asm
	{
		push edi

		mov edi, [esp + 0x8]
		mov eax, ecx
		call LAWN_GETSEEDPACKETPOSITIONX

		pop edi
		ret 0x4
	}
}

constexpr unsigned int LAWN_GETSEEDBANKEXTRAWIDTH = 0x41C290;
__declspec(naked) int Lawn::GetSeedBankExtraWidth()
{
	__asm
	{

		mov eax, ecx
		call LAWN_GETSEEDBANKEXTRAWIDTH

		ret 0x0
	}
}

constexpr unsigned int LAWN_SEEDNOTRECOMMENDEDFORLEVEL = 0x41CC60;
__declspec(naked) bool Lawn::SeedNotRecommendedForLevel(SeedType)
{
	__asm
	{
		push esi

		mov esi, [esp + 0x8]
		mov edx, ecx
		call LAWN_SEEDNOTRECOMMENDEDFORLEVEL

		pop esi
		ret 0x4
	}
}

constexpr unsigned int LAWN_PLANTINGREQUIREMENTSMET = 0x41D7D0;
__declspec(naked) bool Lawn::PlantingRequirementsMet(SeedType)
{
	__asm
	{

		mov eax, [esp + 0x4]
		mov edx, ecx
		call LAWN_PLANTINGREQUIREMENTSMET

		ret 0x4
	}
}

constexpr unsigned int LAWN_FINDUNBRELLAPLANT = 0x41D3D0;
__declspec(naked) Plant* Lawn::FindUmbrellaPlant(int, int)
{
	__asm
	{
		push edi
		push ebx

		mov edi, [esp + 0x10]
		mov ebx, [esp + 0xC]
		mov edx, ecx
		call LAWN_FINDUNBRELLAPLANT

		pop ebx
		pop edi
		ret 0x8
	}
}

constexpr unsigned int LAWN_DOFWOOSH = 0x41D450;
__declspec(naked) void Lawn::DoFwoosh(int)
{
	__asm
	{
		push ebx

		push[esp + 0x8]
		mov ebx, ecx
		call LAWN_DOFWOOSH

		pop ebx
		ret 0x4
	}
}

constexpr unsigned int LAWN_UPDATEFWOOSH = 0x41D630;
__declspec(naked) void Lawn::UpdateFwoosh()
{
	__asm
	{
		push ebx

		mov ebx, ecx
		call LAWN_UPDATEFWOOSH

		pop ebx
		ret 0x0
	}
}

constexpr unsigned int LAWN_GETNUMWAVESPERSURVIVALSTAGE = 0x41DA10;
__declspec(naked) int Lawn::GetNumWavesPerSurvivalStage()
{
	__asm
	{

		mov eax, ecx
		call LAWN_GETNUMWAVESPERSURVIVALSTAGE

		ret 0x0
	}
}

constexpr unsigned int LAWN_REMOVEPARTICLESYSTEMBYTYPE = 0x41DA50;
__declspec(naked) void Lawn::RemoveParticleSystemByType(ParticleEffect)
{
	__asm
	{
		push edi
		push ebx

		mov edi, [esp + 0xC]
		mov ebx, ecx
		call LAWN_REMOVEPARTICLESYSTEMBYTYPE

		pop ebx
		pop edi
		ret 0x4
	}
}

constexpr unsigned int LAWN_PLANTUSESACCELERATEDPRICING = 0x41DA90;
__declspec(naked) bool Lawn::PlantUsesAcceleratedPricing(SeedType)
{
	__asm
	{

		mov eax, [esp + 0x4]
		push ecx
		call LAWN_PLANTUSESACCELERATEDPRICING

		ret 0x4
	}
}

constexpr unsigned int LAWN_GETCURRENTPLANTCOST = 0x41DAE0;
__declspec(naked) int Lawn::GetCurrentPlantCost(SeedType, SeedType)
{
	__asm
	{
		push edi

		mov edx, [esp + 0xC]
		mov eax, [esp + 0x8]
		mov edi, ecx
		call LAWN_GETCURRENTPLANTCOST

		pop edi
		ret 0x8
	}
}

constexpr unsigned int LAWN_UPDATEMOUSEPOSITION = 0x40EAB0;
__declspec(naked) void Lawn::UpdateMousePosition()
{
	__asm
	{

		mov eax, ecx
		call LAWN_UPDATEMOUSEPOSITION

		ret 0x0
	}
}

constexpr unsigned int LAWN_UPDATETOOLTIP = 0x40EF00;
__declspec(naked) void Lawn::UpdateToolTip()
{
	__asm
	{

		push ecx
		call LAWN_UPDATETOOLTIP

		ret 0x0
	}
}

constexpr unsigned int LAWN_MOUSEDOWNCOBCANNONFIRE = 0x40FC70;
__declspec(naked) void Lawn::MouseDownCobcannonFire(int, int, ClickCode)
{
	__asm
	{

		push[esp + 0xC]
		push[esp + 0xC]
		push[esp + 0xC]
		mov eax, ecx
		call LAWN_MOUSEDOWNCOBCANNONFIRE

		ret 0xC
	}
}

constexpr unsigned int LAWN_MOUSEDOWNWITHPLANT = 0x40FD30;
__declspec(naked) void Lawn::MouseDownWithPlant(int, int, ClickCode)
{
	__asm
	{

		mov eax, [esp + 0xC]
		push[esp + 0x8]
		push[esp + 0x8]
		push ecx
		mov ecx, eax
		call LAWN_MOUSEDOWNWITHPLANT

		ret 0xC
	}
}

constexpr unsigned int LAWN_MOUSEDOWNWITHTOOL = 0x411060;
__declspec(naked) void Lawn::MouseDownWithTool(int, int, ClickCode, CursorType)
{
	__asm
	{

		push [esp + 0x10]
		push [esp + 0x10]
		mov eax, ecx
		mov ecx, [esp + 0x10]
		mov edx, [esp + 0xC]
		call LAWN_MOUSEDOWNWITHTOOL

		ret 0x10
	}
}

constexpr unsigned int LAWN_TUTORIALARROWSHOW = 0x410FA0;
__declspec(naked) void Lawn::ShowTutorialArrow(int, int)
{
	__asm
	{
		push edi

		push[esp + 0xC]
		push[esp + 0xC]
		mov edi, ecx
		call LAWN_TUTORIALARROWSHOW

		pop edi
		ret 0x8
	}
}

constexpr unsigned int LAWN_TUTORIALARROWREMOVE = 0x411020;
__declspec(naked) void Lawn::RemoveTutorialArrow()
{
	__asm
	{
		push esi

		mov esi, ecx
		call LAWN_TUTORIALARROWREMOVE

		pop esi
		ret 0x0
	}
}

constexpr unsigned int LAWN_DRAWLEVEL = 0x417DA0;
__declspec(naked) void Lawn::DrawLevelName(Sexy::Graphics*)
{
	__asm
	{

		push[esp + 0x4]
		push ecx
		call LAWN_DRAWLEVEL

		ret 0x4
	}
}

constexpr unsigned int LAWN_CANDROPLOOT = 0x41D2C0;
__declspec(naked) bool Lawn::CanDropLoot()
{
	__asm
	{

		mov edx, ecx
		call LAWN_CANDROPLOOT

		ret 0x0
	}
}

constexpr unsigned int LAWN_BUNGEEISTARGETINGCELL = 0x41D320;
__declspec(naked) bool Lawn::IsBungeeTargetingCell(int, int)
{
	__asm
	{
		push edi
		push ebx

		mov edi, [esp + 0x10]
		mov ebx, [esp + 0xC]
		mov edx, ecx
		call LAWN_BUNGEEISTARGETINGCELL

		pop ebx
		pop edi
		ret 0x8
	}
}

constexpr unsigned int LAWN_GETBOSSZOMBIE = 0x41D390;
__declspec(naked) Zombie* Lawn::GetZomboss()
{
	__asm
	{

		mov edx, ecx
		call LAWN_GETBOSSZOMBIE

		ret 0x0
	}
}
#pragma endregion
