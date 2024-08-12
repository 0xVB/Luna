#pragma once
#include "CGeometry.h"
#include "Particle.h"

class TrailDefinition
{
public:
	Sexy::Image* mImage;
	int mMaxPoints;
	float mMinPointDistance;
	int mTrailFlags;
	FloatParameterTrack mTrailDuration;
	FloatParameterTrack mWidthOverLength;
	FloatParameterTrack mWidthOverTime;
	FloatParameterTrack mAlphaOverLength;
	FloatParameterTrack mAlphaOverTime;
};

struct TrailPoint
{
	Sexy::FVector2 aPos;
};

class TrailHolder;
class Trail
{
public:
	TrailPoint mTrailPoints[20];
	int mNumTrailPoints;
	bool mDead;
	int mRenderOrder;
	int mTrailAge;
	int mTrailDuration;
	TrailDefinition* mDefinition;
	TrailHolder* mTrailHolder;
	float mTrailInterp[4];
	Sexy::FVector2 mTrailCenter;
	bool mIsAttachment;
	Sexy::Color mColorOverride;
};

class TrailHolder
{
public:
	DataArray<Trail> mTrails;
};