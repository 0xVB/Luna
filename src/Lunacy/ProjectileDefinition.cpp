#include "Lunacy/Projectile.h"


ProjectileDefinition::ProjectileDefinition()
{
	mDamage = 0;
	mImageRow = 0;
	mProjectileType = PROJECTILE_PEA;
}

ProjectileDefinition::ProjectileDefinition(ProjectileType Type)
{
	mDamage = 0;
	mImageRow = 0;
	mProjectileType = Type;
}

ProjectileDefinition* const GLOBAL_DEFS = (ProjectileDefinition*)0x69DA80;
ProjectileDefinition* ProjectileDefinition::_gDefArray = GLOBAL_DEFS;
ProjectileDefinition* ProjectileDefinition::_gDefArrayEnd = (ProjectileDefinition*)0x69DE1C;
unsigned int ProjectileDefinition::_gUsedDefs = BASE_NUM_ZOMBIE_TYPES;
unsigned int ProjectileDefinition::_gMaxDefs = BASE_NUM_ZOMBIE_TYPES;
size_t ProjectileDefinition::_gDefSize = 0x69DE1C - 0x69DA80;

unsigned int ProjectileDefinition::_aRefCount = 5;
unsigned int ProjectileDefinition::_aRefs[] = {
	0x46CFE1,
	0x46D3AB,
	0x46D79C,
	0x46E076,
	0x46E578
};;

ProjectileDefinition* ProjectileDefinition::AddProjectile()
{
	if (_gMaxDefs >= _gUsedDefs)
		Reallocate(_gUsedDefs * 2);

	ProjectileDefinition* NewProj = _gDefArray + _gUsedDefs;
	NewProj->mDamage = 0;
	NewProj->mImageRow = 0;
	NewProj->mProjectileType = PROJECTILE_PEA;
	_gUsedDefs++;

	return NewProj;
}

ProjectileDefinition* ProjectileDefinition::GetDefinitionArray()
{
	return _gDefArray;
}

ProjectileDefinition* ProjectileDefinition::GetProjectileDefinition(ProjectileType Type)
{
	return _gDefArray + Type;
}

ProjectileDefinition* ProjectileDefinition::Reallocate(unsigned int NewCapacity)
{
	ProjectileDefinition* NewArray = (ProjectileDefinition*)operator new(sizeof(ProjectileDefinition) * NewCapacity);
	memset(NewArray, 0, NewCapacity * sizeof(ProjectileDefinition));
	memcpy(NewArray, _gDefArray, _gDefSize);

	unsigned int NewDefAddress = (unsigned int)NewArray;

	for (int i = 0; i < _aRefCount; i++)
	{
		auto RefP = (unsigned int*)_aRefs[i];
		unsigned int Ref;

		DWORD OldProt;
		VirtualProtect(RefP, 4, PAGE_EXECUTE_READWRITE, &OldProt);
		Ref = *RefP;

		unsigned int Offset = Ref - (unsigned int)_gDefArray;
		Ref = NewDefAddress + Offset;
		*RefP = Ref;
		VirtualProtect(RefP, 4, OldProt, &OldProt);
	}

	if (_gDefArray != GLOBAL_DEFS)
		delete _gDefArray;

	_gDefArray = NewArray;
	_gDefArrayEnd = NewArray + NewCapacity;
	_gDefSize = (unsigned int)_gDefArrayEnd - (unsigned int)_gDefArray;
	_gMaxDefs = NewCapacity;

	return NewArray;
}