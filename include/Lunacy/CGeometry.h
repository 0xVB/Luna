#pragma once
#include "ForwardDefinitions.h"

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

	Color(int = 0, int = 0, int = 0, int = 255);
};

class Sexy::SColor
{
	byte mRed;
	byte mGreen;
	byte mBlue;
	byte mAlpha;

	SColor(int = 0, int = 0, int = 0, int = 255);
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
	int mY = 0;
	int mX = 0;
	int mWidth = 0;

	Span(int Y, int X, int W);
};

class Sexy::Edge
{
public:
	long double mX = 0;
	long double mDX = 0;
	int i = 0;
	long double b = 0;
};

class Sexy::TriVertex
{
public:
	float x = 0;
	float y = 0;
	float u = 0;
	float v = 0;
	unsigned int color = 0;
};