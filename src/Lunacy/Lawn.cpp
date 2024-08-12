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

void Lawn::KillPlantCell(int C, int L)
{
	auto aPlant = mPlants.GetNext();
	while (aPlant)
	{
		if (aPlant->mColumn == C || C == -1)
		{
			if (aPlant->mRow == L || L == -1)
			{
				aPlant->Die();
			}
		}
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
	if (KillPlants) KillPlantCell(Col, Lane);
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

Projectile* Lawn::GetNearestProjectile(FVector2 Point, float MinDist, ProjectileType Filter, bool IsBlacklist)
{
	bool DoFilter = Filter != -1;
	auto aProj = mProjectiles.GetNext();
	float CurrentDist = 0;
	
	Projectile* ClosestProjectile = nullptr;
	float SmallestDist = -1;

	while (aProj)
	{
		if (!DoFilter) goto Qualifies;
		if (IsBlacklist && aProj->mProjectileType == Filter) goto Skip;
		if (!IsBlacklist && aProj->mProjectileType != Filter) goto Skip;

	Qualifies:
		CurrentDist = aProj->DistanceFrom(Point);
		if (!ClosestProjectile || ((CurrentDist < SmallestDist) && CurrentDist >= MinDist))
		{
			ClosestProjectile = aProj;
			SmallestDist = CurrentDist;
		}

	Skip:
		aProj = mProjectiles.GetNext(aProj);
	}

	return ClosestProjectile;
}

GridItem* Lawn::GetNearestGridItem(FVector2 Point, float MinDist, GridItemType Filter, bool IsBlacklist)
{
	bool DoFilter = Filter != -1;
	auto aItem = mGridItems.GetNext();
	float CurrentDist = 0;

	GridItem* ClosestItem = nullptr;
	float SmallestDist = -1;

	while (aItem)
	{
		if (!DoFilter) goto Qualifies;
		if (IsBlacklist && aItem->mGridItemType == Filter) goto Skip;
		if (!IsBlacklist && aItem->mGridItemType != Filter) goto Skip;

	Qualifies:
		CurrentDist = aItem->mPos.GetDistance(Point);
		if (!ClosestItem || ((CurrentDist < SmallestDist) && CurrentDist >= MinDist))
		{
			ClosestItem = aItem;
			SmallestDist = CurrentDist;
		}

	Skip:
		aItem = mGridItems.GetNext(aItem);
	}

	return ClosestItem;
}

Zombie* Lawn::GetNearestZombie(FVector2 Point, float MinDist, ZombieType Filter, bool IsBlacklist)
{
	bool DoFilter = Filter != -1;
	auto aZombie = mZombies.GetNext();
	float CurrentDist = 0;

	Zombie* ClosestZombie = nullptr;
	float SmallestDist = -1;

	while (aZombie)
	{
		if (!DoFilter) goto Qualifies;
		if (IsBlacklist && aZombie->mZombieType == Filter) goto Skip;
		if (!IsBlacklist && aZombie->mZombieType != Filter) goto Skip;

	Qualifies:
		CurrentDist = aZombie->DistanceFrom(Point);
		if (!ClosestZombie || ((CurrentDist < SmallestDist) && CurrentDist >= MinDist))
		{
			ClosestZombie = aZombie;
			SmallestDist = CurrentDist;
		}

	Skip:
		aZombie = mZombies.GetNext(aZombie);
	}

	return ClosestZombie;
}

Pickup* Lawn::GetNearestPickup(FVector2 Point, float MinDist, PickupType Filter, bool IsBlacklist)
{
	bool DoFilter = Filter != -1;
	auto aPickup = mPickups.GetNext();
	float CurrentDist = 0;

	Pickup* ClosestPickup = nullptr;
	float SmallestDist = -1;

	while (aPickup)
	{
		if (!DoFilter) goto Qualifies;
		if (IsBlacklist && aPickup->mType == Filter) goto Skip;
		if (!IsBlacklist && aPickup->mType != Filter) goto Skip;

	Qualifies:
		CurrentDist = aPickup->DistanceFrom(Point);
		if (!ClosestPickup || ((CurrentDist < SmallestDist) && CurrentDist >= MinDist))
		{
			ClosestPickup = aPickup;
			SmallestDist = CurrentDist;
		}

	Skip:
		aPickup = mPickups.GetNext(aPickup);
	}

	return ClosestPickup;
}

Plant* Lawn::GetNearestPlant(FVector2 Point, float MinDist, SeedType Filter, bool IsBlacklist)
{
	bool DoFilter = Filter != -1;
	auto aPlant = mPlants.GetNext();
	float CurrentDist = 0;

	Plant* ClosestPlant = nullptr;
	float SmallestDist = -1;

	while (aPlant)
	{
		if (!DoFilter) goto Qualifies;
		if (IsBlacklist && aPlant->mType == Filter) goto Skip;
		if (!IsBlacklist && aPlant->mType != Filter) goto Skip;

	Qualifies:
		CurrentDist = aPlant->DistanceFrom(Point);
		if (!ClosestPlant || ((CurrentDist < SmallestDist) && CurrentDist >= MinDist))
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