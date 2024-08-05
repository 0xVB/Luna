#pragma once
#include "ForwardDefinitions.h"
#include <string>
#include <map>

class GameObject
{
public:
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