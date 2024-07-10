#pragma once

#include "ConstEnums.h"
#include "GameObject.h"
#include "CGeometry.h"

class Zombie : GameObject
{
public:
	ZombieType mZombieType;
	ZombiePhase mZombiePhase;
	float mPosX;
	float mPosY;
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
	Sexy::IRect mZombieRect;
	Sexy::IRect mZombieAttackRect;
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
	int mParticleOffsetX;
	int mParticleOffsetY;
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

	Zombie();

	void ZombieInit(int Lane, ZombieType Type, unsigned char Variant, int FromWave = 0, Zombie* ParentZombie = nullptr);
	void LoadReanim(ReanimationType);
	void PickRandomSpeed();

	void Update();
	void Draw();
	void Die();
	void BossDie();

	void SetFuture(bool);
	void SetMustache(bool);

	static void PreloadResources(ZombieType);
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