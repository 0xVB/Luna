#pragma once
#include <Windows.h>
#include "Vector3.h"
template <typename N>
class Sexy::Rect
{
public:
	union
	{
		struct
		{
			N mX;
			N mY;
		};
		Vector2<N> mPosition;
	};

	union
	{
		struct
		{
			N mW;
			N mH;
		};
		Vector2<N> mSize;
	};

	Rect(N X = 0, N Y = 0, N W = 0, N H = 0)
	{
		mX = X;
		mY = Y;
		mW = W;
		mH = H;
	}

	Rect(Vector2<N> Position, Vector2<N> Size)
	{
		mX = Position.mX;
		mY = Position.mY;
		mW = Size.mX;
		mH = Size.mY;
	}

	static Rect FromCenter(float CenterX = 0, float CenterY = 0, float Width = 0, float Height = 0)
	{
		CenterX -= Width / 2;
		CenterY -= Height / 2;
		return Rect(CenterX, CenterY, Width, Height);
	}

	static Rect FromCenter(Vector2<N> Center, Vector2<N> Size)
	{
		return Rect(
			Center - Size / 2,
			Size
		);
	}

	static Rect FromExtent(Vector2<N> Min, Vector2<N> Max)
	{
		return Rect(
			Min,
			Max - Min
		);
	}

	// Returns the area.
	float GetArea()
	{
		if (mW <= 0 || mH <= 0) return 0;
		return mW * mH;
	}
	// Returns the perimeter.
	float GetPerimeter()
	{
		return (mW + mH) * 2;
	}
	// Returns the center of this rectangle.
	Vector2<N> GetCenter()
	{
		return mPosition + mSize / 2;
	}
	// Returns a rectangle with the same width and height, with its center set at the new center.
	Rect SetCenter(Vector2<N> NewCenter)
	{
		return Rect(
			NewCenter - mSize / 2,
			mSize
		);
	}
	// Equivalent to SetCenter.
	Rect Recenter(Vector2<N> NewCenter)
	{
		return Rect(
			NewCenter - mSize / 2,
			mSize
		);
	}
	// Returns the rectangle of intersection between the two rectangles. If the rectangles do not intersect, the returned rect will have an area of 0.
	Rect GetIntersection(Rect Other)
	{
		using std::min;
		using std::min;

		auto MyExtents = mPosition + mSize;
		auto OExtents = Other.mPosition + Other.mSize;

		Vector2<N> IntPos;
		Vector2<N> IntExt;

		IntPos.mX = max(mX, Other.mX);
		IntPos.mY = max(mY, Other.mY);
		IntExt.mX = min(MyExtents.mX, OExtents.mX);
		IntExt.mY = min(MyExtents.mY, OExtents.mY);

		return FromExtent(IntPos, IntExt);
	}
	// Returns true if the two rectangles intersect.
	bool Intersects(Rect Other)
	{
		return IntersectionArea(Other) > 0;
	}
	// Returns the area of the intersection between the 2 rectangles. Returns 0 if they do not intersect.
	float IntersectionArea(Rect Other)
	{
		return GetIntersection(Other).GetArea();
	}
	// Returns true if this rect contains the other rectangle completely.
	bool Contains(Rect Other)
	{
		auto MyExtents = mPosition + mSize;
		auto OExtents = Other.mPosition + Other.mSize;

		return mX <= Other.mX &&
			mY <= Other.mY &&
			MyExtents.mX >= OExtents.mX &&
			MyExtents.mY >= OExtents.mY;
	}
	// Returns true if this rect is contained by the other rectangle completely.
	bool ContainedBy(Rect Other)
	{
		return Other.Contains(*this);
	}
	// Returns the diameter of a circle inscribed in this rectangle.
	float GetDiameter()
	{
		return sqrt(mW * mW + mH * mH);
	}
	// Returns a rectangle with the same center and widht:height ratio as this one, but resized to fit a circle with the given diameter.
	Rect SetDiameter(float NewDiameter)
	{
		float CD = GetDiameter();
		float Ratio = NewDiameter / CD;
		return *this * Ratio;
	}

	operator tagRECT()
	{
		auto Result = tagRECT();
		Result.left = mX;
		Result.top = mY;
		Result.right = mX + mW;
		Result.bottom = mY + mH;
		return Result;
	}

	template <typename T>
	operator Vector2<T>() const
	{
		return Vector2<T>((T)mX, (T)mY);
	}

	template <typename T>
	Rect operator+(Vector2<T> O)
	{
		return Rect(mX + O.mX, mY + O.mY, mW, mH);
	}

	template <typename T>
	Rect operator-(Vector2<T> O)
	{
		return Rect(mX - O.mX, mY - O.mY, mW, mH);
	}

	Rect operator*(float M)
	{
		return Rect(mX, mY, mW * M, mH * M);
	}

	Rect operator/(float M)
	{
		return Rect(mX, mY, mW / M, mH / M);
	}

	Rect operator+(Rect O)
	{
		return Rect(mX + O.mX, mY + O.mY, mW + O.mW, mH + O.mH);
	}

	Rect operator-(Rect O)
	{
		return Rect(mX - O.mX, mY - O.mY, mW - O.mW, mH - O.mH);
	}

	template <typename T>
	operator Rect<T>() const
	{
		return Rect<T>((T)mX, (T)mY, (T)mW, (T)mH);
	}

	Rect& operator=(const Rect& O)
	{
		mX = O.mX;
		mY = O.mY;
		mW = O.mW;
		mH = O.mH;
		return *this;
	}
};

template <typename N>
template <typename T>
Sexy::Vector2<N>::operator Sexy::Rect<T>() const
{
	return Sexy::Rect<T>((T)mX, (T)mY, 0, 0);
}