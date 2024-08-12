#include "Lunacy/EffectSystem.h"
#include "Lunacy/LawnApp.h"
#include "Lunacy/Lawn.h"

Reanimation* TryToGet(ReanimationID ID)
{
	return LawnApp::GetApp()->mEffectSystem->mReanimationHolder->mReanimations.Fetch((unsigned int)ID);
}

Attachment* TryToGet(AttachmentID ID)
{
	return LawnApp::GetApp()->mEffectSystem->mAttachmentHolder->mAttachments.Fetch((unsigned int)ID);
}