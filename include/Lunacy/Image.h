#pragma once
#include "ForwardDefinitions.h"
#include "PopStructs.h"
#include "CGeometry.h"

class Sexy::Image
{
	bool mDrawn;
	PopString mFilePath;
	int mWidth;
	int mHeight;
	int mNumRows;
	int mNumCols;
	AnimInfo* mAnimInfo;

	// Virtual functions
	virtual ~Image() {};
	virtual bool PolyFill3D(const IVector2& Vertices, int VertexCount, const IRect& ClipRect, const Color& Color, int DrawMode, int Tx, int Ty, bool Convex) {};
	virtual void FillRect(const IRect& Rect, const Color& Color, int DrawMode) {};
	virtual void DrawRect(const IRect& Rect, const Color& Color, int DrawMode) {};
	virtual void ClearRect(const IRect& Rect) {};
	virtual void DrawLine(double StartX, double StartY, double EndX, double EndY, const Color& Color, int DrawMode) {};
	virtual void DrawLineAA(double StartX, double StartY, double EndX, double EndY, const Color&, int DrawMode) {};
	virtual void FillScanLines(Span& Spans, int SpanCount, const Color& Color, int DrawMode) {};
	virtual void FillScanLinesWithCoverage(Span& Spans, int SpanCount, const Color& Color, int DrawMode, const unsigned char* Coverage, int CoverX, int CoverY, int CoverWidth, int CoverHeight) {};
	virtual void Blt(Image* OtherImage, int X, int Y, const IRect& SrcRect, const Color& Color, int DrawMode) {};
	virtual void BltF(Image* OtherImage, float X, float Y, const IRect& SrcRect, const IRect& ClipRect, const Color& Color, int DrawMode) {};
	virtual void BltRotated(Image* OtherImage, float X, float Y, const IRect& SrcRect, const IRect& ClipRect, const Color& Color, int DrawMode, double Rotation, float RotCenterX, float RotCenterY) {};
	virtual void StretchBlt(Image* OtherImage, const IRect& DestRectOrig, const IRect& SrcRectOrig, const IRect& ClipRect, const Color& Color, int DrawMode, bool FastStretch) {};
	virtual void BltMatrix(Image* OtherImage, float X, float Y, const Matrix3& Matrix, const IRect& ClipRect, const Color& Color, int DrawMode, const IRect& SrcRect, bool Blend) {};
	virtual void BltTrianglesTex(Image* Texture, const TriVertex& Vertices, int TriangleCount, const IRect& ClipRect, const Color& Color, int DrawMode, float Tx, float Ty, bool Blend) {};
	virtual void BltMirror(Image* OtherImage, int X, int Y, const IRect& SrcRect, const Color& Color, int DrawMode) {};
	virtual void StretchBltMirror(Image* OtherImage, const IRect& DestOrig, const IRect& SrcOrig, const IRect& ClipRect, const Color& Color, int DrawMode, bool FastStretch) {};
};