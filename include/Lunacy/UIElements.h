#pragma once
#include "UIElement.h"

class Sexy::UIButton : Sexy::UIElement
{
public:
	int mId;
	PopString mLabel;
	int mLabelJustify;
	Sexy::Font* mFont;
	Sexy::Image* mButtonImage;
	Sexy::Image* mOverImage;
	Sexy::Image* mDownImage;
	Sexy::Image* mDisabledImage;
	Sexy::IRect mNormalRect;
	Sexy::IRect mOverRect;
	Sexy::IRect mDownRect;
	Sexy::IRect mDisabledRect;
	bool mInverted;
	bool mBtnNoDraw;
	bool mFrameNoDraw;
	Sexy::ButtonListener* mButtonListener;
	long double mOverAlpha;
	long double mOverAlphaSpeed;
	long double mOverAlphaFadeInSpeed;

	virtual void DrawButtonImage(Sexy::Graphics*, Sexy::Image*, const Sexy::IRect*, int X, int Y) = 0;
	virtual void SetFont(Sexy::Font*) = 0;
	virtual bool IsButtonDown() = 0;
};

class Sexy::DialogButton : public Sexy::UIButton
{
public:
	Sexy::Image* mComponentImage;
	int mTranslateX;
	int mTranslateY;
	int mTextOffsetX;
	int mTextOffsetY;
};