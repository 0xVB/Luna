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
			int mLane;
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
};