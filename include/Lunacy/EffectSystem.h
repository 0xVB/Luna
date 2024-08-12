#pragma once
#include "Reanimation.h"
#include "Attachment.h"

class EffectSystem
{
public:
	ParticleHolder* mParticleHolder;
	TrailHolder* mTrailHolder;
	ReanimationHolder* mReanimationHolder;
	AttachmentHolder* mAttachmentHolder;
};