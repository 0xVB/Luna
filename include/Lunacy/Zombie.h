#pragma once

#include "ConstEnums.h"
#include "GameObject.h"
#include "CGeometry.h"

enum ZombieAttackType
{
	ATTACKTYPE_CHEW,
	ATTACKTYPE_DRIVE_OVER,
	ATTACKTYPE_VAULT,
	ATTACKTYPE_LADDER
};

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
	void Animate();
	void UpdateReanim();
	void Draw(Sexy::Graphics*);
	void DrawShadow(Sexy::Graphics*);

	Zombie();

	void Init(int Lane = -1, ZombieType = ZOMBIE_NONE, unsigned char Variant = 0, int FromWave = -1, Zombie* ParentZombie = nullptr);
	void Init(int Lane, ZombieType, unsigned char Variant, Zombie* ParentZombie, int FromWave);
	
	Reanimation* LoadReanim(ReanimationType);
	void PickRandomSpeed();
	void UpdateAnimSpeed();
	void Chill(int ChillTime, int FreezeTime);
	void TakeDamage(int Amount, DamageFlag = DAMAGE_CARRY_OVER);
	void PlayReanimTrack(const char* TrackName, ReanimLoopType = ReanimLoopType::REANIM_PLAY_ONCE, int BlendTime = 1, float FPS = 12.0);
	void GetTrackPosition(const char* TrackName, float& X, float& Y);
	Sexy::FVector2 __inline GetTrackPosition(const char* TrackName)
	{
		Sexy::FVector2 out;
		GetTrackPosition(TrackName, out.mX, out.mY);
		return out;
	}
	int GetBobsledPosition();

	void DropLoot();
	void Die(bool DropLoot = true);
	void BossDie();

	void SetFuture(bool);
	void SetMustache(bool);
	void PreloadResources();
	int __inline GetTotalHealth()
	{
		return mBodyHealth
			+ mHelmHealth
			+ mShieldHealth
			+ mFlyingHealth;
	}
	int __inline GetTotalMaxHealth()
	{
		return mBodyMaxHealth
			+ mHelmMaxHealth
			+ mShieldMaxHealth
			+ mFlyingMaxHealth;
	}

	static void __stdcall PreloadResources(ZombieType);

#pragma region Base Functions
	static void __stdcall SetupDoorArms(Reanimation*, bool ShowArms = true);
	static void __stdcall SetupReanimLayers(Reanimation*, ZombieType);

	void ReanimIgnoreClipRect(const char* TrackName, bool DoIgnore = true);
	void EnableClipping();
	void LoadPlainZombieReanim();
	void TrySpawnLevelAward();
	void RemoveIceTrap();
	void HitIceTrap();

	void PickBungeeZombieTarget(int Column = -1);
	void BungeeDropZombie(Zombie*, int Col, int Row);
	void __inline BungeeDropZombie(ZombieType, int Col, int Row);
	void BungeeStealTarget();
	void BungeeLiftTarget();
	void BungeeLanding();
	void UpdateBungee();

	void PogoBreak(DamageFlag = DamageFlags::DAMAGE_BLOCKING);
	bool IsPogoBouncing();
	void UpdatePogo();

	void CatapultFire(Plant* = nullptr);
	Plant* FindCatapultTarget();
	void UpdateCatapult();

	void LandFlyer(DamageFlag = DamageFlags::DAMAGE_CARRY_OVER);
	void SetPropellerHatSpin(bool);
	void UpdateFlyingZombie();

	void BobseldCrash();
	void UpdateBobsled();
	
	void DiggerLoseAxe();
	void UpdateDigger();
	
	void SummonBackupDancer(int Row, int XPos);
	void SummonBackupDancers();
	bool NeedsBackupDancers();
	void UpdateBackupDancer();
	void UpdateGraveRise();
	void UpdateDancer();

	void UpdateImp();
	void UpdateYeti();
	void UpdateDeath();
	void UpdateLadder();
	void UpdateSnorkel();
	void UpdatePeaHead();
	void UpdateZamboni();
	void UpdatePlaying();
	void UpdateMowered();
	void UpdateZomboss();
	void UpdateNewspaper();
	void UpdateYuckyFace();
	void UpdateGargantuar();
	void UpdateSquashHead();
	void UpdatePoolZombie();
	void UpdatePolevaulter();
	void UpdateGatlingHead();
	void UpdateLadderClimb();
	void UpdateDolphinRider();
	void UpdateJackInTheBox();
	void UpdateJalapenoHead();
	void UpdateZombaquarium();
	void UpdateBossFireball();
	void UpdateZombieFalling();
	void UpdateZombieMovement();
	void UpdateZombiePosition();
	void UpdateZombieInChimney();
	void UpdateZombieHighGround();
	void UpdateZombieChimney();
	void BossPlayIdle();
	void DrawBossFireBall(Sexy::Graphics*);
	void UpdateDamageStates(DamageFlag);
	void UpdateActions();

	bool IsTangleKelpTarget();
	bool IsWalkingBackwards();
	void CheckForLawnEdge();
	void SetYuckyFace(bool);
	bool IsOnHighGround();
	bool HasYuckyFace();
	bool IsOnBoard();
	bool IsFlying();

	void DropShield(DamageFlag);
	void DropHelm(DamageFlag);
	void DropHead(DamageFlag);
	void DropArm(DamageFlag);
	void DropFlag();
	void DropPole();

	bool CanTargetPlant(Plant*, ZombieAttackType = ZombieAttackType::ATTACKTYPE_CHEW);
	Plant* FindPlantTarget(ZombieAttackType);
	Zombie* FindZombieTarget();
	void StartWalking(int BlendTime);
	void SquishPlantsInCell(int Col, int Row, ZombieAttackType);
	void SquishPlants(int Col = -1, int Row = -1, ZombieAttackType = ZombieAttackType::ATTACKTYPE_DRIVE_OVER);
	void ZamboniDeath(DamageFlag);
	void CatapultDeath(DamageFlag);
	void ApplyFPS(float);
	void SetFPS(float);
	void CheckSquish();
	void StartEating();
	void StopEating();
	void Hypnotize();
	void ApplyButter();
	void RemoveButter();
	void RemoveCold();
	void ApplyBurn();
	void MowDown();
	void EatPlant(Plant*);
	void EatZombie(Zombie*);
	void PoolSplash(bool IntoPool = true);
	void AttachShield();
	void DetachShield();
	void DoDaisies();

	void WalkIntoHouse();
	void RiseFrom(int Col, int Row);
	void RiseFromGrave(int Col, int Row);
	void RiseFromPool(int Col, int Row);
	void __inline DropFromSky(int Col, int Row);
	
	float GetZombieYPos(int Row);
	float __inline GetZombieYPos() { GetZombieYPos(mRow); }
	float GetZombieLead(float Time);
	int GetBobseldPosition();
	bool AffectedByDamage(DamageFlag);
	bool ZombieNotWalking();
	bool IsDeadOrDying();
	bool IsImmobilized();
	bool CanBeChilled();
	bool CanBeFrozen();
	bool IsChilled();
	bool HasShadow();
#pragma endregion
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