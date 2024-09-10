#include "Lunacy/Particle.h"

unsigned int ParticleDefinition::_gParticleDefCapacity = BASE_NUM_PARTICLES;
unsigned int* ParticleDefinition::_gParticleDefSize = (unsigned int*)0x6A9F08;
unsigned int* ParticleDefinition::_gEmitterDefSize = (unsigned int*)0x6A9F10;

ParticleDefinition** ParticleDefinition::_gParticleDefs = (ParticleDefinition**)0x6A9F0C;
EmitterDefinition** ParticleDefinition::_gEmitterDefs = (EmitterDefinition**)0x6A9F14;

ParticleDefinition* ParticleDefinition::GetDefinitions()
{
	return (ParticleDefinition*)_gParticleDefs;
}

ParticleDefinition* ParticleDefinition::GetDefinition(ParticleEffect Type)
{
	return ((ParticleDefinition*)(_gParticleDefs)) + Type;
}

unsigned int Reallocations = 0;
ParticleDefinition* ParticleDefinition::Reallocate(unsigned int NewCapacity)
{
	Reallocations++;

	auto NewArray = (ParticleDefinition*)operator new(sizeof(ParticleDefinition) * NewCapacity);
	auto OldArray = *_gParticleDefs;

	// Copy data
	memset(NewArray, 0, sizeof(ParticleDefinition) * NewCapacity);
	memcpy(NewArray, OldArray, sizeof(ParticleDefinition) * (*_gParticleDefSize));

	// Move references
	*_gParticleDefs = NewArray;
	_gParticleDefCapacity = NewCapacity;

	// Delete old array
	if (Reallocations > 1)
		delete OldArray;
	return NewArray;
}

ParticleDefinition* ParticleDefinition::CloneParticle(ParticleEffect Type)
{
	if (_gParticleDefCapacity == *_gParticleDefSize)
		Reallocate(*_gParticleDefSize + 0x10);

	auto NewParticle = *_gParticleDefs + *_gParticleDefSize;
	auto OldParticle = *_gParticleDefs + Type;
	(*_gParticleDefSize)++;

	auto NewDefinition = (EmitterDefinition*)operator new(sizeof(EmitterDefinition) * OldParticle->mEmitterDefCount);
	auto OldDefinition = OldParticle->mEmitterDefs;

	memcpy(NewDefinition, OldDefinition, sizeof(EmitterDefinition) * OldParticle->mEmitterDefCount);
	NewParticle->mEmitterDefCount = OldParticle->mEmitterDefCount;
	NewParticle->mEmitterDefs = NewDefinition;

	return NewParticle;
}