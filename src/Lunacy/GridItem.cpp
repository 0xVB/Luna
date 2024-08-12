#include "Lunacy/LawnApp.h"
#include "Lunacy/GridItem.h"

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