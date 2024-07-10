#include "Lunacy/CGeometry.h"

#define _USE_MATH_DEFINES
#include <math.h>

float Sexy::ClampAngle(float Angle)
{
	while (Angle > M_PI) Angle -= static_cast<float>(2 * M_PI);
	while (Angle <= -M_PI) Angle += static_cast<float>(2 * M_PI);
	return Angle;
}

float Sexy::Clamp(float Value, float Min, float Max)
{
	return (Value > Max) ? Max : (Value < Min) ? Min : Value;
}

Sexy::Color::Color(int R, int G, int B, int A)
{
	mRed = R;
	mGreen = G;
	mBlue = B;
	mAlpha = A;
}

Sexy::Padding::Padding(int L, int T, int R, int B)
{
	mLeft = L;
	mTop = T;
	mRight = R;
	mBottom = B;
}

Sexy::Matrix3::Matrix3()
{
	m00 = 0;
	m01 = 0;
	m02 = 0;

	m10 = 0;
	m11 = 0;
	m12 = 0;

	m20 = 0;
	m21 = 0;
	m22 = 0;
}

Sexy::Matrix3::Matrix3(float _00, float _01, float _02, float _10, float _11, float _12, float _20, float _21, float _22)
{
	m00 = _00;
	m01 = _01;
	m02 = _02;

	m10 = _10;
	m11 = _11;
	m12 = _12;

	m20 = _20;
	m21 = _21;
	m22 = _22;
}

Sexy::Ratio::Ratio(int Num, int Den)
{
	mNumerator = Num;
	mDenominator = Den;
}

Sexy::Span::Span(int Y, int X, int W)
{
	mY = Y;
	mX = X;
	mWidth = W;
}