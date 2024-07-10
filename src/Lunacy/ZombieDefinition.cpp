#include "Lunacy/Zombie.h"

ZombieDefinition::ZombieDefinition()
{
	mZombieType = ZOMBIE_INVALID;
	mReanimationType = REANIM_NONE;
	mZombieValue = 0;
	mStartingLevel = 0;
	mFirstAllowedWave = 0;
	mPickWeight = 0;
	mZombieName = "";
}

ZombieDefinition::ZombieDefinition(ZombieType Type, const char* Name)
{
	mZombieType = Type;
	mReanimationType = REANIM_NONE;
	mZombieValue = 0;
	mStartingLevel = 0;
	mFirstAllowedWave = 0;
	mPickWeight = 0;
	mZombieName = Name;
}

ZombieDefinition* const GLOBAL_DEFS = (ZombieDefinition*)0x69DA80;
ZombieDefinition* ZombieDefinition::_gDefArray = GLOBAL_DEFS;
ZombieDefinition* ZombieDefinition::_gDefArrayEnd = (ZombieDefinition*)0x69DE1C;
unsigned int ZombieDefinition::_gUsedDefs = BASE_NUM_ZOMBIE_TYPES;
unsigned int ZombieDefinition::_gMaxDefs = BASE_NUM_ZOMBIE_TYPES;
size_t ZombieDefinition::_gDefSize = 0x69DE1C - 0x69DA80;

unsigned int ZombieDefinition::_aRefCount = 77;
unsigned int ZombieDefinition::_aRefs[] = {
	0x4030FE,
	0x4032B9,
	0x403460,
	0x40349E,
	0x403A37,
	0x403A87,
	0x403B51,
	0x403B6E,
	0x409274,
	0x4095A1,
	0x4095D6,
	0x40960B,
	0x409640,
	0x409678,
	0x4097D6,
	0x40981A,
	0x409A04,
	0x409A6A,
	0x409B32,
	0x409B67,
	0x409B9C,
	0x409BD1,
	0x409C06,
	0x409C3B,
	0x409C70,
	0x409CA5,
	0x409CDA,
	0x409D12,
	0x409D6E,
	0x409DA3,
	0x409DD8,
	0x409E0D,
	0x409E42,
	0x409E77,
	0x409EAC,
	0x409EE1,
	0x409F16,
	0x409F4E,
	0x409FA8,
	0x409FD5,
	0x40A002,
	0x40A02F,
	0x40A05F,
	0x40A0CF,
	0x40D66F,
	0x40D698,
	0x40D70F,
	0x40D72F,
	0x40D777,
	0x40D77D,
	0x40D7A6,
	0x40D7E5,
	0x40D8CB,
	0x40F059,
	0x40F060,
	0x412A5E,
	0x412CC1,
	0x412DAC,
	0x425D3A,
	0x439B29,
	0x439B58,
	0x439B8A,
	0x439BBC,
	0x439C00,
	0x439C32,
	0x439C64,
	0x439F4A,
	0x439F8A,
	0x439FBC,
	0x439FEE,
	0x4556C9,
	0x455879,
	0x46F91F,
	0x5227B1,
	0x530209,
	0x5369EF,
	0x536A62
};

ZombieDefinition* ZombieDefinition::AddZombie(const char* Name)
{
	if (_gMaxDefs >= _gUsedDefs)
		Reallocate(_gUsedDefs * 2);

	ZombieDefinition* NewZombie = _gDefArray + _gUsedDefs;

	NewZombie->mZombieType = (ZombieType)_gUsedDefs;
	NewZombie->mReanimationType = REANIM_NONE;
	NewZombie->mZombieValue = 0;
	NewZombie->mStartingLevel = 0;
	NewZombie->mFirstAllowedWave = 0;
	NewZombie->mPickWeight = 0;
	NewZombie->mZombieName = Name;
	_gUsedDefs++;

	return NewZombie;
}

ZombieDefinition* ZombieDefinition::GetDefinitionArray()
{
	return _gDefArray;
}

ZombieDefinition* ZombieDefinition::GetZombieDefinition(ZombieType Type)
{
	return _gDefArray + Type;
}

ZombieDefinition* ZombieDefinition::Reallocate(unsigned int NewCapacity)
{
	ZombieDefinition* NewArray = (ZombieDefinition*)operator new(sizeof(ZombieDefinition) * NewCapacity);
	memset(NewArray, 0, NewCapacity * sizeof(ZombieDefinition));
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