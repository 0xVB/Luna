#pragma once
#include "GameObject.h"
#include "PottedPlant.h"

class Pickup : public GameObject
{
public:
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
			float mVelX;
			float mVelY;
		};
		Sexy::FVector2 mVel;
	};
	float mScale;
	bool mDead;
	int mFadeCount;
	float mCollectX;
	float mCollectY;
	int mGroundY;
	int mCoinAge;
	bool mIsBeingCollected;
	int mDisappearCounter;
	PickupType mType;
	PickupMotion mCoinMotion;
	AttachmentID mAttachmentID;
	float mCollectionDistance;
	SeedType mUsableSeedType;
	PottedPlant mPottedPlantSpec;
	bool mNeedsBouncyArrow;
	bool mHasBouncyArrow;
	bool mHitGround;
	int mTimesDropped;

	void Update();
	void Draw(Sexy::Graphics*);

	Pickup(PickupType = PICKUP_NONE);
	void Die();

	void Collect();
};