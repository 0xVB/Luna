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
};

class AttachmentHolder
{
public:
	DataArray<Attachment> mAttachments;
};