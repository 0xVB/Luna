#pragma once
#include "ConstEnums.h"
#include "CGeometry.h"
#include "GameObject.h"

class Plant : public GameObject
{
public:
	class MagnetItem
	{
	public:
		Sexy::FVector2 mPos;
		Sexy::FVector2 mDestOffset;
		MagnetItemType mItemType;
	};

#pragma region Fields
	SeedType mType;
	int mColumn;
	int mAnimTimer;
	int mCurrentFrame;
	int mTicksPerFrame;
	int mFrameCount;
	PlantState mState;
	int mHealth;
	int mMaxHealth;
	PlantSubClass mSubClass;
	int mVanishTimer;
	int mSpecialTimer;
	int mStateTimer;
	int mActionTimer;
	int mActionRate;
	Sexy::IRect mPlantRect;
	Sexy::IRect mPlantAttackRect;
	Sexy::IVector2 mTarget;
	int mStartLane;
	ParticleSystemID mParticleID;
	int mShootingTimer;
	ReanimationID mBodyReanimID;
	ReanimationID mHeadReanimID;
	ReanimationID mHeadReanimID2;
	ReanimationID mHeadReanimID3;
	ReanimationID mBlinkReanimID;
	ReanimationID mLightReanimID;
	ReanimationID mSleepingReanimID;
	int mBlinkTimer;
	int mEatenTimer;
	int mGlowTimer;
	int mHighlightTimer;
	Sexy::FVector2 mShakeOffset;
	MagnetItem mMagnetItems[5];
	ZombieID mTargetZombieID;
	int mWakingTimer;
	PlantOnBungeeState mOnBungeeState;
	SeedType mImitaterType;
	int mPottedPlantIndex;
	bool mAnimPing;
	bool mDead;
	bool mSquished;
	bool mAsleep;
	bool mOnLawn;
	bool mHighlighted;
#pragma endregion

	Plant();

	void Initialize(SeedType Type, SeedType Imitater, int Lane, int Column);
	void PlantingEffects();
	void Die();
	void Fire(Zombie* Target = NULL, int Lane = -1, bool IsSecondary = false);

};

class PlantDefinition
{
private:

	static PlantDefinition* _gDefArray;
	static PlantDefinition* _gDefArrayEnd;
	static unsigned int _gUsedDefs;
	static unsigned int _gMaxDefs;
	static size_t _gDefSize;

	static unsigned int _aRefCount;
	static unsigned int _aRefs[];

	PlantDefinition();
	PlantDefinition(SeedType, const char* Name);

public:
	SeedType mSeedType;
	Sexy::Image** mPlantImage;
	ReanimationType mReanimationType;
	int mPacketIndex;
	int mSeedCost;
	int mRefreshTime;
	PlantSubClass mSubClass;
	int mLaunchRate;
	const char* mPlantName;

	/// <summary>
	/// Creates a new plant definition with the given name and adds it to the definition array.
	/// If the definition array isn't big enough, calls Reallocate before allocation.
	/// </summary>
	static PlantDefinition* AddPlant(const char* Name);

	static PlantDefinition* GetDefinitionArray();
	static PlantDefinition* GetPlantDefinition(SeedType Type);
	static PlantDefinition* Reallocate(unsigned int NewCapacity);
};