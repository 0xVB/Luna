#pragma once
#include "TodLib.h"
#include "DataArray.h"
#include "Listeners.h"
#include "UIElement.h"

class Lawn : Sexy::UIElement, Sexy::ButtonListener
{
#pragma region Fields
public:
	LawnApp* mApp;
	DataArray<Zombie> mZombies;
	DataArray<Plant> mPlants;
	DataArray<Projectile> mProjectiles;
	DataArray<Pickup> mPickups;
	DataArray<LawnMower> mLawnMowers;
	DataArray<GridItem> mGridItems;
	CursorObject* mCursorObject;
	CursorPreview* mCursorPreview;
	UIMessage* mAdvice;
	SeedBank* mSeedBank;
	GameButton* mMenuButton;
	GameButton* mStoreButton;
	bool mIgnoreMouseUp;
	UIToolTip* mToolTip;
	Sexy::Font* mDebugFont;
	CutScene* mCutScene;
	Challenge* mChallenge;
	bool mPaused;
	GridSquareType mGridSquareType[9][6];
	int mGridCelLook[9][6];
	int mGridCelOffset[9][6][2];
	int mGridCelFog[9][7];
	bool mEnableGraveStones;
	int mSpecialGraveStoneX;
	int mSpecialGraveStoneY;
	float mFogOffset;
	int mFogBlownCountDown;
	PlantRowType mPlantRow[6];
	int mWaveRowGotLawnMowered[6];
	int mBonusLawnMowersRemaining;
	int mIceMinX[6];
	int mIceTimer[6];
	ParticleSystemID mIceParticleID[6];
	TodSmoothArray mRowPickingArray[6];
	ZombieType mZombiesInWave[100][50];
	bool mZombieAllowed[100];
	int mSunCountDown;
	int mNumSunsFallen;
	int mShakeCounter;
	int mShakeAmountX;
	int mShakeAmountY;
	BackgroundType mBackground;
	int mLevel;
	int mSodPosition;
	int mPrevMouseX;
	int mPrevMouseY;
	int mSunMoney;
	int mNumWaves;
	int mMainCounter;
	int mEffectCounter;
	int mDrawCount;
	int mRiseFromGraveCounter;
	int mOutOfMoneyCounter;
	int mCurrentWave;
	int mTotalSpawnedWaves;
	TutorialState mTutorialState;
	ParticleSystemID mTutorialParticleID;
	int mTutorialTimer;
	int mLastBungeeWave;
	int mZombieHealthToNextWave;
	int mZombieHealthWaveStart;
	int mZombieCountDown;
	int mZombieCountDownStart;
	int mHugeWaveCountDown;
	bool mHelpDisplayed[65];
	AdviceType mHelpIndex;
	bool mFinalBossKilled;
	bool mShowShovel;
	int mCoinBankFadeCount;
	DebugTextMode mDebugTextMode;
	bool mLevelComplete;
	int mBoardFadeOutCounter;
	int mNextSurvivalStageCounter;
	int mScoreNextMowerCounter;
	bool mLevelAwardSpawned;
	int mProgressMeterWidth;
	int mFlagRaiseCounter;
	int mIceTrapCounter;
	int mBoardRandSeed;
	ParticleSystemID mPoolSparklyParticleID;
	ReanimationID mFwooshID[6][12];
	int mFwooshCountDown;
	int mTimeStopCounter;
	bool mDroppedFirstCoin;
	int mFinalWaveSoundCounter;
	int mCobCannonCursorDelayCounter;
	int mCobCannonMouseX;
	int mCobCannonMouseY;
	bool mKilledYeti;
	bool mMustacheMode;
	bool mSuperMowerMode;
	bool mFutureMode;
	bool mPinataMode;
	bool mDaisyMode;
	bool mSukhbirMode;
	BoardResult mPrevBoardResult;
	int mTriggeredLawnMowers;
	int mPlayTimeActiveLevel;
	int mPlayTimeInactiveLevel;
	int mMaxSunPlants;
	int mStartDrawTime;
	int mIntervalDrawTime;
	int mIntervalDrawCountStart;
	float mMinFPS;
	int mPreloadTime;
	int mGameID;
	int mGravesCleared;
	int mPlantsEaten;
	int mPlantsShoveled;
	int mCoinsCollected;
	int mDiamondsCollected;
	int mPottedPlantsCollected;
	int mChocolateCollected;
#pragma endregion

#pragma region Functions
	GridItem* AddLadder(int Column, int Lane);
	GridItem* AddCrater(int Column, int Lane);
	int CountGraves();

	void SpawnZombiesFromPool();
	void SpawnZombiesFromSky();
	void SpawnZombiesFromGrave();

	Plant* NewPlant(int Column, int Lane, SeedType, SeedType ImitaterType);
	void DoPlantingEffects(int Column, int Lane, Plant*);

	Projectile* NewProjectile(int X, int Y, int RenderOrder, int Lane, ProjectileType);

	int PlantingPixelToGridX(SeedType, int X, int Y);
	int PlantingPixelToGridY(SeedType, int X, int Y);
	int GridToPixelX(int Col, int Lane);
	int GridToPixelY(int Col, int Lane);
	int PixelToGridX(int X, int Y);
	int PixelToGridY(int X, int Y);

	Sexy::IVector2 PlantingPixelToGrid(SeedType, int X, int Y);
	Sexy::IVector2 GridToPixel(int Col, int Lane);
	Sexy::IVector2 PixelToGrid(int X, int Y);
#pragma endregion

};