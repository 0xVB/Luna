#pragma once
#include "Lunacy/MSD3D/MSD3D.h"
#include "PopStructs.h"
#include "CGeometry.h"

class Sexy::Image
{
public:
	struct bColor
	{
		unsigned char b;
		unsigned char g;
		unsigned char r;
		unsigned char a;

		bColor(Color);
		operator Color() const;
	};

	bool mDrawn;
	PopString mFilePath;
	union
	{
		struct
		{
			int mWidth;
			int mHeight;
		};
		IVector2 mSize;
	};
	int mNumRows;
	int mNumCols;
	AnimInfo* mAnimInfo;

	Image();
	Image(const Image&);

	// Virtual functions
	virtual ~Image() {};// 00

	virtual bool PolyFill3D(const IVector2& Vertices, int VertexCount, const IRect& ClipRect, const Color& Color, int DrawMode, int Tx, int Ty, bool Convex) = 0;// 04
	virtual void FillRect(const IRect& Rect, const Color& Color, int DrawMode) = 0;// 08
	virtual void DrawRect(const IRect& Rect, const Color& Color, int DrawMode) = 0;// 0C
	virtual void ClearRect(const IRect& Rect) = 0;// 10
	virtual void DrawLine(double StartX, double StartY, double EndX, double EndY, const Color& Color, int DrawMode) = 0;// 14
	virtual void DrawLineAA(double StartX, double StartY, double EndX, double EndY, const Color&, int DrawMode) = 0;// 18
	virtual void FillScanLines(Span& Spans, int SpanCount, const Color& Color, int DrawMode) = 0;// 1C
	virtual void FillScanLinesWithCoverage(Span& Spans, int SpanCount, const Color& Color, int DrawMode, const unsigned char* Coverage, int CoverX, int CoverY, int CoverWidth, int CoverHeight) = 0;// 20
	virtual void Blt(Image* OtherImage, int X, int Y, const IRect& SrcRect, const Color& Color, int DrawMode) = 0;// 24
	virtual void BltF(Image* OtherImage, float X, float Y, const IRect& SrcRect, const IRect& ClipRect, const Color& Color, int DrawMode) = 0;// 28
	virtual void BltRotated(Image* OtherImage, float X, float Y, const IRect& SrcRect, const IRect& ClipRect, const Color& Color, int DrawMode, double Rotation, float RotCenterX, float RotCenterY) = 0;// 2C
	virtual void StretchBlt(Image* OtherImage, const IRect& DestRect, const IRect& SrcRect, const IRect& ClipRect, const Color& Color, int DrawMode, bool FastStretch) = 0;// 30
	virtual void BltMatrix(Image* OtherImage, float X, float Y, const Matrix3& Matrix, const IRect& ClipRect, const Color& Color, int DrawMode, const IRect& SrcRect, bool Blend) = 0;// 34
	virtual void BltTrianglesTex(Image* Texture, const TriVertex& Vertices, int TriangleCount, const IRect& ClipRect, const Color& Color, int DrawMode, float Tx, float Ty, bool Blend) = 0;// 38
	virtual void BltMirror(Image* OtherImage, int X, int Y, const IRect& SrcRect, const Color& Color, int DrawMode) = 0;// 3C
	virtual void StretchBltMirror(Image* OtherImage, const IRect& DestOrig, const IRect& SrcOrig, const IRect& ClipRect, const Color& Color, int DrawMode, bool FastStretch) = 0;// 40

	MemoryImage* GetHReflect();// Returns a new texture reflected across the y-axis.
	MemoryImage* GetVReflect();// Returns a new texture reflected across the x-axis.
	MemoryImage* GetOReflect();// Returns a new texture reflected across the origin.
	MemoryImage* GetScaled(int NewWidth, int NewHeight);// Returns a new texture scaled to the new width and height.
	MemoryImage* GetRotated(float Radians, int NewWidth = -1, int NewHeight = -1);// Returns a new texture rotated by the given angle in radians. Will use the image's default size if NewWidth and NewHeight aren't specified. They do not stretch the texture, but they determine the final size of the rotated texture to ensure it won't be clipped when rotated.
	MemoryImage* GetCropped(IRect Source);// Returns a new texture cropped by the given rectangle region.
};

class Sexy::MemoryImage : public Sexy::Image
{
private:
	unsigned int* mBits;

public:
	int mBitsChangedCount;
	void* mD3DData;
	unsigned int mD3DFlags;
	unsigned int* mColorTable;
	unsigned __int8* mColorIndices;
	bool mForcedMode;
	bool mHasTrans;
	bool mHasAlpha;
	bool mIsVolatile;
	bool mPurgeBits;
	bool mWantPal;
	unsigned int* mNativeAlphaData;
	unsigned __int8* mRLAlphaData;
	unsigned __int8* mRLAdditiveData;
	bool mBitsChanged;
	SexyAppBase* mApp;

	MemoryImage();
	MemoryImage(const MemoryImage&);
	MemoryImage(SexyAppBase*);

	virtual ~MemoryImage() {};

	virtual void*  GetNativeAlphaData(Sexy::NativeDisplay*) = 0;// 44
	virtual unsigned __int8*  GetRLAlphaData() = 0;// 48
	virtual unsigned __int8*  GetRLAdditiveData(Sexy::NativeDisplay*) = 0; // 4C
	virtual void PurgeBits() = 0;// 50
	virtual void DeleteSWBuffers() = 0; // 54
	virtual void Delete3DBuffers() = 0;// 58
	virtual void DeleteExtraBuffers() = 0;// 5C
	virtual void ReInit() = 0;// 60
	virtual void BitsChanged() = 0;// 64
	virtual void CommitBits() = 0;// 68
	virtual void DeleteNativeData() = 0;// 6C
	virtual void Clear() = 0;// 70
	virtual void SetBits(unsigned int*, int, int, bool) = 0;// 74
	virtual void Create(int, int) = 0;// 78
	virtual unsigned int*  GetBits() = 0;// 7C
	virtual void SetImageMode(bool, bool) = 0;// 80
	virtual void SetVolatile(bool) = 0;// 84
	virtual bool Palletize() = 0;// 88

	void CopyImage(MemoryImage* OtherImage, bool CommitBits = false);

	bColor* GetPixels();
	MemoryImage* Blend(MemoryImage* ColorMap, MemoryImage* Destination = nullptr, float Alpha = 0.35f, int X = 0, int Y = 0);
	void BlendWith(MemoryImage* ColorMap, float Alpha = 0.35f, int X = 0, int Y = 0);

	static MemoryImage* __stdcall New(int Width = 800, int Height = 600);
};

class Sexy::DDImage : public Sexy::MemoryImage
{
public:
	Sexy::DDInterface* mDDInterface;
	IDirectDrawSurface* mSurface;
	bool mSurfaceSet;
	bool mNoLock;
	bool mVideoMemory;
	bool mFirstPixelTrans;
	bool mWantDDSurface;
	bool mDrawToBits;
	int mLockCount;
	_DDSURFACEDESC mLockedSurfaceDesc;

	DDImage();
	DDImage(DDInterface*);

	// Virtual Functions
	virtual ~DDImage() {};

	virtual void SetVideoMemory(bool) = 0;// 8C
	virtual void RehupFirstPixelTrans() = 0;// 90
	virtual void NormalFillRect(const IRect&, const Color&) = 0;// 94
	virtual void AdditiveFillRect(const IRect&, const Color&) = 0;// 98
	virtual void NormalBlt(Image*, int, int, const IRect&, const Color&) = 0;// 9C
	virtual void AdditiveBlt(Image*, int, int, const IRect&, const Color&) = 0;// A0
	virtual void NormalDrawLine(long double, long double, long double, long double, const Color&) = 0;// A4
	virtual void AdditiveDrawLine(long double, long double, long double, long double, const Color&) = 0;// A8
	virtual void NormalDrawLineAA(long double, long double, long double, long double, const Color&) = 0;// AC
	virtual void AdditiveDrawLineAA(long double, long double, long double, long double, const Color&) = 0;// B0
	virtual void NormalBltMirror(Image*, int, int, const IRect&, const Color&) = 0;// B4
	virtual void AdditiveBltMirror(Image*, int, int, const IRect&, const Color&) = 0;// B8
	virtual bool LockSurface() = 0;// BC
	virtual bool UnlockSurface() = 0;// C0
	virtual void SetSurface(IDirectDrawSurface*) = 0;// C4
	virtual void WriteToCache(const PopString&, const PopString&) = 0;// C8

	static DDImage* New(int Width = 800, int Height = 600);
};

class Sexy::SharedImage
{
public:
	DDImage* mImage;
	int mRefCount;
};

class Sexy::SharedImageRef
{
public:
	SharedImage* mSharedImage;
	MemoryImage* mUnsharedImage;
	bool mOwnsUnshared;
};