#pragma once
#include "PopStructs.h"
#include "CGeometry.h"

class Sexy::GraphicsState
{
public:
	Sexy::Image* mDestImage;
	FVector2 mTranslation;
	FVector2 mScale;
	FVector2 mScaleOrig;
	IRect mClipRect;
	Color mColor;
	Font* mFont;
	int mDrawMode;
	bool mColorizeImages;
	bool mFastStretch;
	bool mWriteColoredString;
	bool mLinearBlend;
	bool mIs3D;
};


class Sexy::Graphics : public Sexy::GraphicsState
{
public:
	Edge* mPFActiveEdgeList;
	int mPFNumActiveEdges;
	int mPFNumVertices;
	PopList<Sexy::GraphicsState> mStateStack;

	// Members
	enum Alignment
	{
		LEFT = -1,
		CENTER = 0,
		RIGHT = 1
	};

	// Methods
	virtual ~Graphics() {};

	void PushState();
	void PopState();
	Graphics* Create();

	// Drawing Functions
	void FillRect(int X, int Y, int Width, int Height);
	void DrawRect(int X, int Y, int Width, int Height);
	void FillRect(const IRect&);
	void DrawRect(const IRect&);

	void DrawImage(Image*, int X, int Y, const IRect& Src, double Rotation, const IRect& Clip, Color* Color, int RotCenterX, int RotCenterY);
	void DrawImage(Image*, int X, int Y, const IRect& SourceRect);
	void DrawImage(Image*, int X, int Y, int Width, int Height);
	void DrawImage(Image*, int X, int Y);

	void DrawTriangles(Image* Texture, const TriVertex& Vertices, int TriangleCount);
	void DrawImageCel(Image*, int X, int Y, int Col, int Row = 0);

	// String Drawing
	void DrawString(const PopString&, int X, int Y);
	int WriteWordWrapped(const PopString&, const IRect& TextArea, int LineSpacing = -1, Alignment = CENTER);
	int GetWrappedWordHeight(const PopString&, int TextAreaWidth, int LineSpacing);
};