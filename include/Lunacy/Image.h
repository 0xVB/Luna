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
	void FillRect(const IRect& Rect, const Color& Color, int DrawMode) {};
	void DrawRect(const IRect& Rect, const Color& Color, int DrawMode) {};
	void ClearRect(const IRect& Rect) {};
	void DrawLine(double StartX, double StartY, double EndX, double EndY, const Color& Color, int DrawMode) {};
	void DrawLineAA(double StartX, double StartY, double EndX, double EndY, const Color&, int DrawMode) {};
	void FillScanLines(Span& Spans, int SpanCount, const Color& Color, int DrawMode) {};
	void FillScanLinesWithCoverage(Span& Spans, int SpanCount, const Color& Color, int DrawMode, const unsigned char* Coverage, int CoverX, int CoverY, int CoverWidth, int CoverHeight) {};
	void Blt(Image* OtherImage, int X, int Y, const IRect& SrcRect, const Color& Color, int DrawMode) {};
	void BltF(Image* OtherImage, float X, float Y, const IRect& SrcRect, const IRect& ClipRect, const Color& Color, int DrawMode) {};
	void BltRotated(Image* OtherImage, float X, float Y, const IRect& SrcRect, const IRect& ClipRect, const Color& Color, int DrawMode, double Rotation, float RotCenterX, float RotCenterY) {};
	void StretchBlt(Image* OtherImage, const IRect& SrcRect, const IRect& DestRect, const IRect&, const Color*, int, bool);
	void BltMatrix(Image*, float, float, const SexyMatrix3*, const IRect*, const Color*, int, const IRect*, bool);
	void BltTrianglesTex(Image*, const TriVertex(*)[], int, const IRect*, const Color*, int, float, float, bool);
	void BltMirror(Image*, int, int, const IRect*, const Color*, int);
	void StretchBltMirror(Image*, const IRect*, const IRect*, const IRect*, const Color*, int, bool);
	
};
