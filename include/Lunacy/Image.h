#pragma once
#include "Lunacy/MSD3D/MSD3D.h"
#include "PopStructs.h"
#include "CGeometry.h"

class Sexy::Image
{
public:
	bool mDrawn;
	PopString mFilePath;
	int mWidth;
	int mHeight;
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
	virtual void StretchBlt(Image* OtherImage, const IRect& DestRectOrig, const IRect& SrcRectOrig, const IRect& ClipRect, const Color& Color, int DrawMode, bool FastStretch) = 0;// 30
	virtual void BltMatrix(Image* OtherImage, float X, float Y, const Matrix3& Matrix, const IRect& ClipRect, const Color& Color, int DrawMode, const IRect& SrcRect, bool Blend) = 0;// 34
	virtual void BltTrianglesTex(Image* Texture, const TriVertex& Vertices, int TriangleCount, const IRect& ClipRect, const Color& Color, int DrawMode, float Tx, float Ty, bool Blend) = 0;// 38
	virtual void BltMirror(Image* OtherImage, int X, int Y, const IRect& SrcRect, const Color& Color, int DrawMode) = 0;// 3C
	virtual void StretchBltMirror(Image* OtherImage, const IRect& DestOrig, const IRect& SrcOrig, const IRect& ClipRect, const Color& Color, int DrawMode, bool FastStretch) = 0;// 40
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

	virtual bool PolyFill3D(const IVector2&, int, const IRect&, const Color&, int, int, int, bool) = 0;
	virtual void FillRect(const IRect&, const Color&, int) = 0;
	virtual void DrawRect(const IRect&, const Color&, int) = 0;
	virtual void ClearRect(const IRect&) = 0;
	virtual void DrawLine(long double, long double, long double, long double, const Color&, int) = 0;
	virtual void DrawLineAA(long double, long double, long double, long double, const Color&, int) = 0;
	virtual void FillScanLines(Span*, int, const Color&, int) = 0;
	virtual void FillScanLinesWithCoverage(Span*, int, const Color&, int, const unsigned __int8*, int, int, int, int) = 0;
	virtual void Blt(Image*, int, int, const IRect&, const Color&, int) = 0;
	virtual void BltF(Image*, float, float, const IRect&, const IRect&, const Color&, int) = 0;
	virtual void BltRotated(Image*, float, float, const IRect&, const IRect&, const Color&, int, long double, float, float) = 0;
	virtual void StretchBlt(Image*, const IRect&, const IRect&, const IRect&, const Color&, int, bool) = 0;
	virtual void BltMatrix(Image*, float, float, const Matrix3&, const IRect&, const Color&, int, const IRect&, bool) = 0;
	virtual void BltTrianglesTex(Image*, const Sexy::TriVertex(*)[], int, const IRect&, const Color&, int, float, float, bool) = 0;
	virtual void BltMirror(Image*, int, int, const IRect&, const Color&, int) = 0;
	virtual void StretchBltMirror(Image*, const IRect&, const IRect&, const IRect&, const Color&, int, bool) = 0;
	virtual void*  GetNativeAlphaData(Sexy::NativeDisplay*) = 0;
	virtual unsigned __int8*  GetRLAlphaData() = 0;
	virtual unsigned __int8*  GetRLAdditiveData(Sexy::NativeDisplay*) = 0;
	virtual void PurgeBits() = 0;
	virtual void DeleteSWBuffers() = 0;
	virtual void Delete3DBuffers() = 0;
	virtual void DeleteExtraBuffers() = 0;
	virtual void ReInit() = 0;
	virtual void BitsChanged() = 0;
	virtual void CommitBits() = 0;
	virtual void DeleteNativeData() = 0;
	virtual void Clear() = 0;
	virtual void SetBits(unsigned int*, int, int, bool) = 0;
	virtual void Create(int, int) = 0;
	virtual unsigned int*  GetBits() = 0;
	virtual void SetImageMode(bool, bool) = 0;
	virtual void SetVolatile(bool) = 0;
	virtual bool Palletize() = 0;
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

	virtual bool PolyFill3D(const IVector2&, int, const IRect&, const Color&, int, int, int, bool) = 0;
	virtual void FillRect(const IRect&, const Color&, int) = 0;
	virtual void DrawRect(const IRect&, const Color&, int) = 0;
	virtual void ClearRect(const IRect&) = 0;
	virtual void DrawLine(long double, long double, long double, long double, const Color&, int) = 0;
	virtual void DrawLineAA(long double, long double, long double, long double, const Color&, int) = 0;
	virtual void FillScanLines(Span*, int, const Color&, int) = 0;
	virtual void FillScanLinesWithCoverage(Span*, int, const Color&, int, const unsigned __int8*, int, int, int, int) = 0;
	virtual void Blt(Image*, int, int, const IRect&, const Color&, int) = 0;
	virtual void BltF(Image*, float, float, const IRect&, const IRect&, const Color&, int) = 0;
	virtual void BltRotated(Image*, float, float, const IRect&, const IRect&, const Color&, int, long double, float, float) = 0;
	virtual void StretchBlt(Image*, const IRect&, const IRect&, const IRect&, const Color&, int, bool) = 0;
	virtual void BltMatrix(Image*, float, float, const Matrix3&, const IRect&, const Color&, int, const IRect&, bool) = 0;
	virtual void BltTrianglesTex(Image*, const Sexy::TriVertex(*)[], int, const IRect&, const Color&, int, float, float, bool) = 0;
	virtual void BltMirror(Image*, int, int, const IRect&, const Color&, int) = 0;
	virtual void StretchBltMirror(Image*, const IRect&, const IRect&, const IRect&, const Color&, int, bool) = 0;
	virtual void*  GetNativeAlphaData(Sexy::NativeDisplay*) = 0;
	virtual unsigned __int8*  GetRLAlphaData() = 0;
	virtual unsigned __int8*  GetRLAdditiveData(Sexy::NativeDisplay*) = 0;
	virtual void PurgeBits() = 0;
	virtual void DeleteSWBuffers() = 0;
	virtual void Delete3DBuffers() = 0;
	virtual void DeleteExtraBuffers() = 0;
	virtual void ReInit() = 0;
	virtual void BitsChanged() = 0;
	virtual void CommitBits() = 0;
	virtual void DeleteNativeData() = 0;
	virtual void Clear() = 0;
	virtual void SetBits(unsigned int*, int, int, bool) = 0;
	virtual void Create(int, int) = 0;
	virtual unsigned int*  GetBits() = 0;
	virtual void SetImageMode(bool, bool) = 0;
	virtual void SetVolatile(bool) = 0;
	virtual bool Palletize() = 0;
	virtual void SetVideoMemory(bool) = 0;
	virtual void RehupFirstPixelTrans() = 0;
	virtual void NormalFillRect(const IRect&, const Color&) = 0;
	virtual void AdditiveFillRect(const IRect&, const Color&) = 0;
	virtual void NormalBlt(Image*, int, int, const IRect&, const Color&) = 0;
	virtual void AdditiveBlt(Image*, int, int, const IRect&, const Color&) = 0;
	virtual void NormalDrawLine(long double, long double, long double, long double, const Color&) = 0;
	virtual void AdditiveDrawLine(long double, long double, long double, long double, const Color&) = 0;
	virtual void NormalDrawLineAA(long double, long double, long double, long double, const Color&) = 0;
	virtual void AdditiveDrawLineAA(long double, long double, long double, long double, const Color&) = 0;
	virtual void NormalBltMirror(Image*, int, int, const IRect&, const Color&) = 0;
	virtual void AdditiveBltMirror(Image*, int, int, const IRect&, const Color&) = 0;
	virtual bool LockSurface() = 0;
	virtual bool UnlockSurface() = 0;
	virtual void SetSurface(IDirectDrawSurface*) = 0;
	virtual void WriteToCache(const PopString&, const PopString&) = 0;
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