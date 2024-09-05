#pragma once
#include "LawnApp.h"
#include "Lawn.h"

class LawnMower
{
public:
	LawnApp* mApp;
	Lawn* mLawn;
	union
	{
		struct
		{
			float mPosX;
			float mPosY;
		};
		Sexy::FVector2 mPos;
	};
	int mRenderOrder;
	union
	{
		int mRow;
		int mLane;
	};
	int mAnimTicksPerFrame;
	ReanimationID mReanimID;
	int mChompCounter;
	int mRollingInCounter;
	int mSquishedCounter;
	LawnMowerState mMowerState;
	bool mDead;
	bool mVisible;
	LawnMowerType mMowerType;
	float mAltitude;
	MowerHeight mMowerHeight;
	int mLastPortalX;

	void Update();
	void UpdatePoolCleaner();
	void Draw(Sexy::Graphics*);
	void Die();

	void Init(int Lane);
	void MowZombie(Zombie*);
	void StartMower();
	void SquishMower();
	void EnableSuperMower();

	LawnMower(int Lane);
};