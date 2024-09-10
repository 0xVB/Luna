#pragma once
#include "TodLib.h"
#include "DataArray.h"
#include "Listeners.h"
#include "UIElement.h"

class HitResult
{
public:
	void* aObject;
	GameObjectType mType;
};

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
	GridItem* GetGridItemAt(int Col, int Row, GridItemType = GRIDITEM_NONE);

	int CountGraves();

	Pickup* NewPickup(int X, int Y, PickupType, PickupMotion = PICKUP_MOTION_COIN);
	Pickup* NewPickup(PickupType, int X, int Y, PickupMotion = PICKUP_MOTION_COIN);
	Pickup* NewPacket(SeedType, int X, int Y);

	Zombie* NewZombie(ZombieType, int Lane, int FromWave = 0);
	void KillAllZombies(int Col = -1, int Row = -1, ZombieType = ZOMBIE_NONE, bool DropLoot = false);
	void __inline KillAllZombies(ZombieType Type, int Col = -1, int Row = -1, bool DropLoot = false) { KillAllZombies(Col, Row, Type, DropLoot); }
	void SpawnZombiesFromPool();
	void SpawnZombiesFromSky();
	void SpawnZombiesFromGrave();

	Plant* NewPlant(int Column, int Lane, SeedType, SeedType ImitaterType);
	void DoPlantingEffects(int Column, int Lane, Plant*);
	void KillAllPlants(int Col = -1, int Row = -1, SeedType = SEED_NONE);
	void __inline KillAllPlants(SeedType Type, int Col = -1, int Row = -1) { KillAllPlants(Col, Row, Type); }
	Plant* GetPlantAt(int Col, int Row, SeedType = SEED_NONE);

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

	Projectile* GetNearestProjectile(Sexy::FVector2, float MinDistance = 0, float MaxDistance = 9e5, ProjectileType Filter = PROJECTILE_NONE, bool IsBlacklist = false);
	GridItem* GetNearestGridItem(Sexy::FVector2, float MinDistance = 0, float MaxDistance = 9e5, GridItemType = GRIDITEM_NONE, bool IsBlacklist = false);
	Zombie* GetNearestZombie(Sexy::FVector2, float MinDistance = 0, float MaxDistance = 9e5, ZombieType = ZOMBIE_NONE, bool IsBlacklist = false);
	Pickup* GetNearestPickup(Sexy::FVector2, float MinDistance = 0, float MaxDistance = 9e5, PickupType = PICKUP_NONE, bool IsBlacklist = false);
	Plant* GetNearestPlant(Sexy::FVector2, float MinDistance = 0, float MaxDistance = 9e5, SeedType = SEED_NONE, bool IsBlacklist = false);

	std::list<Projectile*> GetProjectilesInArea(Sexy::IRect, ProjectileType = PROJECTILE_NONE, bool IsBlacklist = false);
	std::list<GridItem*> GetGridItemsInArea(Sexy::IRect, GridItemType = GRIDITEM_NONE, bool IsBlacklist = false);
	std::list<Zombie*> GetZombiesInArea(Sexy::IRect, ZombieType = ZOMBIE_NONE, bool IsBlacklist = false);
	std::list<Pickup*> GetPickupsInArea(Sexy::IRect, PickupType = PICKUP_NONE, bool IsBlacklist = false);
	std::list<Plant*> GetPlantsInArea(Sexy::IRect, SeedType = SEED_NONE, bool IsBlacklist = false);
#pragma endregion
#pragma region Base Methods
	Lawn(LawnApp*);
	void Dispose();
	
	int CountPlants(SeedType = SEED_NONE);
	bool AreEnemiesOnScreen();
	int CountEnemiesOnScreen();
	int CountLawnMowers();
	
	void TrySaveGame();
	bool NeedSaveGame();
	bool LoadGame(PopString& FileName);

	GridItem* GetRake();
	bool CanAddGraveAt(int Col, int Row);
	
	int GetNumWavesPerFlag();
	bool IsFlagWave(int WaveNumber);

	static bool __stdcall CanZombieSpawnOnLevel(ZombieType, int Level);
	ZombieType GetIntroducedZombieType();
	bool LaneCanHaveZombie(int Row, ZombieType);
	void InitZombieWavesForLevel(int Level);
	int PickLaneForNewZombie(ZombieType);
	void RemoveZombiesForRepick();
	void RemoveCutsceneZombies();
	bool ChooseSeedsForLevel();
	void InitSurvivalStage();
	void RemoveAllZombies();
	void PickZombieWaves();
	void InitZombieWaves();
	void InitLawnMowers();
	bool CanAddBobsled();
	void StartLevel();
	void InitLevel();
	void PlaceRake();

	void SetEffectsPlaying(bool);
	int GetLevelRandSeed();
	void LoadBackground();
	void PickBackground();

	void GetShovelButtonRect(Sexy::IRect*);
	void GetZenButtonRect(GameObjectType, Sexy::IRect*);
	Sexy::IRect __inline GetShovelButtonRect()
	{
		Sexy::IRect aRect;
		GetShovelButtonRect(&aRect);
		return aRect;
	}
	Sexy::IRect __inline GetZenButtonRect(GameObjectType Type)
	{
		Sexy::IRect aRect;
		GetZenButtonRect(Type, &aRect);
		return aRect;
	}

	void FadeOutLevel();
	bool IsPlantEquipped();
	SeedType GetEquippedPlantType();
	void RefreshEquippedSeed();

	bool CanPlantAt(int Col, int Row, SeedType);
	bool IsPoolCell(int Col, int Row);
	bool IsIceCell(int Col, int Row);

	void PlantHitTest(int MouseX, int MouseY, HitResult*);
	void MouseHitTest(int, int, HitResult*);

	GridItem* GridItemHitTest(int MouseX, int MouseY);
	Zombie* ZombieHitTest(int MouseX, int MouseY);
	Plant* PlantHitTest(int MouseX, int MouseY);
	Plant* SpecialPlantHitTest(int MouseX, int MouseY);

	void PickUpTool(GameObjectType);
	bool CanInteractWithButtons();
	void SetPause(bool);
	void ClearCursor();
	void HighlightPlantsForMouse(int X, int Y);
	void PickSpecialGraveStone();

	void UpdateMousePosition();
	void UpdateToolTip();
	void MouseDownWithPlant(int X, int Y, ClickCode);
	void MouseDownCobcannonFire(int X, int Y, ClickCode);
	void MouseDownWithTool(int X, int Y, ClickCode, CursorType);

	void ShowTutorialArrow(int X, int Y);
	void RemoveTutorialArrow();

	int GetWaveHealth(int WaveIndex);
	int __inline GetWaveHealth() { return GetWaveHealth(mCurrentWave); }
	void SpawnNextWave();
	void StopZombieSounds();
	int GetSurvivalFlagsCompleted();
	void ZombiesWon(Zombie*);
	void __inline ZombiesWon() { ZombiesWon(NewZombie(ZOMBIE_NORMAL, 0)); }

	bool IsFinalSurvivalStage();
	bool IsFinalScaryPotterStage();
	bool IsSurvivalStageWithRepick();
	bool IsLastStandStageWithRepick();
	bool LevelAwardDropped();
	void UpdateSunSkyfall();
	void UpdateZombieSpawning();
	void UpdateIce();
	void UpdateProgressMeter();
	bool CanSpawnZombiesInLane(int Lane);
	bool HasProgressMeter();
	bool ProgressMeterHasFlags();

	void ClearFogAroundPlant(Plant*, int Size);
	void UpdateFog();

	void DrawZenWheelBarrowButton(Sexy::Graphics*, int YOffset);
	void DrawIce(Sexy::Graphics*, int Lane);
	void DrawBackground(Sexy::Graphics*);
	void DrawProgressMeter(Sexy::Graphics*);
	void DrawHouseDoorBottom(Sexy::Graphics*);
	void DrawHouseDoorTop(Sexy::Graphics*);
	void DrawLevelName(Sexy::Graphics*);
	void DrawZenButtons(Sexy::Graphics*);
	void DrawShovel(Sexy::Graphics*);
	void DrawDebugText(Sexy::Graphics*);
	void DrawObjectRects(Sexy::Graphics*);
	void DrawFadeOut(Sexy::Graphics*);
	void DrawTopRightUI(Sexy::Graphics*);
	void DrawBottomUI(Sexy::Graphics*);
	void DrawCoinBank(Sexy::Graphics*);
	void DrawFog(Sexy::Graphics*);
	void DrawTopUI(Sexy::Graphics*);

	void SetMustacheMode(bool);
	void SetFutureMode(bool);
	void SetPinataMode(bool);
	void SetDanceMode(bool);
	void SetSuperMowerMode(bool);

	void AddSun(int);
	bool TakeSun(int);
	bool CanTakeSun(int);
	int GetSunBeingCollected();
	int GetCoinsBeingCollected();
	int GetNumSeedsInBank();
	int GetNumWavesPerSurvivalStage();
	void RemoveParticleSystemByType(ParticleEffect);

	bool IsConveyorBeltLevel();
	bool StageHasGraves();
	bool IsNightStage();
	bool StageHasRoof();
	bool StageHasPool();
	bool StageHasFog();
	int LeftFogColumn();
	bool StageHasZombiesWalkInFromRight();
	int GetSeedPacketXPosition(int PacketIndex);
	int GetSeedBankExtraWidth();
	Plant* FindUmbrellaPlant(int Col, int Row);

	bool SeedNotRecommendedForLevel(SeedType);
	bool CanDropLoot();
	bool IsBungeeTargetingCell(int Col, int Row);
	Zombie* GetZomboss();
	void DoFwoosh(int Row);
	void UpdateFwoosh();
	bool PlantingRequirementsMet(SeedType);
	bool PlantUsesAcceleratedPricing(SeedType);
	int GetCurrentPlantCost(SeedType Type, SeedType ImitaterType = SeedType::SEED_NONE);

#pragma endregion

};