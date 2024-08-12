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
		union
		{
			struct
			{
				float mX;
				float mY;
			};
			Sexy::FVector2 mPos;
		};
		union
		{
			struct
			{
				float mDestOffsetX;
				float mDestOffsetY;
			};
			Sexy::FVector2 mDestOffset;
		};
		MagnetItemType mItemType;
		
		MagnetItem(MagnetItemType = MAGNET_ITEM_NONE);
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
	union
	{
		struct
		{
			int mPlantX;
			int mPlantY;
			int mPlantW;
			int mPlantH;
		};
		struct
		{
			Sexy::IVector2 mPlantPos;
			Sexy::IVector2 mPlantSize;
		};
		Sexy::IRect mPlantRect;
	};
	union
	{
		struct
		{
			int mPlantAttackX;
			int mPlantAttackY;
			int mPlantAttackW;
			int mPlantAttackH;
		};
		struct
		{
			Sexy::IVector2 mPlantAttackPos;
			Sexy::IVector2 mPlantAttackSize;
		};
		Sexy::IRect mPlantAttackRect;
	};
	union
	{
		struct
		{
			int mTargetX;
			int mTargetY;
		};
		Sexy::IVector2 mTarget;
	};
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
	union
	{
		struct
		{
			float mShakeOffsetX;
			float mShakeOffsetY;
		};
		Sexy::FVector2 mShakeOffset;
	};
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

	void Update();
	void Draw(Sexy::Graphics*);

	Plant(SeedType = SEED_NONE);

	void Die();
	void Fire(Zombie* Target = NULL, int Lane = -1, bool IsSecondary = false);
	void SetSleeping(bool IsAsleep);
	void PlayBodyReanim(const char* TrackName, ReanimLoopType = REANIM_LOOP, int BlendTime = 0, float AnimRate = 12.0);
	void DoPlantingEffects();
	bool MakeSun();
	void Initialize();
	void Initialize(int Col, int Row, SeedType, SeedType Imitater = SEED_NONE);
	int GetRenderOrder();
	ParticleSystem* AttachParticle(int X, int Y, int RenderPos, ParticleEffect);
	void RemoveEffects();
	void Squish();
	void DrawShadow(Sexy::Graphics*, float X, float Y);
	Zombie* FindTargetZombie(int Lane, bool IsSecondaryWeapon);
	Zombie* FindTargetZombie(bool IsSecondaryWeapon = false);
	
	static bool __stdcall IsNocturnal(SeedType);
	static bool __stdcall IsAquatic(SeedType);
	static bool __stdcall IsUpgrade(SeedType);
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