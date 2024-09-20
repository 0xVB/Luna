#pragma once
#include "DataArray.h"
#include "CGeometry.h"

enum FilterEffect
{
	FILTER_EFFECT_NONE = 0xFFFFFFFF,
	FILTER_EFFECT_WASHED_OUT = 0x0,
	FILTER_EFFECT_LESS_WASHED_OUT = 0x1,
	FILTER_EFFECT_WHITE = 0x2,
	NUM_FILTER_EFFECTS = 0x3,
};

class ReanimatorTransform
{
public:
	union
	{
		struct
		{
			float mTransX;
			float mTransY;
		};
		Sexy::FVector2 mTrans;
	};
	union
	{
		struct
		{
			float mSkewX;
			float mSkewY;
		};
		Sexy::FVector2 mSkew;
	};
	union
	{
		struct
		{
			float mScaleX;
			float mScaleY;
		};
		Sexy::FVector2 mScale;
	};

	float mFrame;
	float mAlpha;
	Sexy::Image* mImage;
	Sexy::Font* mFont;
	char* mText;
};

class ReanimatorTrackInstance
{
public:
	int mBlendCounter;
	int mBlendTime;
	ReanimatorTransform mBlendTransform;
	float mShakeOverride;
	float mShakeX;
	float mShakeY;
	AttachmentID mAttachmentID;
	Sexy::Image* mImageOverride;
	int mRenderGroup;
	Sexy::Color mTrackColor;
	bool mIgnoreClipRect;
	bool mTruncateDisappearingFrames;
};

#define ReanimTime ReanimatorFrameTime
class ReanimTime
{
public:
	float mFraction = 0;
	int mAnimFrameBeforeInt = 0;
	int mAnimFrameAfterInt = 0;
};

class Reanimation
{
private:
	static void __stdcall CreateReanim(Reanimation*);

public:
	ReanimationType mReanimationType;
	float mAnimTime;
	float mAnimRate;
	ReanimatorDefinition* mDefinition;
	ReanimLoopType mLoopType;
	bool mDead;
	int mFrameStart;
	int mFrameCount;
	int mFrameBasePose;
	Sexy::Transform2D mOverlayMatrix;
	Sexy::Color mColorOverride;
	ReanimatorTrackInstance* mTrackInstances;
	int mLoopCount;
	ReanimationHolder* mReanimationHolder;
	bool mIsAttachment;
	int mRenderOrder;
	Sexy::Color mExtraAdditiveColor;
	bool mEnableExtraAdditiveDraw;
	Sexy::Color mExtraOverlayColor;
	bool mEnableExtraOverlayDraw;
	float mLastFrameTime;
	FilterEffect mFilterEffect;

	Reanimation();
	~Reanimation();
	
	void Initialize(float X, float Y, ReanimationType);
	void Initialize(float X, float Y, ReanimatorDefinition*);
	void Update();
	void SetTranslation(float X, float Y);
	void SetScale(float X, float Y);
	void SetSkew(float X, float Y);
	void TranslateBy(float X, float Y);
	void ScaleBy(float X, float Y);
	void SkewBy(float X, float Y);
	void RotateByRadians(float Radians);
	void RotateByDegrees(float Deg);
	void SetRotationRadians(float Radians);
	void SetRotationDegrees(float Deg);
	Sexy::FVector2 GetTranslation();
	Sexy::FVector2 GetScale();
	Sexy::FVector2 GetSkew();
	float GetRotationRadians();
	float GetRotationDegrees();
	// void GetCurrentTransform(int TrackIndex, ReanimatorTransform* CurrentTransform);
	// void GetTransformAtTime(int TrackIndex, ReanimatorTransform* Transform, ReanimatorFrameTime* Time);
	// void MatrixFromTransform(const ReanimatorTransform& Out, Sexy::Matrix3& Matrix);
	void AttachToAnotherReanim(Reanimation* OtherReanim, const char* TrackName);
	AttachEffect* AttachParticleToTrack(const char* TrackName, ParticleSystem* ParticleSystem, float X, float Y);
	void SetImageOverride(const char* TrackName, Sexy::Image* = nullptr);
	Sexy::Image* GetImageOverride(const char* TrackName);
	bool DrawTrack(Sexy::Graphics*, int TrackIndex, Sexy::TriangleGroup*);
	void Draw(Sexy::Graphics*, int RenderGroup = 0);
	void Die();

	/// <summary>
	/// THIS FUNCTION DOES NOT WORK!!
	/// It's supposed to extract a single frame from the reanim and output it as an image, but it causes
	/// SEVERE MEMORY LEAKS and has mediocre results. It's kept here to remind me to revisit it later.
	/// </summary>
	Sexy::DDImage* ExtractFrame(Sexy::DDImage* Out = nullptr, int RenderGroup = 0);
};

class ReanimatorTrack
{
public:
	char* mName;
	ReanimatorTransform* mTransforms;
	int mTransformCount;
};

class ReanimAtlasImage
{
public:
	union
	{
		struct
		{
			int mX;
			int mY;
			int mWidth;
			int mHeight;
		};
		struct
		{
			Sexy::IVector2 mPos;
			Sexy::IVector2 mSize;
		};
		Sexy::IRect mBounds;
	};
	Sexy::Image* mOriginalImage;
};

class ReanimAtlas
{
public:
	ReanimAtlasImage mImageArray[64];
	int mImageCount;
	Sexy::MemoryImage* mMemoryImage;
};

class ReanimationParams
{
public:
	ReanimationType mType;
	const char* mFileName;
	int mParamFlags;

	__inline ReanimationParams(ReanimationType Type, const char* FileName, int ParamFlags = 0)
	{
		mType = Type;
		mFileName = FileName;
		mParamFlags = ParamFlags;
	}
};

class ReanimatorDefinition
{
private:
	constexpr static ReanimatorDefinition** _defs = (ReanimatorDefinition**)0x6A9EE8;
	static ReanimationParams* _newParams;

	constexpr static DWORD _paramArray = 0x6A1340;
	constexpr static DWORD _paramArrayEnd = 0x6A19F4;
	constexpr static DWORD _paramArraySize = _paramArrayEnd - _paramArray;

	constexpr static DWORD _paramCount = 0x8F;
	constexpr static DWORD _countRefs[] =
	{
		0x48153C,
		0x47377E,
		0x4814F3
	};

	constexpr static DWORD _paramRefs[] =
	{
		0x4737A5,
		0x4737F5
	};

public:
	ReanimatorTrack* mTracks;
	int mTrackCount;
	float mFPS;
	ReanimAtlas* mReanimAtlas;

	// Must be called ONLY ONCE before ReanimatorLoadDefinitions.
	static void Reallocate(unsigned int NewCapacity);

	// Creates a new reanimation with the given ReanimationType.
	// Do not include the extension or the parent folder in the name.
	// Ex: "reanim\\Zombie" is valid, "compiled\\reanim\\Zombie.reanim.compiled" is not.
	// Reallocate MUST be called before this function can be called.
	static ReanimationParams* NewReanim(ReanimationType, const char* CompiledFileName);
};

class ReanimationHolder : public DataArray<Reanimation>
{ };