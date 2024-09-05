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
	// A dummy struct to serve as a return type for ToHSV
	struct HSV
	{
		float mHue;
		float mSat;
		float mVal;
		HSV(float, float, float);
	};

	enum AlphaLerpingConsideration
	{
		ALC_NONE,// Does not lerp alpha at all.
		ALC_LERP,// Lerps to alpha like it does every color.
		ALC_ALPHA// The Alpha determines the strength of lerping. (Absolute Alpha = Alpha * Color Alpha)
	};

	int mRed;
	int mGreen;
	int mBlue;
	int mAlpha;

	Color(int = 0, int = 0, int = 0, int = 255);
	Color(std::string HexString);// Uses the provided hex code to create a new color. Accepts with and without the # and shortened colors (shortened means #000 = #000000FF)

	static Color FromHSV(int Hue, int Sat, int Val, int Alpha = 255);
	static Color FromHSVf(float Hue, float Sat, float Val, float Alpha);

	Color Lerp(Color, float Alpha = 0.5, AlphaLerpingConsideration = ALC_NONE);
	float GetBrightness();// Returns the brightness of the color.
	float GetSaturation();// Returns the saturation of the color.
	float GetHue();// Returns the hue of the current color.
	HSV ToHSV();// Returns the HSV of the current RGB color.

	Color HueShift(int Amount);// Shifts the hue of the current color by the given amount
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

	Padding(int Left = 0, int Top = 0, int Right = 0, int Bottom = 0);
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

	void LoadIdentity();
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
	void HorizontalReflect();
	void VerticalReflect();
	Sexy::FVector2 GetTranslation();
	Sexy::FVector2 GetScale();
	Sexy::FVector2 GetSkew();
	float GetRotationRadians();
	float GetRotationDegrees();

	Matrix3 operator*(const Matrix3&) const;
	FVector3 operator*(const FVector3&) const;
	FVector2 operator*(const FVector2&) const;
	const Matrix3& operator*=(const Matrix3&);
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

struct Sexy::TriangleGroup
{
	Image* mImage;
	TriVertex mVertArray[256][3];
	int mTriangleCount;
	int mDrawMode;

	TriangleGroup();
	void DrawGroup(Graphics*);
	void AddTriangle(Graphics*, Image*, const Matrix3&, const IRect& ClipRect, const Color&, int DrawMode, const IRect& SrcRect);
};

float Map(float Number, float OldMin, float OldMax, float NewMin = 0, float NewMax = 1);
float GetTicksToTarget(float TargetPosition, float InitialPosition, float Velocity, float Acceleration = 0.0f);