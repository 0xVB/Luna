#pragma once
#include "CGeometry.h"

class Challenge
{
public:
	LawnApp* mApp;
	Lawn* mLawn;
	bool mBeghouledMouseCapture;
	int mBeghouledMouseDownX;
	int mBeghouledMouseDownY;
	bool mBeghouledEated[9][6];
	bool mBeghouledPurcasedUpgrade[3];
	int mBeghouledMatchesThisMove;
	ChallengeState mChallengeState;
	int mChallengeStateCounter;
	int mConveyorBeltCounter;
	int mChallengeScore;
	bool mShowBowlingLine;
	SeedType mLastConveyorSeedType;
	int mSurvivalStage;
	int mSlotMachineRollCount;
	ReanimationID mReanimChallenge;
	ReanimationID mReanimCloud[6];
	int mCloudCounter[6];
	int mChallengeGridX;
	int mChallengeGridY;
	int mScaryPotterPots;
	int mRainCounter;
	int mTreeOfWisdomTalkIndex;
};