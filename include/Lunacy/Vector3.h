#pragma once

#include "Vector2.h"

template <typename N>
class Sexy::Vector3
{
public:
	N mX;
	N mY;
	N mZ;

	Vector3(N X = 0, N Y = 0, N Z = 0)
	{
		mX = X;
		mY = Y;
		mZ = Z;
	}

	Vector3(Vector2<N> Vector)
	{
		mX = Vector.mX;
		mY = Vector.mY;
		mZ = 0;
	}

	static Vector3<float> FromAngle(float HAngle, float VAngle, float Magnitude = 1)
	{
		return Vector3(
			cos(HAngle) * cos(VAngle) * Magnitude,
			sin(HAngle) * cos(VAngle) * Magnitude,
			sin(VAngle) * Magnitude
		);
	}

	// Returns the magnitude of the vector.
	float GetMagnitude()
	{
		return sqrt(mX * mX + mY * mY + mZ * mZ);
	}
	// Returns a vector with equivalent direction but with the given new magnitude.
	Vector3<float> SetMagnitude(float NewMag)
	{
		return GetUnit() * NewMag;
	}
	// Returns the vertical (ZY) direction of this vector in radians.
	float GetVDirection(bool DoClamp = true)
	{
		if (DoClamp)
			return ClampAngle(atan2(mZ, mY));
		return atan2(mZ, mY);
	}
	// Returns the horizontal (XZ) direction of this vector in radians.
	float GetHDirection(bool DoClamp = true)
	{
		if (DoClamp)
			return ClampAngle(atan2(mZ, mX));
		return atan2(mZ, mX);
	}
	// Returns the orbital (XY) direction of this vector in radians.
	float GetODirection(bool DoClamp)
	{
		if (DoClamp)
			return ClampAngle(atan2(mY, mX));
		return atan2(mY, mX);
	}
	// Rotates the vector by the given horizontal (Across Y) and vertical (Across X) degrees in radians.
	Vector3<float> RotateBy(float H = 0, float V = 0)
	{
		return Vector3::FromAngle(GetHDirection() + H, GetVDirection() + V, GetMagnitude());
	}
	// Returns the basic unit direction of this vector.
	Vector3<float> GetUnit()
	{
		float Mag = GetMagnitude();
		if (Mag == 0) return Vector3<float>();

		return Vector3(
			mX / Mag,
			mY / Mag,
			mZ / Mag
		);
	}
	// Returns a vector with the given unit direction but maintaining the magnitude of this vector.
	Vector3<float> SetUnit(Vector3 NewUnit)
	{
		return NewUnit * GetMagnitude();
	}
	// Returns a vector lerped from this one to the target vector. Alpha is set to 0.5 by default, which returns the midpoint.
	Vector3<float> Lerp(Vector3 Target, float Alpha = 0.5)
	{
		return Vector3(
			mX + (Target.mX - mX) * Alpha,
			mY + (Target.mY - mY) * Alpha,
			mZ + (Target.mZ - mZ) * Alpha
		);
	}
	// Returns the cross product of the two given vectors.
	Vector3<float> Cross(Vector3 Other)
	{
		return Vector3(
			mY * Other.mZ - mZ * Other.mY,
			mZ * Other.mX - mX * Other.mZ,
			mX * Other.mY - mY * Other.mX
		);
	}
	// Returns the dot product of the two given vectors.
	float Dot(Vector3 Other)
	{
		return mX * Other.mX + mY * Other.mY + mZ * Other.mZ;
	}
	// Returns a lerped vector from `this` to `Target` with a magnitude amount as opposed to an alpha value.
	Vector3<float> Nudge(Vector3 Target, float Amount, bool DoClamp = true)
	{
		float MagDelta = Target.GetMagnitude() - GetMagnitude();
		float Alpha = Amount / MagDelta;
		if (DoClamp)
			Alpha = Clamp(Alpha, -1, 1);

		return Lerp(Target, Alpha);
	}
	// Lerps to the `Target` vector's direction.
	Vector3<float> RadialLerp(Vector3 Target, float Alpha, bool LerpMagnitude = true)
	{
		float HDir = GetHDirection(false);
		float VDir = GetVDirection(false);
		float HDel = ClampAngle(Target.GetHDirection() - HDir);
		float VDel = ClampAngle(Target.GetVDirection() - VDir);
		float Mag = GetMagnitude();
		if (LerpMagnitude)
			Mag = Mag + (Target.GetMagnitude() - Mag) * Alpha;
		return Vector3::FromAngle(
			HDir + HDel * Alpha,
			VDir + VDel * Alpha,
			Mag
		);
	}
	// Nudges to the `Target` vector's direction by the given amount.
	Vector3<float> RadialNudge(Vector3 Target, float Amount, bool NudgeMagnitude = true, bool DoClamp = true)
	{
		float HDir = GetHDirection(false);
		float VDir = GetVDirection(false);
		float HDel = ClampAngle(Target.GetHDirection() - HDir);
		float VDel = ClampAngle(Target.GetVDirection() - VDir);
		float TDel = sqrt(HDel * HDel + VDel * VDel);
		float Alpha = Amount / TDel;
		float Mag = GetMagnitude();
		if (NudgeMagnitude)
			Mag = Mag + (Target.GetMagnitude() - Mag) * Alpha;
		return Vector3::FromAngle(
			HDir + HDel * Alpha,
			VDir + VDel * Alpha,
			Mag
		);
	}
	// Returns the normal to this vector (perpendicular vector.)
	Vector3<float> Normal(float Angle = M_PI_2)
	{
		return Cross(Vector3(cos(Angle), sin(Angle), 0)).GetUnit();
	}
	// Returns a projected Vector2 value. Vector2(X, Y + Z). If InvertZ is true, it returns Vector2(X, Y - Z).
	Vector2<float> Project(bool InvertZ = Z_INVERTED)
	{
		if (InvertZ)
			return Vector2(mX, mY - mZ);
		return Vector2(mX, mY + mZ);
	}
	// Returns a string representation of this vector.
	PopString ToString(bool Brackets = true, bool Constructor = false)
	{
		std::string Result = "";
		if (Constructor) Result = "Vector3";
		if (Brackets) Result += "(";
		Result += std::to_string(mX) + ", " + std::to_string(mY) + ", " + std::to_string(mZ);
		if (Brackets) Result += ")";
		return Result;
	}

	Vector3 operator+(Vector3 O)
	{
		return Vector3(mX + O.mX, mY + O.mY, mZ + O.mZ);
	}
	Vector3 operator-(Vector3 O)
	{
		return Vector3(mX + O.mX, mY + O.mY, mZ + O.mZ);
	}
	Vector3 operator*(float M)
	{
		return Vector3(mX * M, mY * M, mZ * M);
	}
	Vector3 operator/(float M)
	{
		return Vector3(mX / M, mY / M, mZ / M);
	}

	template <typename T>
	operator Vector2<T>() const
	{
		return Vector2<T>((T)mX, (T)mY);
	}

	template <typename T>
	operator Vector3<T>() const
	{
		return Vector3<T>((T)mX, (T)mY, (T)mZ);
	}
};

template <typename N>
Sexy::Vector3<N> Sexy::Vector2<N>::To3D()
{
	return Sexy::Vector3<N>(mX, mY, 0);
}

template <typename N>
template <typename T>
float Sexy::Vector2<N>::GetDistance(Sexy::Vector3<T> V3)
{
	return (V3.Project() - *this).GetMagnitude();
}

template <typename N>
template <typename T>
Sexy::Vector2<N>::operator Sexy::Vector3<T>() const
{
	return Sexy::Vector3<T>((T)mX, (T)mY, 0);
}