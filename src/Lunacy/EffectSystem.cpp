#include "Lunacy/EffectSystem.h"
#include "Lunacy/LawnApp.h"
#include "Lunacy/Lawn.h"

Reanimation* TryToGet(ReanimationID ID)
{
	return LawnApp::GetApp()->mEffectSystem->mReanimationHolder->Fetch((unsigned int)ID);
}

Attachment* TryToGet(AttachmentID ID)
{
	return LawnApp::GetApp()->mEffectSystem->mAttachmentHolder->Fetch((unsigned int)ID);
}

Trail* TryToGet(TrailID ID)
{
	return LawnApp::GetApp()->mEffectSystem->mTrailHolder->Fetch((unsigned int)ID);
}

Particle* TryToGet(ParticleID ID)
{
	return LawnApp::GetApp()->mEffectSystem->mParticleHolder->mParticles.Fetch((unsigned int)ID);
}

ParticleEmitter* TryToGet(ParticleEmitterID ID)
{
	return LawnApp::GetApp()->mEffectSystem->mParticleHolder->mEmitters.Fetch((unsigned int)ID);
}

ParticleSystem* TryToGet(ParticleSystemID ID)
{
	return LawnApp::GetApp()->mEffectSystem->mParticleHolder->mParticleSystems.Fetch((unsigned int)ID);
}