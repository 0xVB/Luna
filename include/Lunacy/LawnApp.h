#pragma once
#include "SexyApp.h"

class CrazyDave
{
public:
	ReanimationID AnimationID;
	CrazyDaveState State;
	int BlinkCounter;
	ReanimationID BlinkAnimationID;
	int MessageIndex;
	PopString Message;
};

class LawnApp : public Sexy::SexyApp
{
#pragma region Fields
public:
	Lawn* mLawn;
	LoadingScreen* mLoadingScreen;
	MainMenu* mMainMenu;
	SeedChooser* mSeedChooser;
	AwardScreen* mAwardScreen;
	CreditScreen* mCreditScreen;
	ChallengeScreen* mChallengeScreen;
	SoundSystem* mSoundSystem;

	PopList<Sexy::UIButton> mControlButtonList;
	PopList<Sexy::Image> mCreatedImageList;
	PopString mReferID;
	PopString mRegisterLink;
	PopString mMod;
	bool mRegisterResourcesLoaded;
	bool mCheatKeys;

	GameMode mGameMode;
	GameScenes mGameScene;
	bool mLoadingZombiesThreadCompleted;
	bool mIsNewUser;
	int mGamesPlayed;
	int mMaxExecutions;
	int mMaxPlays;
	int mMaxTime;
	bool mEasyPlantingCheat;

	PoolEffect* mPoolEffect;
	ZenGarden* mZenGarden;
	EffectSystem* mEffectSystem;
	ReanimatorCache* mReanimatorCache;
	ProfileManager* mProfileManager;
	UserData* mUserData;
	LevelStats* mLastLevelStats;
	bool mCloseRequest;

	int mAppCounter;
	Music* mMusic;
	CrazyDave mCrazyDave;

	int mRandAppSeed;
	HICON mBigArrowCursor;
	PopDRM* mDRM;
	int mSessionID;
	int mPlaytimeActiveSession;
	int mPlaytimeInactiveSession;
	GameResult mGameResult;
	bool mKilledYetiAndRestarted;

	TypingCheck* mKonamiCheck;
	TypingCheck* mMustacheCheck;
	TypingCheck* mMoustacheCheck;
	TypingCheck* mSuperMowerCheck;
	TypingCheck* mSuperMowerCheck2;
	TypingCheck* mFutureCheck;
	TypingCheck* mPinataCheck;
	TypingCheck* mDanceCheck;
	TypingCheck* mDaisyCheck;
	TypingCheck* mSukhbirCheck;

	bool mMustacheMode;
	bool mSuperMowerMode;
	bool mFutureMode;
	bool mPinataMode;
	bool mDanceMode;
	bool mDaisyMode;
	bool mSukhbirMode;

	size_t mLawnAppSize = sizeof(LawnApp);
#pragma endregion
	static LawnApp* GetApp();

	int LawnMessageBox(int ID, const char* Head, const char* Body, const char* B1, const char* B2, int ButtonMode = 1);
	Reanimation* AddReanim(ReanimationType, float X, float Y, int Layer = 400000);
	ParticleSystem* __thiscall AddParticles(ParticleEffect, float X, float Y, int Layer = 400000);
};