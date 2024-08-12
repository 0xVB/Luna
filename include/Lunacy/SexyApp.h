#pragma once
#include <Windows.h>
#include "PopStructs.h"
#include "CGeometry.h"
#include "Listeners.h"
#include "Buffer.h"

class Sexy::SexyAppBase : public Sexy::ButtonListener, public Sexy::DialogListener
{
public:
#pragma region Fields
	unsigned int mRandSeed;
	PopString mCompanyName;
	PopString mFullCompanyName;
	PopString mProdName;
	PopString mTitle;
	PopString mRegKey;
	PopString mChangeDirTo;
	int mRelaxUpdateBacklogCount;
	int mPreferredX;
	int mPreferredY;
	int mWidth;
	int mHeight;
	int mFullscreenBits;
	long double mMusicVolume;
	long double mSfxVolume;
	long double mDemoMusicVolume;
	long double mDemoSfxVolume;
	bool mNoSoundNeeded;
	bool mWantFMod;
	bool mCmdLineParsed;
	bool mSkipSignatureChecks;
	bool mStandardWordWrap;
	bool mbAllowExtendedChars;
	void* mMutex;
	bool mOnlyAllowOneCopyToRun;
	unsigned int mNotifyGameMessage;
	_RTL_CRITICAL_SECTION mCritSect;
	bool mBetaValidate;
	unsigned __int8 mAdd8BitMaxTable[512];
	Sexy::UIRoot* mWidgetManager;
	PopMap<int, Sexy::UIDialog*> mDialogMap;
	PopList<Sexy::UIDialog*> mDialogList;
	unsigned int mPrimaryThreadId;
	bool mSEHOccured;
	bool mShutdown;
	bool mExitToTop;
	bool mIsWindowed;
	bool mIsPhysWindowed;
	bool mFullScreenWindow;
	bool mForceFullscreen;
	bool mForceWindowed;
	bool mInitialized;
	bool mProcessInTimer;
	unsigned int mTimeLoaded;
	HWND mHWnd;
	HWND mInvisHWnd;
	bool mIsScreenSaver;
	bool mAllowMonitorPowersave;
	PopList<tagMSG> mDeferredMessages;
	bool mNoDefer;
	bool mFullScreenPageFlip;
	bool mTabletPC;
	Sexy::DDInterface* mDDInterface;
	bool mAlphaDisabled;
	Sexy::MusicInterface* mMusicInterface;
	bool mReadFromRegistry;
	PopString mRegisterLink;
	PopString mProductVersion;
	Sexy::Image* mCursorImages[13];
	HICON mOverrideCursor;
	bool mIsOpeningURL;
	bool mShutdownOnURLOpen;
	PopString mOpeningURL;
	unsigned int mOpeningURLTime;
	unsigned int mLastTimerTime;
	unsigned int mLastBigDelayTime;
	long double mUnmutedMusicVolume;
	long double mUnmutedSfxVolume;
	int mMuteCount;
	int mAutoMuteCount;
	bool mDemoMute;
	bool mMuteOnLostFocus;
	PopSet<Sexy::MemoryImage*> mMemoryImageSet;
	PopMap<PopPair<PopString, PopString>, Sexy::SharedImage> mSharedImageMap;
	bool mCleanupSharedImages;
	int mNonDrawCount;
	int mFrameTime;
	bool mIsDrawing;
	bool mLastDrawWasEmpty;
	bool mHasPendingDraw;
	long double mPendingUpdatesAcc;
	long double mUpdateFTimeAcc;
	unsigned int mLastTimeCheck;
	unsigned int mLastTime;
	unsigned int mLastUserInputTick;
	int mSleepCount;
	int mDrawCount;
	int mUpdateCount;
	int mUpdateAppState;
	int mUpdateAppDepth;
	long double mUpdateMultiplier;
	bool mPaused;
	int mFastForwardToUpdateNum;
	bool mFastForwardToMarker;
	bool mFastForwardStep;
	unsigned int mLastDrawTick;
	unsigned int mNextDrawTick;
	int mStepMode;
	int mCursorNum;
	Sexy::SoundManager* mSoundManager;
	HICON mHandCursor;
	HICON mDraggingCursor;
	PopList<Sexy::UISafeDeleteInfo> mSafeDeleteList;
	bool mMouseIn;
	bool mRunning;
	bool mActive;
	bool mMinimized;
	bool mPhysMinimized;
	bool mIsDisabled;
	bool mHasFocus;
	int mDrawTime;
	unsigned int mFPSStartTick;
	int mFPSFlipCount;
	int mFPSDirtyCount;
	int mFPSTime;
	int mFPSCount;
	bool mShowFPS;
	int mShowFPSMode;
	int mScreenBltTime;
	bool mAutoStartLoadingThread;
	bool mLoadingThreadStarted;
	bool mLoadingThreadCompleted;
	bool mLoaded;
	bool mYieldMainThread;
	bool mLoadingFailed;
	bool mCursorThreadRunning;
	bool mSysCursor;
	bool mCustomCursorsEnabled;
	bool mCustomCursorDirty;
	bool mLastShutdownWasGraceful;
	bool mIsWideWindow;
	bool mWriteToSexyCache;
	bool mSexyCacheBuffers;
	int mNumLoadingThreadTasks;
	int mCompletedLoadingThreadTasks;
	bool mRecordingDemoBuffer;
	bool mPlayingDemoBuffer;
	bool mManualShutdown;
	PopString mDemoPrefix;
	PopString mDemoFileName;
	Sexy::Buffer mDemoBuffer;
	int mDemoLength;
	int mLastDemoMouseX;
	int mLastDemoMouseY;
	int mLastDemoUpdateCnt;
	bool mDemoNeedsCommand;
	bool mDemoIsShortCmd;
	int mDemoCmdNum;
	int mDemoCmdOrder;
	int mDemoCmdBitPos;
	bool mDemoLoadingComplete;
	PopMap<void*, int> mHandleToIntMap;
	int mCurHandleNum;
	PopList<PopString> mDemoMarkerList;
	bool mDebugKeysEnabled;
	bool mEnableMaximizeButton;
	bool mCtrlDown;
	bool mAltDown;
	bool mAllowAltEnter;
	int mSyncRefreshRate;
	bool mVSyncUpdates;
	bool mVSyncBroken;
	int mVSyncBrokenCount;
	unsigned int mVSyncBrokenTestStartTick;
	unsigned int mVSyncBrokenTestUpdates;
	bool mWaitForVSync;
	bool mSoftVSyncWait;
	bool mUserChanged3DSetting;
	bool mAutoEnable3D;
	bool mTest3D;
	unsigned int mMinVidMemory3D;
	unsigned int mRecommendedVidMemory3D;
	bool mWidescreenAware;
	bool mWidescreenTranslate;
	IRect mScreenBounds;
	bool mEnableWindowAspect;
	Ratio mWindowAspect;
	PopMap<PopString, PopString> mStringProperties;
	PopMap<PopString, PopString> mBoolProperties;
	PopMap<PopString, PopString> mIntProperties;
	PopMap<PopString, PopString> mDoubleProperties;
	PopMap<PopString, PopString> mStringVectorProperties;
	Sexy::ResourceManager* mResourceManager;
	int mOldWndProc;
	size_t mSexyAppBaseSize = sizeof(SexyAppBase);
#pragma endregion
#pragma region Virtual Functions
	virtual void __thiscall ButtonClick(int ID, int ClickType); // 0000
	virtual void __thiscall ButtonPress(int ID); // 0004
	virtual void __thiscall ButtonDepress(int ID);// 0008
	virtual void __thiscall ButtonDownTick(int ID);// 000C
	virtual void __thiscall ButtonMouseEnter(int ID);// 0010
	virtual void __thiscall ButtonMouseLeave(int ID);// 0014
	virtual void __thiscall ButtonMouseMove(int ID, int X, int Y);// 0018

	virtual void __thiscall DialogButtonPress(int DialogID, int ButtonID);
	virtual void __thiscall DialogButtonDepress(int DialogID, int ButtonID);

	virtual bool __thiscall Process(bool AllowSleep);// 001C
	virtual void __thiscall UpdateFrames();// 0020
	virtual bool __thiscall DoUpdateFrames();// 0024
	virtual void __thiscall DoUpdateFramesF(float Fraction);// 0028
	virtual void __thiscall MakeWindow();// 002C
	virtual void __thiscall EnforceCursor();// 0030
	virtual void __thiscall ReInitImages();// 0034
	virtual void __thiscall DeleteNativeImageData();// 0038
	virtual void __thiscall DeleteExtraImageData();// 003C
	virtual void __thiscall CheckUpdates();// 0040
	virtual ~SexyAppBase();// 0044
	virtual Sexy::MusicInterface* CreateMusicInterface(HWND Window);// 0048
	virtual void __thiscall InitHook();// 004C
	virtual void __thiscall D3DT2();// 0050
	virtual void __thiscall D3DT3();// 0054
	virtual void __thiscall LoadingThreadProc();// 0058
	virtual void __thiscall WriteToRegistery();// 005C
	virtual void __thiscall ReadFromRegistry();// 0060
	virtual UIDialog* __thiscall NewDialog(int ID, bool IsModal, const PopString& Header, const PopString& Content, const PopString& Footer, int ButtonLayout);// 0064
	virtual void __thiscall PreDisplayHook();// 0068
	virtual void __thiscall BeginPopup();// 006C
	virtual void __thiscall EndPopup();// 0070
	virtual void __thiscall WMsgBox(const PopWString& Text, const PopWString& Title, int Flags);// 0074
	virtual void __thiscall MsgBox(const PopString& Text, const PopString& Title, int Flags);// 0078
	virtual void __thiscall WPopup(const PopWString& Text);// 007C
	virtual void __thiscall Popup(const PopString& Text);// 0080
	virtual void __thiscall LogScreenSaverError(const PopString& Error);// 0084
	virtual void __thiscall SafeDeleteElement(UIElement* Element);// 0088
	virtual void __thiscall URLOpenFailed(const PopString& URL);// 008C
	virtual void __thiscall URLOpenSucceeded(const PopString& URL);// 0090
	virtual void __thiscall OpenURL(const PopString& URL, bool ShutdownAfter);// 0094
	virtual void __thiscall GetProductVersion(_Out_ PopString&& Out, const PopString& Path);// 0098
	virtual void __thiscall SEHOccured();// 009C
	virtual void __thiscall GetGameSEHInfo(_Out_ PopString&& Out);// 00A0
	virtual void __thiscall KeyUp(unsigned int KeyCode);// 00A4
	virtual void __thiscall ShutDown();// 00A8
	virtual void __thiscall DoParseCmdLine();// 00AC
	virtual void __thiscall ParseCmdLine(const PopString& Cmd);// 00B0
	virtual void __thiscall HandleCmdLineParam(const PopString& ParamName, const PopString& ParamValue);// 00B4
	virtual void __thiscall HandleNotifyGameMessage(int Type, int Param);// 00B8
	virtual void __thiscall HandleGameAlreadyRunning();// 00BC
	virtual void __thiscall Start();// 00C0
	virtual void __thiscall Init();// 00C4
	virtual void __thiscall D3DT6();// 00C8
	virtual void __thiscall D3DT7();// 00CC
	virtual void __thiscall ChangeDirHook(const char* Path);// 00D0
	virtual void __thiscall PlaySample(int SoundNum, int Pan);// 00D4
	virtual void __thiscall PlaySample(int SoundNum);// 00D8
	virtual double __thiscall GetMasterVolume();// 00DC
	virtual double __thiscall GetMusicVolume();// 00E0
	virtual double __thiscall GetSfxVolume();// 00E4
	virtual bool __thiscall IsMuted();// 00E8
	virtual void __thiscall SetMasterVolume(double Volume);// 00EC
	virtual void __thiscall SetMusicVolume(double Volume);// 00F0
	virtual void __thiscall SetSfxVolume(double Volume);// 00F4
	virtual void __thiscall Mute(bool AutoMute);// 00F8
	virtual void __thiscall Unmute(bool AutoMute);// 00FC
	virtual double GetLoadingThreadProgress();// 0100
	virtual DDImage* GetImage(const PopString& FileName, bool CommitBits);// 0104
	virtual SharedImageRef** __thiscall SetSharedImage(_Out_ SharedImageRef** Out, const PopString& FileName, const PopString& Variant, DDImage* Image, bool* IsNew);// 0108
	virtual SharedImage** __thiscall GetSharedImage(_Out_ SharedImageRef** Out, const PopString& FileName, const PopString& Variant, bool* IsNew);// 010C
	virtual void __thiscall SwitchScreenMode(bool WantWindowed, bool Is3D, bool Force);// 0110
	virtual void __thiscall SwitchScreenMode(bool WantWindowed);// 0114
	virtual void __thiscall SwitchScreenMode();// 0118
	virtual void __thiscall SetAlphaDisabled(bool Disabled);// 011C
	virtual UIDialog* __thiscall DoDialog(int DialogID, bool Modal, const PopString& Header, const PopString& Content, const PopString& Footer, int ButtonLayout);// 0120
	virtual UIDialog* __thiscall GetDialog(int DialogID);// 0124
	virtual void __thiscall AddDialog(UIDialog* ToAdd);// 0128
	virtual void __thiscall AddDialog(int DialogID, UIDialog* Dialog);// 012C
	virtual bool __thiscall KillDialog(UIDialog* Dialog);// 130
	virtual bool __thiscall KillDialog(int DialogID);// 134
	virtual bool __thiscall KillDialog(int DialogID, bool RemoveElement, bool DeleteElement);// 138
	virtual int __thiscall GetDialogCount();// 13C
	virtual void __thiscall D3DT8();// 0140
	virtual void __thiscall D3DT9();// 0144
	virtual void __thiscall D3DTA();// 0148
	virtual void __thiscall D3DTB();// 014C
	virtual void __thiscall IsAltKeyUsed(WPARAM Param);// 0150
	virtual bool __thiscall DebugKeyDown(unsigned int Key);// 0154
	virtual bool __thiscall DebugKeyDownAsync(unsigned int Key, bool CtrlDown, bool AltDown);// 0158
	virtual void __thiscall D3DTC();// 015C
	virtual void __thiscall D3DTD();// 0160
	virtual PopString&& __thiscall NotifyCrashHook(_Out_ PopString&& UploadFile);// 0164
	virtual bool __thiscall CheckSignature(const Buffer& Buffer, const PopString& FileName);// 0168
	virtual bool __thiscall DrawDirtyStuff();// 016C
	virtual void __thiscall Redraw(IRect* ClipRect = NULL);// 0170
	virtual void __thiscall D3DTE();// 0174
	virtual void __thiscall DoMainLoop();// 0178
	virtual bool __thiscall UpdateAppStep(bool* Updated);// 017C
	virtual void __thiscall UpdateApp();// 0180
	virtual bool __thiscall AppCanRestore();// 0184
	virtual bool __thiscall Unk();// 0188
#pragma endregion
};

class Sexy::SexyApp : public SexyAppBase
{
public:
	Sexy::InternetManager* mInternetManager;
	Sexy::BetaSupport* mBetaSupport;
	PopString mBetaSupportSiteOverride;
	PopString mBetaSupportProdNameOverride;
	PopString mReferID;
	PopString mVariation;
	unsigned long mDownloadID;
	PopString mRegSource;
	unsigned long mLastVerCheckQueryTime;
	bool mSkipAd;
	bool mDontUpdate;

	int mBuildNum;
	PopString mBuildDate;
	PopString mUserName;
	PopString mRegUserName;
	PopString mRegCode;
	bool mIsRegistered;
	bool mBuildUnlocked;

	int mTimesPlayed;
	int mTimesExecuted;
	bool mTimedOut;

	size_t mSexyAppSize = sizeof(SexyApp);

	virtual ~SexyApp();
};