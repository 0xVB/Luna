#pragma once
#include "ForwardDefinitions.h"

#ifndef CGEOMETRY_DEFINED
#define CGEOMETRY_DEFINED
#define Z_INVERTED 1

#define IVector2 Vector2<int>
#define FVector2 Vector2<float>

#define IVector3 Vector3<int>
#define FVector3 Vector3<float>

#define IRect Rect<int>
#define FRect Rect<float>

#include "Rect.h"

class Sexy::Color
{
public:
	int mRed;
	int mGreen;
	int mBlue;
	int mAlpha;

	Color(int, int, int, int);
};

class Sexy::Padding
{
public:
	int mLeft;
	int mTop;
	int mRight;
	int mBottom;

	Padding(int Left, int Top, int Right, int Bottom);
};

class Sexy::Matrix3
{
public:
	union
	{
		float m[3][3];
		struct
		{
			float m00;
			float m01;
			float m02;
			float m10;
			float m11;
			float m12;
			float m20;
			float m21;
			float m22;
		};
	};

	Matrix3();
	Matrix3(float, float, float, float, float, float, float, float, float);
};

class Sexy::Ratio
{
public:
	int mNumerator;
	int mDenominator;

	Ratio(int = 0, int = 1);
};

class Sexy::Transform2D : public Sexy::Matrix3
{
};

class Sexy::Transform
{
public:
	Transform2D mMatrix;
	bool mNeedCalcMatrix;
	bool mComplex;
	bool mHaveRot;
	bool mHaveScale;
	float mTransX1;
	float mTransY1;
	float mTransX2;
	float mTransY2;
	float mScaleX;
	float mScaleY;
	float mRot;
};

class Sexy::Span
{
public:
	int mY;
	int mX;
	int Width;

	Span(int Y, int X, int W);
};

class Sexy::Edge
{
public:
	long double mX;
	long double mDX;
	int i;
	long double b;

	Edge();
};

class Sexy::TriVertex
{
public:
	float x;
	float y;
	float u;
	float v;
	unsigned int color;

	TriVertex();
};
#endif // !CGEOMETRY_DEFINED