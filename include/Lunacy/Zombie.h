#pragma once

#include "ConstEnums.h"
#include "GameObject.h"
#include "CGeometry.h"

class Zombie : public GameObject
{
private:
	Reanimation* LoadReanimUnsafe(ReanimationType);
	void DieNoLoot();
	void DieLoot();

public:
	ZombieType mZombieType;
	ZombiePhase mZombiePhase;
	union
	{
		struct
		{
			float mPosX;
			float mPosY;
		};
		Sexy::FVector2 mPos;
	};
	float mVelX;
	int mAnimCounter;
	int mGroanCounter;
	int mAnimTicksPerFrame;
	int mAnimFrames;
	int mFrame;
	int mPrevFrame;
	bool mVariant;
	bool mIsEating;
	int mJustGotShotCounter;
	int mShieldJustGotShotCounter;
	int mShieldRecoilCounter;
	int mZombieAge;
	ZombieHeight mZombieHeight;
	int mPhaseCounter;
	int mFromWave;
	bool mDroppedLoot;
	int mZombieFade;
	bool mFlatTires;
	int mUseLadderCol;
	int mTargetCol;
	float mAltitude;
	bool mHitUmbrella;
	union
	{
		struct
		{
			int mZombieX;
			int mZombieY;
			int mZobmieW;
			int mZombieH;
		};
		struct
		{
			Sexy::IVector2 mZombiePos;
			Sexy::IVector2 mZombieSize;
		};
		Sexy::IRect mZombieRect;
	};
	union
	{
		struct
		{
			int mZombieAttackX;
			int mZombieAttackY;
			int mZombieAttackW;
			int mZombieAttackH;
		};
		struct
		{
			Sexy::IVector2 mZombieAttackPos;
			Sexy::IVector2 mZombieAttackSize;
		};
		Sexy::IRect mZombieAttackRect;
	};
	int mChilledCounter;
	int mButteredCounter;
	int mIceTrapCounter;
	bool mMindControlled;
	bool mBlowingAway;
	bool mHasHead;
	bool mHasArm;
	bool mHasObject;
	bool mInPool;
	bool mOnHighGround;
	bool mYuckyFace;
	int mYuckyFaceCounter;
	HelmType mHelmType;
	int mBodyHealth;
	int mBodyMaxHealth;
	int mHelmHealth;
	int mHelmMaxHealth;
	ShieldType mShieldType;
	int mShieldHealth;
	int mShieldMaxHealth;
	int mFlyingHealth;
	int mFlyingMaxHealth;
	bool mDead;
	ZombieID mRelatedZombieID;
	ZombieID mFollowerZombieID[4];
	bool mPlayingSong;
	union
	{
		struct
		{
			int mParticleOffsetX;
			int mParticleOffsetY;
		};
		Sexy::IVector2 mParticleOffset;
	};
	AttachmentID mAttachmentID;
	int mSummonCounter;
	ReanimationID mBodyReanimID;
	float mScaleZombie;
	float mVelZ;
	float mOrginalAnimRate;
	PlantID mTargetPlantID;
	int mBossMode;
	int mTargetRow;
	int mBossBungeeCounter;
	int mBossStompCounter;
	int mBossHeadCounter;
	ReanimationID mBossFireBallReanimID;
	ReanimationID mSpecialHeadReanimID;
	int mFireballRow;
	bool mIsFireBall;
	ReanimationID mMoweredReanimID;
	int mLastPortalX;

	void Update();
	void Draw(Sexy::Graphics*);

	Zombie();

	void Init(int Lane = -1, ZombieType = (ZombieType)-1, unsigned char Variant = 0, int FromWave = -1, Zombie* ParentZombie = nullptr);
	void Init(int Lane, ZombieType, unsigned char Variant, Zombie* ParentZombie, int FromWave);
	
	Reanimation* LoadReanim(ReanimationType);
	void PickRandomSpeed();
	void UpdateAnimSpeed();
	void Chill(int ChillTime, int FreezeTime);
	void TakeDamage(int Amount, DamageFlag);

	void DropLoot();
	void Die(bool DropLoot = true);
	void BossDie();

	void SetFuture(bool);
	void SetMustache(bool);
	void PreloadResources();

	static void __stdcall PreloadResources(ZombieType);
};

class ZombieDefinition
{
private:
	static ZombieDefinition* _gDefArray;
	static ZombieDefinition* _gDefArrayEnd;
	static unsigned int _gUsedDefs;
	static unsigned int _gMaxDefs;
	static size_t _gDefSize;

	static unsigned int _aRefCount;
	static unsigned int _aRefs[];

	ZombieDefinition();
	ZombieDefinition(ZombieType, const char* Name);

public:
	ZombieType mZombieType;
	ReanimationType mReanimationType;
	int mZombieValue;
	int mStartingLevel;
	int mFirstAllowedWave;
	int mPickWeight;
	const char* mZombieName;

	/// <summary>
	/// Creates a new zombie definition with the given name and adds it to the definition array.
	/// If the definition array isn't big enough, calls Reallocate before allocation.
	/// </summary>
	static ZombieDefinition* AddZombie(const char* Name);

	static ZombieDefinition* GetDefinitionArray();
	static ZombieDefinition* GetZombieDefinition(ZombieType Type);
	static ZombieDefinition* Reallocate(unsigned int NewCapacity);
};