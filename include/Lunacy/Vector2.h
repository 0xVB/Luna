#pragma once

#include <corecrt_math_defines.h>
#include "ForwardDefinitions.h"
#include "PopStructs.h"

template <typename N>
class Sexy::Vector2
{
public:
	N mX;
	N mY;

	Vector2(N X = 0, N Y = 0)
	{
		mX = X;
		mY = Y;
	}

	Vector2(Vector3<N> Vector)
	{
		auto V = (N*)&Vector;
		mX = V[0];
		mY = V[1];
	}

	Vector2(Rect<N> Rectangle)
	{
		auto V = (N*)&Rectangle;
		mX = V[0];
		mY = V[1];
	}

	static Vector2<float> FromAngle(float Angle, float Magnitude = 1)
	{
		return Vector2<float>(
			cos(Angle) * Magnitude,
			sin(Angle) * Magnitude
		);
	}

	// Returns the magnitude of the vector.
	float GetMagnitude()
	{
		return sqrt(mX * mX + mY * mY);
	}
	// Returns the distance between this vector and the other vector.
	float GetDistance(Vector2 V2)
	{
		return (V2 - *this).GetMagnitude();
	}
	// Returns a vector with equivalent direction but with the given new magnitude.
	Vector2<float> SetMagnitude(float NewMag)
	{
		auto Direction = GetUnit();
		return Direction * NewMag;
	}
	// Returns the basic unit direction of this vector.
	Vector2<float> GetUnit()
	{
		float Mag = GetMagnitude();
		if (Mag == 0) return Vector2();

		return Vector2(
			mX / Mag,
			mY / Mag
		);
	}
	// Returns a vector with the given unit direction but maintaining the magnitude of this vector.
	Vector2<float> SetUnit(Vector2 NewUnit)
	{
		return NewUnit * GetMagnitude();
	}
	// Returns the direction of this vector in radians.
	float GetDirection(bool Clamp = true)
	{
		if (Clamp)
			return ClampAngle(atan2(mY, mX));
		else
			return atan2(mY, mX);
	}
	// Returns a vector with the same magnitude but the given direction in radians.
	Vector2<float> SetDirection(float NewDir)
	{
		float Magnitude = GetMagnitude();
		return Vector2(
			mX * cos(NewDir),
			mY * sin(NewDir)
		);
	}
	// Rotates the vector by the given amount in radians.
	Vector2<float> Rotate(float Rad)
	{
		float NX = mX * cos(Rad) - mY * sin(Rad);
		float NY = mX * sin(Rad) + mY * cos(Rad);
		return Vector2(NX, NY);
	}
	// Returns a vector lerped from this one to the target vector. Alpha is set to 0.5 by default, which returns the midpoint.
	Vector2<float> Lerp(Vector2 Target, float Alpha = 0.5)
	{
		return Vector2(
			mX + (Target.mX - mX) * Alpha,
			mY + (Target.mY - mY) * Alpha
		);
	}
	// Returns the cross product of the two given vectors.
	Vector2<float> Cross(Vector2 Other)
	{
		return Vector2(mY * Other.mY, mX * Other.mX);
	}
	// Returns the dot product of the two given vectors.
	float Dot(Vector2 Other)
	{
		return mX * Other.mX + mY * Other.mY;
	}
	// Returns a lerped vector from `this` to `Target` with a magnitude amount as opposed to an alpha value.
	Vector2<float> Nudge(Vector2 Target, float Amount, bool DoClamp = true)
	{
		float MagDelta = Target.GetMagnitude() - GetMagnitude();
		float Alpha = Amount / MagDelta;
		if (DoClamp)
			Alpha = Clamp(Alpha, -1, 1);

		return Lerp(Target, Alpha);
	}
	// Lerps to the `Target` vector's direction.
	Vector2<float> RadialLerp(Vector2 Target, float Alpha, bool LerpMagnitude = true)
	{
		float MyDir = GetDirection(false);
		float TDir = Target.GetDirection(false);
		float DirDelta = ClampAngle(TDir - MyDir);
		float NewDir = MyDir + DirDelta * Alpha;
		float NewMag = GetMagnitude();

		if (LerpMagnitude)
			NewMag = NewMag + (Target.GetMagnitude() - NewMag) * Alpha;
		return Vector2::FromAngle(NewDir, NewMag);
	}
	// Nudges to the `Target` vector's direction by the given amount.
	Vector2<float> RadialNudge(Vector2 Target, float Amount, bool NudgeMagnitude = true, bool DoClamp = true)
	{
		float MyDir = GetDirection(false);
		float TDir = Target.GetDirection(false);
		float DirDelta = ClampAngle(TDir - MyDir);
		float Alpha = Amount / DirDelta;
		if (DoClamp) Alpha = Clamp(Alpha, -1, 1);
		float NewDir = MyDir + DirDelta * Alpha;
		float NewMag = MyDir;

		if (NudgeMagnitude)
			NewMag = MyDir + (Target.GetMagnitude() - MyDir) * Alpha;
		return Vector2::FromAngle(NewDir, NewMag);
	}
	// Returns the normal to this vector (perpendicular vector.)
	Vector2<float> Normal(bool Clockwise = false)
	{
		if (Clockwise)
			return Vector2(
				mY,
				-mX
			);

		return Vector2(
			-mY,
			mX
		);
	}
	// Returns a string representation of this vector.
	PopString ToString(bool Brackets = true, bool Constructor = false)
	{
		std::string Result = "";
		if (Constructor) Result = "Vector2";
		if (Brackets) Result += "(";
		Result += std::to_string(mX) + ", " + std::to_string(mY);
		if (Brackets) Result += ")";
		return Result;
	}

	void operator=(Vector2 O)
	{
		mX = O.mX;
		mY = O.mY;
	}
	Vector2 operator+(Vector2 O)
	{
		return Vector2(mX + O.mX, mY + O.mY);
	}
	Vector2 operator-(Vector2 O)
	{
		return Vector2(mX - O.mX, mY - O.mY);
	}
	Vector2 operator*(float M)
	{
		return Vector2(mX * M, mY * M);
	}
	Vector2 operator/(float M)
	{
		return Vector2(mX / M, mY / M);
	}

	template <typename T>
	operator Vector2<T>() const
	{
		return Vector2<T>((T)mX, (T)mY);
	}
	
	// To be implemented
	Vector3<N> To3D();

	template <typename T>
	float GetDistance(Vector3<T>);

	template <typename T>
	operator Vector3<T>() const;

	template <typename T>
	operator Rect<T>() const;
};