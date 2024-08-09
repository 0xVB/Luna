#pragma once
#include "CGeometry.h"
#include "UIElement.h"

class UIMessage
{
public:
	LawnApp* mApp;
	char mLabel[128];
	int mDisplayTime;
	int mDuration;
	MessageStyle mMessageStyle;
	ReanimationID mTextReanimID[128];
	ReanimationType mReanimType;
	int mSlideOffTime;
	char mLabelNext[128];
	MessageStyle mMessageStyleNext;
};

class GameButton
{
public:
	LawnApp* mApp;
	Sexy::UIElement* mParent;
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
		Sexy::IRect mBounds;
	};
	bool mIsOver;
	bool mIsDown;
	bool mDisabled;
	Sexy::Color mColors[6];
	int mId;
	PopString mLabel;
	int mLabelJustify;
	Sexy::Font* mFont;
	Sexy::Image* mButtonImage;
	Sexy::Image* mOverImage;
	Sexy::Image* mDownImage;
	Sexy::Image* mDisabledImage;
	Sexy::Image* mOverOverlayImage;
	Sexy::IRect mNormalRect;
	Sexy::IRect mOverRect;
	Sexy::IRect mDownRect;
	Sexy::IRect mDisabledRect;
	bool mInverted;
	bool mBtnNoDraw;
	bool mFrameNoDraw;
	long double mOverAlpha;
	long double mOverAlphaSpeed;
	long double mOverAlphaFadeInSpeed;
	bool mDrawStoneButton;
	Sexy::IVector2 TextOffset;
	Sexy::IVector2 ButtonOffset;
};

class UIToolTip
{
public:
	PopString mTitle;
	PopString mLabel;
	PopString mWarningText;
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
		Sexy::IRect mBounds;
	};
	bool mVisible;
	bool mCenter;
	int mMinLeft;
	int mMaxBottom;
	int mGetsLinesWidth;
	int mWarningFlashCounter;
};