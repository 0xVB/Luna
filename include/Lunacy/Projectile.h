#pragma once
#include "ConstEnums.h"
#include "GameObject.h"
#include "CGeometry.h"
class Projectile : public GameObject
{
public:
	int mFrame;
	int mNumFrames;
	int mAnimCounter;
	union
	{
		struct
		{
			float mPosX;
			float mPosY;
			float mPosZ;
		};
		Sexy::FVector3 mPos;
	};
	union
	{
		struct
		{
			float mVelX;
			float mVelY;
			float mVelZ;
		};
		Sexy::FVector3 mVel;
	};
	float mAccZ;
	float mShadowY;
	bool mDead;
	int mAnimTicksPerFrame;
	ProjectileMotion mMotionType;
	ProjectileType mProjectileType;
	int mProjectileAge;
	int mClickBackoffCounter;
	float mRotation;
	float mRotationSpeed;
	bool mOnHighGround;
	int mDamageRangeFlags;
	int mHitTorchwoodGridX;
	AttachmentID mAttachmentID;
	float mCobTargetX;
	int mCobTargetRow;
	ZombieID mTargetZombieID;
	int mLastPortalX;

	void Update();
	void Draw(Sexy::Graphics*);

	Projectile(ProjectileType = PROJECTILE_PEA);
	void Die();

	Plant* FindTargetPlant();
	Zombie* FindTargetZombie();
	Sexy::IRect GetHitbox();
	void Collide(Zombie* = nullptr);
	void ToFireball(int GridPos = -1);
};

class ProjectileDefinition
{
private:

	static ProjectileDefinition* _gDefArray;
	static ProjectileDefinition* _gDefArrayEnd;
	static unsigned int _gUsedDefs;
	static unsigned int _gMaxDefs;
	static size_t _gDefSize;

	static unsigned int _aRefCount;
	static unsigned int _aRefs[];

	ProjectileDefinition();
	ProjectileDefinition(ProjectileType);

public:
	ProjectileType mProjectileType;
	int mImageRow;
	int mDamage;

	/// <summary>
	/// Creates a new projectile definition and adds it to the definition array.
	/// If the definition array isn't big enough, calls Reallocate before allocation.
	/// </summary>
	static ProjectileDefinition* AddProjectile();

	static ProjectileDefinition* GetDefinitionArray();
	static ProjectileDefinition* GetProjectileDefinition(ProjectileType Type);
	static ProjectileDefinition* Reallocate(unsigned int NewCapacity);
};