#pragma once
#include "Trail.h"

class AttachEffect
{
public:
	unsigned int mEffectID;
	EffectType mEffectType;
	Sexy::Transform2D mOffset;
	bool mDontDrawIfParentHidden;
	bool mDontPropogateColor;
};

class Attachment
{
public:
	AttachEffect mEffectArray[16];
	int mNumEffects;
	bool mDead;

	void Update();
	void SetPosition(const Sexy::FVector2&);
	void OverrideColor(const Sexy::Color&);
	void PropogateColor(const Sexy::Color& Overlay, bool EnableOverlayColor, const Sexy::Color& Additive, bool EnableAdditiveColor, const Sexy::Color& Color);
	void OverrideScale(float Scale);
	void CrossFade();
	void SetMatrix(const Sexy::Matrix3&);
	void Draw(Sexy::Graphics*, bool ParentHidden);
	void Detach();
	void Die();

	AttachmentID GetID();
	operator AttachmentID();
};

class AttachmentHolder : public DataArray<Attachment>
{ };