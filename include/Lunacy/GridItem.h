#pragma once
#include "CGeometry.h"

struct MotionTrailFrame
{
	float mPosX = 0;
	float mPosY = 0;
	float mAnimTime = 0;
};

class GridItem
{
	typedef void(__stdcall* DoGraveEffects_Type)(GridItem*);

public:
	LawnApp* mApp;
	Lawn* mLawn;
	GridItemType mGridItemType;
	GridItemState mGridItemState;
	union
	{
		struct
		{
			int mGridX;
			int mGridY;
		};
		struct
		{
			int mCol;
			union
			{
				int mLane;
				int mRow;
			};
		};
		Sexy::IVector2 GridPos;
	};
	int mGridItemCounter;
	int mRenderOrder;
	bool mDead;
	union
	{
		struct
		{
			float mPosX;
			float mPosY;
		};
		Sexy::FVector2 mPos;
	};
	union
	{
		struct
		{
			float mGoalX;
			float mGoalY;
		};
		Sexy::FVector2 mGoal;
	};
	ReanimationID mGridItemReanimID;
	ParticleSystemID mGridItemParticleID;
	ZombieType mZombieType;
	SeedType mSeedType;
	ScaryPotType mScaryPotType;
	bool mHighlighted;
	int mTransparentCounter;
	int mSunCount;
	MotionTrailFrame mMotionTrailFrames[12];
	int mMotionTrailCount;

	GridItem(GridItemType = GRIDITEM_NONE);
	void Die();

	void DoGraveEffects();
	void OpenPortal();
	void ClosePortal();

	Sexy::IRect GetHitbox();
	Sexy::IVector2 GetCenter();

	std::list<GridItem*> GetGridItemsAround(int ColRange, int RowRange, GridItemType = GRIDITEM_NONE, bool IsBlacklist = false);
	std::list<Zombie*> GetZombiesAround(int ColRange, int RowRange, ZombieType = ZOMBIE_NONE, bool IsBlacklist = false);
	std::list<Plant*> GetPlantsAround(int ColRange, int RowRange, SeedType = SEED_NONE, bool IsBlacklist = false);
};