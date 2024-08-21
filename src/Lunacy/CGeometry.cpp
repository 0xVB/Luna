#include "Lunacy/CGeometry.h"

#define _USE_MATH_DEFINES

#include <corecrt_math_defines.h>
#include <sstream>
#include <iomanip>
#include <math.h>

const float DEG_RAD = M_PI / 180.0f;
const float RAD_DEG = 180.0f / M_PI;

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

float Map(float n, float n1, float x1, float n2, float x2)
{
	return (n - n1) / (x1 - n1) * (x2 - n2) + n2;
}

Sexy::Matrix3 Sexy::Matrix3::operator*(const Sexy::Matrix3& theMat) const
{
	Matrix3 aResult;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			float x = 0;
			for (int k = 0; k < 3; k++)
				x += m[i][k] * theMat.m[k][j];

			aResult.m[i][j] = x;
		}
	}

	return aResult;
}

void Sexy::Matrix3::LoadIdentity()
{
	m01 = m02 = m10 = m12 = m20 = m21 = 0;
	m00 = m11 = m22 = 1;
}

Sexy::FVector3 Sexy::Matrix3::operator*(const Sexy::FVector3& theVec) const
{
	return Sexy::FVector3(
		m00 * theVec.mX + m01 * theVec.mY + m02 * theVec.mZ,
		m10 * theVec.mX + m11 * theVec.mY + m12 * theVec.mZ,
		m20 * theVec.mX + m21 * theVec.mY + m22 * theVec.mZ);
}

Sexy::FVector2 Sexy::Matrix3::operator*(const Sexy::FVector2& theVec) const
{
	return Sexy::FVector2(
		m00 * theVec.mX + m01 * theVec.mY + m02,
		m10 * theVec.mY + m11 * theVec.mX + m12);
}

const Sexy::Matrix3& Sexy::Matrix3::operator*=(const Sexy::Matrix3& theMat)
{
	return operator=(operator*(theMat));
}

void Sexy::Matrix3::TranslateBy(float tx, float ty)
{
	Sexy::Matrix3 aMat;
	aMat.LoadIdentity();
	aMat.m02 = tx;
	aMat.m12 = ty;
	aMat.m22 = 1;

	*this = aMat * (*this);
}

void Sexy::Matrix3::SetTranslation(float tx, float ty)
{
	m02 = tx;
	m12 = ty;
}

Sexy::FVector2 Sexy::Matrix3::GetTranslation()
{
	return FVector2(m02, m12);
}

void Sexy::Matrix3::ScaleBy(float sx, float sy)
{
	Sexy::Matrix3 aMat;
	aMat.LoadIdentity();
	aMat.m00 = sx;
	aMat.m11 = sy;

	*this = aMat * (*this);
}

void Sexy::Matrix3::SetScale(float sx, float sy)
{
	m00 = sx;
	m11 = sy;
}

Sexy::FVector2 Sexy::Matrix3::GetScale()
{
	return FVector2(m00, m11);
}

void Sexy::Matrix3::RotateByRadians(float r)
{
	Sexy::Matrix3 aMat;
	aMat.LoadIdentity();

	float sinRot = -sinf(r);
	float cosRot = cosf(r);

	aMat.m00 = cosRot;
	aMat.m01 = -sinRot;
	aMat.m10 = sinRot;
	aMat.m11 = cosRot;

	*this = aMat * (*this);
}

void Sexy::Matrix3::RotateByDegrees(float d)
{
	RotateByRadians(DEG_RAD * d);
}

void Sexy::Matrix3::SetRotationRadians(float r)
{
	RotateByRadians(r - GetRotationRadians());
}

void Sexy::Matrix3::SetRotationDegrees(float r)
{
	SetRotationRadians(r * DEG_RAD);
}

float Sexy::Matrix3::GetRotationRadians()
{
	return atan2f(m10, m00);
}

float Sexy::Matrix3::GetRotationDegrees()
{
	return GetRotationRadians() * RAD_DEG;
}

void Sexy::Matrix3::SetSkew(float sx, float sy)
{
	m10 = sx;
	m01 = sy;
}

void Sexy::Matrix3::SkewBy(float sx, float sy)
{
	Sexy::Matrix3 aMat;
	aMat.LoadIdentity();

	aMat.m10 = sx;  // Skew in the x direction
	aMat.m01 = sy;  // Skew in the y direction

	*this = aMat * (*this);
}

Sexy::FVector2 Sexy::Matrix3::GetSkew()
{
	return FVector2(m10, m01);
}

void Sexy::Matrix3::HorizontalReflect()
{
	Sexy::Matrix3 aMat;
	aMat.LoadIdentity();
	aMat.m00 = -1;  // Invert the X-axis

	*this = aMat * (*this);
}

void Sexy::Matrix3::VerticalReflect()
{
	Sexy::Matrix3 aMat;
	aMat.LoadIdentity();
	aMat.m11 = -1;  // Invert the Y-axis

	*this = aMat * (*this);
}

// Color Functions
Sexy::Color::HSV::HSV(float h, float s, float v)
{
	mHue = h;
	mSat = s;
	mVal = v;
}

Sexy::Color::Color(std::string aHexString)
{
	// Remove the '#' if present
	if (aHexString[0] == '#')
		aHexString = aHexString.substr(1);

	// Convert shortened hex (e.g., #03F) to full hex (e.g., #0033FF)
	if (aHexString.length() == 1)
	{
		auto c = aHexString[0];
		aHexString = aHexString + c + c + c + c + c;
	}
	else if (aHexString.length() == 2)
	{
		auto c0 = aHexString[0];
		auto c1 = aHexString[1];
		aHexString = std::string() + c0 + c1 + c0 + c1 + c0 + c1;
	}
	else if (aHexString.length() == 3)
	{
		auto r = aHexString[0];
		auto g = aHexString[1];
		auto b = aHexString[2];
		aHexString = std::string() + r + r + g + g + b + b;
	}
	else if (aHexString.length() == 4)
	{
		auto r = aHexString[0];
		auto g = aHexString[1];
		auto b = aHexString[2];
		auto a = aHexString[3];
		aHexString = std::string() + r + r + g + g + b + b + a + a;
	}
	else if (aHexString.length() == 5)
	{
		auto r = aHexString[0];
		auto g = aHexString[1];
		auto b = aHexString[2];
		auto a = aHexString[3];
		auto s = aHexString[4];
		aHexString = std::string() + r + r + g + g + b + b + a + s;
	}

	if (aHexString.length() == 6) {
		aHexString += "FF";  // Default alpha to 255 (opaque) if not provided
	}

	if (aHexString.length() == 8) {
		mRed = std::stoi(aHexString.substr(0, 2), nullptr, 16);
		mGreen = std::stoi(aHexString.substr(2, 2), nullptr, 16);
		mBlue = std::stoi(aHexString.substr(4, 2), nullptr, 16);
		mAlpha = std::stoi(aHexString.substr(6, 2), nullptr, 16);
	}
	else {
		// Default to black with full opacity if aHexString is invalid
		mRed = mGreen = mBlue = 0;
		mAlpha = 255;
	}
}

float Sexy::Color::GetBrightness()
{
	return max(max(mRed, mGreen), mBlue) / 255.0f;
}

float Sexy::Color::GetSaturation()
{
	float aMin = min(min(mRed, mGreen), mBlue) / 255.0f;
	float aMax = max(min(mRed, mGreen), mBlue) / 255.0f;
	return (aMax == 0) ? 0 : (aMax - aMin) / aMax;
}

float Sexy::Color::GetHue()
{
	float r = mRed / 255.0f;
	float g = mGreen / 255.0f;
	float b = mBlue / 255.0f;

	float aMin = min(min(r, g), b);
	float aMax = max(max(r, g), b);

	float hue = 0.0f;

	if (aMax == aMin)
		return 0;
	else if (aMax == r)
		hue = 60.0f * (fmod(((g - b) / (aMax - aMin)), 6));
	else if (aMax == g)
		hue = 60.0f * (((b - r) / (aMax - aMin)) + 2);
	else if (aMax == b)
		hue = 60.0f * (((r - g) / (aMax - aMin)) + 4);

	if (hue < 0.0f)
		hue += 360.0f;

	return hue;
}

Sexy::Color::HSV Sexy::Color::ToHSV()
{
	float r = mRed / 255.0f;
	float g = mGreen / 255.0f;
	float b = mBlue / 255.0f;

	float aMin = min(min(r, g), b);
	float aMax = max(max(r, g), b);

	float hue = GetHue();
	float sat = (aMax == 0.0f) ? 0.0f : (aMax - aMin) / aMax;
	float val = aMax;

	return HSV(hue, sat, val);
}

Sexy::Color Sexy::Color::FromHSV(int hue, int sat, int val, int alpha)
{
	float h = hue / 360.0f;   // Normalize hue to the range [0, 1]
	float s = sat / 100.0f;   // Normalize saturation to the range [0, 1]
	float v = val / 100.0f;   // Normalize value to the range [0, 1]

	float r = 0, g = 0, b = 0;

	int i = (int)(h * 6);				// Sector 0 to 5
	float f = h * 6 - i;				// Fractional part of h
	float p = v * (1 - s);
	float q = v * (1 - f * s);
	float t = v * (1 - (1 - f) * s);

	switch (i % 6)
	{
	case 0: r = v; g = t; b = p; break;
	case 1: r = q; g = v; b = p; break;
	case 2: r = p; g = v; b = t; break;
	case 3: r = p; g = q; b = v; break;
	case 4: r = t; g = p; b = v; break;
	case 5: r = v; g = p; b = q; break;
	}

	return Color((int)(r * 255), (int)(g * 255), (int)(b * 255), alpha);
}

Sexy::Color Sexy::Color::FromHSVf(float h, float s, float v, float a)
{
	float r = 0, g = 0, b = 0;
	int i = (int)(h * 6);				// Sector 0 to 5
	float f = h * 6 - i;				// Fractional part of h
	float p = v * (1 - s);
	float q = v * (1 - f * s);
	float t = v * (1 - (1 - f) * s);

	switch (i % 6)
	{
	case 0: r = v; g = t; b = p; break;
	case 1: r = q; g = v; b = p; break;
	case 2: r = p; g = v; b = t; break;
	case 3: r = p; g = q; b = v; break;
	case 4: r = t; g = p; b = v; break;
	case 5: r = v; g = p; b = q; break;
	}

	return Color((int)(r * 255), (int)(g * 255), (int)(b * 255), (int)(a * 255));
}

Sexy::Color Sexy::Color::HueShift(int aHue)
{
	return FromHSV(GetHue() + (aHue / 360.0f), GetSaturation(), GetBrightness(), 1.0f);
}

Sexy::Color Sexy::Color::Lerp(Sexy::Color aColor, float a, AlphaLerpingConsideration ALC)
{
	if (ALC == ALC_ALPHA)
		a *= (aColor.mAlpha / 255.0f);

	float i = 1 - a;
	return Color(
		(mRed * i) + aColor.mRed * a,
		(mBlue * i) + aColor.mBlue * a,
		(mGreen * i) + aColor.mGreen * a,
		(ALC == ALC_LERP) ? ((mAlpha * i) + aColor.mAlpha * a) : mAlpha
	);
}

CONST DWORD TRIGCONST = 0x4461B0;
CONST DWORD TRIGDRAW = 0x4461F0;
CONST DWORD TRIGADD = 0x446300;

__declspec(naked) void __stdcall CONSTRUCTTG(Sexy::TriangleGroup*)
{
	__asm
	{
		pop edx// Ret
		pop eax
		push edx
		jmp TRIGCONST
	}
}
Sexy::TriangleGroup::TriangleGroup()
{
	CONSTRUCTTG(this);
}

__declspec(naked) void Sexy::TriangleGroup::DrawGroup(Graphics*)
{
	__asm
	{
		push esi
		mov esi, ecx
		push[esp + 0x8]
		call TRIGDRAW
		pop esi
		ret 0x4
	}
}
__declspec(naked) void Sexy::TriangleGroup::AddTriangle(Graphics*, Image*, const Matrix3&, const IRect&, const Color&, int, const IRect&)
{
	/*
	* edi: this*
	* eax: Image*
	* Then push in order
	*/
	__asm
	{
		push edi
		mov edi, ecx
		mov eax, [esp + 0xC]

		push[esp + 0x20]// IRect
		push[esp + 0x20]// int
		push[esp + 0x20]// Color
		push[esp + 0x20]// IRect
		push[esp + 0x20]// Matrix3
		push[esp + 0x1C]// G
		call TRIGADD

		pop edi
		ret 0x1C
	}
}

float GetTicksToTarget(float iTarg, float iPos, float iVel, float iAcc)
{
	float Delta = iTarg - iPos;
	float NextDelta = Delta;

	if (iAcc == 0 && iVel == 0)
		return -1;  // No movement possible, will never reach target
	else if (iAcc == 0)
		return (Delta / iVel);  // Simple linear motion (constant velocity), return ticks directly

	float Ticks = 0;
	bool AccelerationPointsToTarget = (Delta * iAcc) > 0;
	// Since the acceleration points to the target, it will eventually hit the target so there's no reason to make
	// a break check.

	// Start the iteration to calculate the ticks
Start:
	Delta = iTarg - iPos;

	if ((Delta > 0 && iVel > 0) || (Delta < 0 && iVel < 0) || AccelerationPointsToTarget)
	{
		// Perform the position and velocity update for one tick
		iPos += iVel;
		iVel += iAcc;
		Ticks += 1;

		NextDelta = iTarg - iPos;

		// Check if we've crossed the target or exactly reached it
		if ((Delta > 0 && NextDelta <= 0) || (Delta < 0 && NextDelta >= 0) || (NextDelta == 0))
			return Ticks;  // Target reached

		goto Start;
	}

	// If velocity is zero and acceleration doesn't point towards the target
	return -1;
}