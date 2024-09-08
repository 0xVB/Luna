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

class ChallengeDefinition
{
private:
	static ChallengeDefinition* _gDefArray;
	static ChallengeDefinition* _gDefArrayEnd;
	static unsigned int _gUsedDefs;
	static unsigned int _gMaxDefs;
	static size_t _gDefSize;

	static unsigned int _aEndRefCount;
	static unsigned int _aEndRefs[];

	static unsigned int _aRefCount;
	static unsigned int _aRefs[];

	ChallengeDefinition();
	ChallengeDefinition(GameMode, ChallengePage, int IconIndex, int Row, int Col, const char* Name);

public:
	GameMode mChallengeMode;
	int mChallengeIconIndex;
	ChallengePage mPage;
	int mRow;
	int mCol;
	const char* mChallengeName;

	static ChallengeDefinition* Reallocate(unsigned int NewCapacity);
	static ChallengeDefinition* AddChallenge(const char* Name, ChallengePage, int Row, int Col);
	static ChallengeDefinition* GetDefinition(GameMode);
	static ChallengeDefinition* GetDefinitions();
};

#include "ExtendedUI.h"
#include "UIElement.h"
#include "Listeners.h"
class ChallengeScreen : public Sexy::UIElement, public Sexy::ButtonListener
{
public:
	LawnButton* mBackButton;
	Sexy::UIButton* mPageButton[4];
	Sexy::UIButton* mChallengeButton[70];
	LawnApp* mApp;
	UIToolTip* mToolTip;
	ChallengePage mPageIndex;
	bool mCheatEnableChallenges;
	UnlockingState mUnlockState;
	int mUnlockStateCounter;
	int mUnlockChallengeIndex;
	float mLockShakeX;
	float mLockShakeY;
};