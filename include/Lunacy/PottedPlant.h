#pragma once
#include "CGeometry.h"

class PottedPlant
{
public:
	SeedType mSeedType;
	GardenType mWhichZenGarden;
	union
	{
		struct
		{
			int mX;
			int mY;
		};
		Sexy::IVector2 mPos;
	};
	int mFacing;
	__int64 mLastWateredTime;
	DrawVariation mDrawVariation;
	PottedPlantAge mPlantAge;
	int mTimesFed;
	int mFeedingsPerGrow;
	PottedPlantNeed mPlantNeed;
	__int64 mLastNeedFulfilledTime;
	__int64 mLastFertilizedTime;
	__int64 mLastChocolateTime;
	int mFutureAttribute[1];
	PottedPlant() {}
};
