#include "Lunacy/LawnApp.h"
#include "Lunacy/GridItem.h"
#include "Lunacy/Zombie.h"
#include "Lunacy/Plant.h"
#include "Lunacy/Lawn.h"

GridItem::GridItem(GridItemType Type)
{
	mApp = LawnApp::GetApp();
	mLawn = mApp->mLawn;

	mGridItemType = Type;
	mCol = 0;
	mLane = 0;
	mGridItemCounter = 0;
	mRenderOrder = 0;
	mDead = false;
	mPos = Sexy::FVector2();
	mGoal = Sexy::FVector2();
	mGridItemReanimID = REANIMID_NULL;
	mGridItemParticleID = PARTICLESYSTEMID_NULL;
	mZombieType = ZOMBIE_INVALID;
	mSeedType = SEED_NONE;
	mScaryPotType = SCARYPOT_NONE;
	mHighlighted = false;
	mTransparentCounter = 0;
	mSunCount = 0;
	mMotionTrailCount = 0;
}

Sexy::IRect GridItem::GetHitbox()
{
	return mLawn->GridToPixelArea(mCol, mRow, 1, 1);
}
Sexy::IVector2 GridItem::GetCenter()
{
	return GetHitbox().GetCenter();
}

std::list<GridItem*> GridItem::GetGridItemsAround(int ColRange, int RowRange, GridItemType Type, bool Blacklist)
{
	auto List = std::list<GridItem*>();
	auto aItem = mLawn->mGridItems.GetNext();

	while (aItem)
	{
		if (Type == GRIDITEM_NONE) goto Qualifies;
		if (Blacklist && aItem->mGridItemType == Type) goto Skip;
		if (!Blacklist && aItem->mGridItemType != Type) goto Skip;

	Qualifies:
		if (abs(aItem->mCol - mCol) <= ColRange && abs(aItem->mRow - mRow) <= RowRange)
			List.push_back(aItem);

	Skip:
		aItem = mLawn->mGridItems.GetNext(aItem);
	}

	return List;
}

std::list<Plant*> GridItem::GetPlantsAround(int ColRange, int RowRange, SeedType Type, bool Blacklist)
{
	auto List = std::list<Plant*>();
	auto aItem = mLawn->mPlants.GetNext();

	while (aItem)
	{
		if (Type == SEED_NONE) goto Qualifies;
		if (Blacklist && aItem->mType == Type) goto Skip;
		if (!Blacklist && aItem->mType != Type) goto Skip;

	Qualifies:
		if (abs(aItem->mCol - mCol) <= ColRange && abs(aItem->mRow - mRow) <= RowRange)
			List.push_back(aItem);

	Skip:
		aItem = mLawn->mPlants.GetNext(aItem);
	}

	return List;
}

std::list<Zombie*> GridItem::GetZombiesAround(int ColRange, int RowRange, ZombieType Type, bool Blacklist)
{
	auto List = std::list<Zombie*>();
	auto aItem = mLawn->mZombies.GetNext();

	while (aItem)
	{
		if (Type == ZOMBIE_NONE) goto Qualifies;
		if (Blacklist && aItem->mZombieType == Type) goto Skip;
		if (!Blacklist && aItem->mZombieType != Type) goto Skip;

	Qualifies:
		if (abs(aItem->GetColumn() - mCol) <= ColRange && abs(aItem->mRow - mRow) <= RowRange)
			List.push_back(aItem);

	Skip:
		aItem = mLawn->mZombies.GetNext(aItem);
	}

	return List;
}

void GridItem::DoGraveEffects()
{
	DoGraveEffects_Type Function = (DoGraveEffects_Type)(0x44E090);
	Function(this);
}

void __declspec(naked) __thiscall GridItem::Die()
{
	__asm
	{
		mov esi, ecx
		mov eax, 0x44D000
		call eax
		ret
	}
}

void __declspec(naked) __thiscall GridItem::OpenPortal()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x44E1B0
		call ecx
		ret
	}
}

void __declspec(naked) __thiscall GridItem::ClosePortal()
{
	__asm
	{
		mov esi, ecx
		mov eax, 0x44E360
		call eax
		ret
	}
}