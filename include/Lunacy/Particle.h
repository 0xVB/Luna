#pragma once
#include "DataArray.h"
#include "CGeometry.h"

struct FloatParameterTrackNode
{
	float mTime;
	float mLowValue;
	float mHighValue;
	TodCurves mCurveType;
	TodCurves mDistribution;
};

struct FloatParameterTrack
{
	FloatParameterTrackNode* mNodes;
	int mCountNodes;
};

class ParticleField
{
public:
	ParticleFieldType mFieldType;
	FloatParameterTrack mX;
	FloatParameterTrack mY;
};

class EmitterDefinition
{
public:
	Sexy::Image* mImage;
	int mImageCol;
	int mImageRow;
	int mImageFrames;
	int mAnimated;
	int mParticleFlags;
	EmitterType mEmitterType;
	char* mName;
	char* mOnDuration;
	FloatParameterTrack mSystemDuration;
	FloatParameterTrack mCrossFadeDuration;
	FloatParameterTrack mSpawnRate;
	FloatParameterTrack mSpawnMinActive;
	FloatParameterTrack mSpawnMaxActive;
	FloatParameterTrack mSpawnMaxLaunched;
	FloatParameterTrack mEmitterRadius;
	FloatParameterTrack mEmitterOffsetX;
	FloatParameterTrack mEmitterOffsetY;
	FloatParameterTrack mEmitterBoxX;
	FloatParameterTrack mEmitterBoxY;
	FloatParameterTrack mEmitterSkewX;
	FloatParameterTrack mEmitterSkewY;
	FloatParameterTrack mEmitterPath;
	FloatParameterTrack mParticleDuration;
	FloatParameterTrack mLaunchSpeed;
	FloatParameterTrack mLaunchAngle;
	FloatParameterTrack mSystemRed;
	FloatParameterTrack mSystemGreen;
	FloatParameterTrack mSystemBlue;
	FloatParameterTrack mSystemAlpha;
	FloatParameterTrack mSystemBrightness;
	ParticleField* mParticleFields;
	int mParticleFieldCount;
	ParticleField* mSystemFields;
	int mSystemFieldCount;
	FloatParameterTrack mParticleRed;
	FloatParameterTrack mParticleGreen;
	FloatParameterTrack mParticleBlue;
	FloatParameterTrack mParticleAlpha;
	FloatParameterTrack mParticleBrightness;
	FloatParameterTrack mParticleSpinAngle;
	FloatParameterTrack mParticleSpinSpeed;
	FloatParameterTrack mParticleScale;
	FloatParameterTrack mParticleStretch;
	FloatParameterTrack mCollisionReflect;
	FloatParameterTrack mCollisionSpin;
	FloatParameterTrack mClipTop;
	FloatParameterTrack mClipBottom;
	FloatParameterTrack mClipLeft;
	FloatParameterTrack mClipRight;
	FloatParameterTrack mAnimationRate;
};

class ParticleDefinition
{
public:
	EmitterDefinition* mEmitterDefs;
	int mEmitterDefCount;
};

class ParticleEmitter
{
public:
	EmitterDefinition* mEmitterDef;
	ParticleSystem* mParticleSystem;
	List<enum ParticleID> mParticleList;
	float mSpawnAccum;
	Sexy::FVector2 mSystemCenter;
	int mParticlesSpawned;
	int mSystemAge;
	int mSystemDuration;
	float mSystemTimeValue;
	float mSystemLastTimeValue;
	bool mDead;
	Sexy::Color mColorOverride;
	bool mExtraAdditiveDrawOverride;
	float mScaleOverride;
	Sexy::Image* mImageOverride;
	ParticleEmitterID mCrossFadeEmitterID;
	int mEmitterCrossFadeCountDown;
	int mFrameOverride;
	float mTrackInterp[10];
	float mSystemFieldInterp[4][2];
};

class Particle
{
	ParticleEmitter* mParticleEmitter;
	int mParticleDuration;
	int mParticleAge;
	float mParticleTimeValue;
	float mParticleLastTimeValue;
	float mAnimationTimeValue;
	Sexy::FVector2 mVelocity;
	Sexy::FVector2 mPosition;
	int mImageFrame;
	float mSpinPosition;
	float mSpinVelocity;
	ParticleID mCrossFadeParticleID;
	int mCrossFadeDuration;
	float mParticleInterp[16];
	float mParticleFieldInterp[4][2];
};

class ParticleHolder
{
public:
	DataArray<ParticleSystem> mParticleSystems;
	DataArray<ParticleEmitter> mEmitters;
	DataArray<Particle> mParticles;
	Allocator mParticleListNodeAllocator;
	Allocator mEmitterListNodeAllocator;
};

class ParticleSystem
{
public:
	ParticleEffect mEffectType;
	ParticleDefinition* mParticleDef;
	ParticleHolder* mParticleHolder;
	List<enum ParticleEmitterID> mEmitterList;
	bool mDead;
	bool mIsAttachment;
	int mRenderOrder;
	bool mDontUpdate;
};