#pragma once
#include "CGeometry.h"
#include <string>
#include <map>

class GameObject
{
public:
	LawnApp* mApp;
	Lawn* mLawn;
	union
	{
		struct
		{
			int mX;
			int mY;
			int mWidth;
			int mHeight;
		};
		struct
		{
			Sexy::IVector2 mPosition;
			Sexy::IVector2 mSize;
		};
		Sexy::IRect mHitbox;
	};
	bool mVisible;
	int mRow;
	int mRenderOrder;
};