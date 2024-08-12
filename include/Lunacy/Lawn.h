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
	union
	{
		struct
		{
			int mSpecialGraveStoneX;
			int mSpecialGraveStoneY;
		};
		Sexy::IVector2 mSpecialGraveStonePos;
	};
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
	union
	{
		struct
		{
			int mShakeAmountX;
			int mShakeAmountY;
		};
		Sexy::IVector2 mShakeAmount;
	};
	BackgroundType mBackground;
	int mLevel;
	int mSodPosition;
	union
	{
		struct
		{
			int mPrevMouseX;
			int mPrevMouseY;
		};
		Sexy::IVector2 mPrevMousePos;
	};
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
	union
	{
		struct
		{
			int mCobCannonMouseX;
			int mCobCannonMouseY;
		};
		Sexy::IVector2 mCobCannonMousePos;
	};
	bool mKilledYeti;
	bool mMustacheMode;
	bool mSuperMowerMode;
	bool mFutureMode;
	bool mPinataMode;
	bool mDaisyMode;
	bool mSukhbirMode;
	GameResult mPrevGameResult;
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

	void Update();
	void Draw(Sexy::Graphics* G);
#pragma region Functions
	GridItem* NewGridItem(GridItemType, int Lane, int Column);
	GridItem* AddLadder(int Column, int Lane);
	GridItem* AddCrater(int Column, int Lane);
	GridItem* AddGrave(int Column, int Lane, bool DoEffects = true, bool KillPlants = true);

	int CountGraves();

	Pickup* NewPickup(int X, int Y, PickupType, PickupMotion = PICKUP_MOTION_COIN);
	Pickup* NewPickup(PickupType, int X, int Y, PickupMotion = PICKUP_MOTION_COIN);
	Pickup* NewPacket(SeedType, int X, int Y);

	Zombie* NewZombie(ZombieType, int Lane, int FromWave = 0);
	void SpawnZombiesFromPool();
	void SpawnZombiesFromSky();
	void SpawnZombiesFromGrave();

	Plant* NewPlant(int Column, int Lane, SeedType, SeedType ImitaterType);
	void DoPlantingEffects(int Column, int Lane, Plant*);
	void KillPlantCell(int Col = -1, int Lane = -1);

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

	Sexy::IRect GridToPixelArea(int Col, int Lane, int HSize = 3, int VSize = 3);
	Sexy::IRect PixelToGridArea(int X, int Y, int W = 100, int H = 100);

	Projectile* GetNearestProjectile(Sexy::FVector2, float MinDistance = 0, ProjectileType Filter = (ProjectileType)-1, bool IsBlacklist = false);
	GridItem* GetNearestGridItem(Sexy::FVector2, float MinDistance = 0, GridItemType = GRIDITEM_NONE, bool IsBlacklist = false);
	Zombie* GetNearestZombie(Sexy::FVector2, float MinDistance = 0, ZombieType = (ZombieType)-1, bool IsBlacklist = false);
	Pickup* GetNearestPickup(Sexy::FVector2, float MinDistance = 0, PickupType = PICKUP_NONE, bool IsBlacklist = false);
	Plant* GetNearestPlant(Sexy::FVector2, float MinDistance = 0, SeedType = SEED_NONE, bool IsBlacklist = false);

	std::list<Projectile*> GetProjectilesInArea(Sexy::IRect, ProjectileType = (ProjectileType)-1, bool IsBlacklist = false);
	std::list<GridItem*> GetGridItemsInArea(Sexy::IRect, GridItemType = GRIDITEM_NONE, bool IsBlacklist = false);
	std::list<Zombie*> GetZombiesInArea(Sexy::IRect, ZombieType = (ZombieType)-1, bool IsBlacklist = false);
	std::list<Pickup*> GetPickupsInArea(Sexy::IRect, PickupType = PICKUP_NONE, bool IsBlacklist = false);
	std::list<Plant*> GetPlantsInArea(Sexy::IRect, SeedType = SEED_NONE, bool IsBlacklist = false);
#pragma endregion
};