#include "Lunacy/Plant.h"

PlantDefinition::PlantDefinition()
{
	mSeedType = SEED_NONE;
	mPlantImage = nullptr;
	mReanimationType = REANIM_NONE;
	mPacketIndex = 0;
	mSeedCost = 0;
	mRefreshTime = 0;
	mSubClass = SUBCLASS_NORMAL;
	mLaunchRate = 0;
	mPlantName = "";
}

PlantDefinition::PlantDefinition(SeedType Type, const char* Name)
{
	mSeedType = Type;
	mPlantImage = nullptr;
	mReanimationType = REANIM_NONE;
	mPacketIndex = 0;
	mSeedCost = 0;
	mRefreshTime = 0;
	mSubClass = SUBCLASS_NORMAL;
	mLaunchRate = 0;
	mPlantName = Name;
}

PlantDefinition* GLOBAL_DEFS = (PlantDefinition*)0x69F2B0;
PlantDefinition* PlantDefinition::_gDefArray = GLOBAL_DEFS;
PlantDefinition* PlantDefinition::_gDefArrayEnd = (PlantDefinition*)0x69FA24;
unsigned int PlantDefinition::_gUsedDefs = BASE_NUM_SEED_TYPES;
unsigned int PlantDefinition::_gMaxDefs = BASE_NUM_SEED_TYPES;
size_t PlantDefinition::_gDefSize = 0x69FA24 - 0x69F2B0;

unsigned int PlantDefinition::_aRefCount = 62;
unsigned int PlantDefinition::_aRefs[] = {
	0x4024C0,
	0x4397B0,
	0x4397C4,
	0x439C9F,
	0x439CB6,
	0x439CCA,
	0x439CE7,
	0x439CFE,
	0x439D24,
	0x439D3B,
	0x439D4F,
	0x439D63,
	0x439D77,
	0x439D94,
	0x439DB4,
	0x439DCB,
	0x439DDF,
	0x439DFC,
	0x439E13,
	0x439E30,
	0x439E50,
	0x439E67,
	0x439E7B,
	0x43A032,
	0x43A049,
	0x43A05D,
	0x43A071,
	0x43A085,
	0x43A099,
	0x43A0BF,
	0x43A0D6,
	0x45DCBF,
	0x45FF69,
	0x45FF73,
	0x463F4A,
	0x465AFB,
	0x466290,
	0x4662F8,
	0x467B99,
	0x467BA4,
	0x467C29,
	0x467C82,
	0x467C89,
	0x467DD3,
	0x467E4E,
	0x467E59,
	0x4681E6,
	0x46F5F2,
	0x486DF6,
	0x486E02,
	0x488F68,
	0x488F79,
	0x48BE52,
	0x48BE68,
	0x48BE7B,
	0x48BEB1,
	0x48BECF,
	0x48BEE7,
	0x48BEFC,
	0x48BF11,
	0x48BF26,
	0x48BF3B
};

PlantDefinition* PlantDefinition::AddPlant(const char* Name)
{
	if (_gMaxDefs == BASE_NUM_SEED_TYPES)
		Reallocate(SEED_UNOCCUPIED_START * 2);

	if (_gMaxDefs >= _gUsedDefs)
		Reallocate(_gUsedDefs * 2);

	PlantDefinition* NewPlant = _gDefArray + _gUsedDefs;

	NewPlant->mSeedType = (SeedType)(BASE_NUM_SEED_TYPES - _gUsedDefs + SEED_UNOCCUPIED_START);
	NewPlant->mReanimationType = REANIM_NONE;
	NewPlant->mPlantImage = nullptr;
	NewPlant->mPacketIndex = _gUsedDefs;
	NewPlant->mSeedCost = 0;
	NewPlant->mRefreshTime = 0;
	NewPlant->mSubClass = SUBCLASS_NORMAL;
	NewPlant->mLaunchRate = 0;
	NewPlant->mPlantName = Name;
	_gUsedDefs++;

	return NewPlant;
}

PlantDefinition* PlantDefinition::GetDefinitionArray()
{
	return _gDefArray;
}

PlantDefinition* PlantDefinition::GetPlantDefinition(SeedType Type)
{
	return _gDefArray + Type;
}

PlantDefinition* PlantDefinition::Reallocate(unsigned int NewCapacity)
{
	PlantDefinition* NewArray = (PlantDefinition*)operator new(sizeof(PlantDefinition) * NewCapacity);
	memset(NewArray, 0, NewCapacity * sizeof(PlantDefinition));
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