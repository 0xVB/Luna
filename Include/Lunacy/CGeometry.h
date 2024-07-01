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

template <typename N>
class Sexy::Vector2
{
public:
	N mX;
	N mY;

	Vector2(N = 0, N = 0);
	Vector2(Vector3<N>);
	Vector2(Rect<N>);

	static Vector2<float> FromAngle(float Angle, float Magnitude = 1);

	// Returns the magnitude of the vector.
	float GetMagnitude();
	// Returns a vector with equivalent direction but with the given new magnitude.
	Vector2<float> SetMagnitude(float);
	// Returns the basic unit direction of this vector.
	Vector2<float> GetUnit();
	// Returns a vector with the given unit direction but maintaining the magnitude of this vector.
	Vector2<float> SetUnit(Vector2);
	// Returns the direction of this vector in radians.
	float GetDirection(bool Clamp = true);
	// Returns a vector with the same magnitude but the given direction in radians.
	Vector2<float> SetDirection(float);
	// Rotates the vector by the given amount in radians.
	Vector2<float> Rotate(float);
	// Returns a vector lerped from this one to the target vector. Alpha is set to 0.5 by default, which returns the midpoint.
	Vector2<float> Lerp(Vector2 Target, float Alpha = 0.5);
	// Returns the cross product of the two given vectors.
	Vector2<float> Cross(Vector2);
	// Returns the dot product of the two given vectors.
	float Dot(Vector2);
	// Returns a lerped vector from `this` to `Target` with a magnitude amount as opposed to an alpha value.
	Vector2<float> Nudge(Vector2, float Amount, bool DoClamp = true);
	// Lerps to the `Target` vector's direction.
	Vector2<float> RadialLerp(Vector2 Target, float Alpha, bool LerpMagnitude = true);
	// Nudges to the `Target` vector's direction by the given amount.
	Vector2<float> RadialNudge(Vector2 Target, float Amount, bool NudgeMagnitude = true, bool DoClamp = true);
	// Returns the normal to this vector (perpendicular vector.)
	Vector2<float> Normal(bool Clockwise = false);
	// Returns a string representation of this vector.
	PopString ToString(bool Brackets = true, bool Constructor = false);
	Vector3<float> To3D();

	void operator=(Vector2);
	Vector2 operator+(Vector2);
	Vector2 operator-(Vector2);
	Vector2 operator*(float);
	Vector2 operator/(float);

	operator Vector2<int>();
	operator Vector2<float>();
	operator Vector2<double>();
};

template <typename N>
class Sexy::Vector3
{
public:
	N mX;
	N mY;
	N mZ;

	Vector3(N = 0, N = 0, N = 0);
	Vector3(Vector2<N>);

	static Vector3<float> FromAngle(float HAngle, float VAngle, float Magnitude = 1);

	// Returns the magnitude of the vector.
	float GetMagnitude();
	// Returns a vector with equivalent direction but with the given new magnitude.
	Vector3<float> SetMagnitude(float);
	// Returns the vertical (ZY) direction of this vector in radians.
	float GetVDirection(bool DoClamp = true);
	// Returns the horizontal (XZ) direction of this vector in radians.
	float GetHDirection(bool DoClamp = true);
	// Returns the orbital (XY) direction of this vector in radians.
	float GetODirection(bool DoClamp);
	// Rotates the vector by the given horizontal (Across Y) and vertical (Across X) degrees in radians.
	Vector3<float> RotateBy(float H = 0, float V = 0);
	// Returns the basic unit direction of this vector.
	Vector3<float> GetUnit();
	// Returns a vector with the given unit direction but maintaining the magnitude of this vector.
	Vector3<float> SetUnit(Vector3);
	// Returns a vector lerped from this one to the target vector. Alpha is set to 0.5 by default, which returns the midpoint.
	Vector3<float> Lerp(Vector3 Target, float Alpha = 0.5);
	// Returns the cross product of the two given vectors.
	Vector3<float> Cross(Vector3);
	// Returns the dot product of the two given vectors.
	float Dot(Vector3);
	// Returns a lerped vector from `this` to `Target` with a magnitude amount as opposed to an alpha value.
	Vector3<float> Nudge(Vector3, float Amount, bool DoClamp = true);
	// Lerps to the `Target` vector's direction.
	Vector3<float> RadialLerp(Vector3 Target, float Alpha, bool LerpMagnitude = true);
	// Nudges to the `Target` vector's direction by the given amount.
	Vector3<float> RadialNudge(Vector3 Target, float Amount, bool NudgeMagnitude = true, bool DoClamp = true);
	// Returns the normal to this vector (perpendicular vector.)
	Vector3<float> Normal(float Angle = M_PI_2);
	// Returns a projected Vector2 value. Vector2(X, Y + Z). If InvertZ is true, it returns Vector2(X, Y - Z).
	Vector2<float> Project(bool InvertZ = Z_INVERTED);
	// Returns a string representation of this vector.
	PopString ToString(bool Brackets = true, bool Constructor = false);
	static Vector3 Zero;

	Vector3 operator+(Vector3);
	Vector3 operator-(Vector3);
	Vector3 operator*(float);
	Vector3 operator/(float);
};

template <typename N>
class Sexy::Rect
{
public:
	N mX;
	N mY;
	N mW;
	N mH;

	Rect(N = 0, N = 0, N = 0, N = 0);
	Rect(Vector2<N>, Vector2<N>);

	static Rect FromCenter(float CenterX = 0, float CenterY = 0, float Width = 0, float Height = 0);
	static Rect FromCenter(Vector2<N> Center, Vector2<N> Size);
	static Rect FromExtent(Vector2<N> Min, Vector2<N> Max);

	// Returns the area.
	float GetArea();
	// Returns the perimeter.
	float GetPerimeter();
	// Returns the center of this rectangle.
	Vector2<N> GetCenter();
	// Returns a rectangle with the same width and height, with its center set at the new center.
	Rect SetCenter(Vector2<N> NewCenter);
	// Equivalent to SetCenter.
	Rect Recenter(Vector2<N> NewCenter);
	// Returns the rectangle of intersection between the two rectangles. If the rectangles do not intersect, the returned rect will have an area of 0.
	Rect GetIntersection(Rect Other);
	// Returns true if the two rectangles intersect.
	bool Intersects(Rect Other);
	// Returns the area of the intersection between the 2 rectangles. Returns 0 if they do not intersect.
	float IntersectionArea(Rect Other);
	// Returns true if this rect contains the other rectangle completely.
	bool Contains(Rect Other);
	// Returns true if this rect is contained by the other rectangle completely.
	bool ContainedBy(Rect Other);
	// Returns the diameter of a circle inscribed in this rectangle.
	float GetDiameter();
	// Returns a rectangle with the same center and widht:height ratio as this one, but resized to fit a circle with the given diameter.
	Rect SetDiameter(float NewDiameter);
	static Rect Zero;

	operator tagRECT();

	operator Vector2<N>();

	Rect operator+(Vector2<N>);
	Rect operator-(Vector2<N>);
	Rect operator*(float);
	Rect operator/(float);
	Rect operator+(Rect);
	Rect operator-(Rect);
};

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

#include "Source/Vector2.cpp"
#include "Source/Vector3.cpp"
#include "Source/Rect.cpp"
#include "Source/Color.cpp"
#include "Source/CGeometry.cpp"
#endif // !CGEOMETRY_DEFINED