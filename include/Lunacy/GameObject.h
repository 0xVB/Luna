#pragma once
#include "ForwardDefinitions.h"

class GameObject
{
	LawnApp* mApp;
	Lawn* mLawn;
	int mX;
	int mY;
	int mWidth;
	int mHeight;
	bool mVisible;
	int mRow;
	int mRenderOrder;
};