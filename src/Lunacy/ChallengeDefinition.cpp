#include "Lunacy/Challange.h"

ChallengeDefinition* const GLOBAL_DEFS = (ChallengeDefinition*)0x6A2BA0;
ChallengeDefinition* ChallengeDefinition::_gDefArray = GLOBAL_DEFS;
ChallengeDefinition* ChallengeDefinition::_gDefArrayEnd = (ChallengeDefinition*)0x6A3278;
unsigned int ChallengeDefinition::_gUsedDefs = BASE_NUM_GAMEMODES;
unsigned int ChallengeDefinition::_gMaxDefs = BASE_NUM_GAMEMODES;
size_t ChallengeDefinition::_gDefSize = 0x6A3278 - 0x6A2BA0;

unsigned int ChallengeDefinition::_aRefCount = 10;
unsigned int ChallengeDefinition::_aRefs[] =
{
	0x42DF79,
	0x42E3E4,
	0x42E459,
	0x42E515,
	0x42E5AA,
	0x42E720,
	0x42E8B6,
	0x42E965,
	0x42F834,
	0x455BA5
};

unsigned int ChallengeDefinition::_aEndRefCount = 9;
unsigned int ChallengeDefinition::_aEndRefs[] =
{
	0x424A0A,
	0x424CEE,
	0x424E46,
	0x42E066,
	0x42E425,
	0x42E541,
	0x42E5D1,
	0x42F963,
	0x455C08
};

ChallengeDefinition* ChallengeDefinition::AddChallenge(const char* Name, ChallengePage Page, int Row, int Col)
{
	if (_gMaxDefs >= _gUsedDefs)
		Reallocate(_gUsedDefs * 2);

	ChallengeDefinition* NewChallenge = _gDefArray + _gUsedDefs;
	
	NewChallenge->mChallengeMode = (GameMode)_gUsedDefs;
	NewChallenge->mChallengeIconIndex = 0;
	NewChallenge->mChallengeName = Name;
	NewChallenge->mPage = Page;
	NewChallenge->mRow = Row;
	NewChallenge->mCol = Col;

	_gUsedDefs++;
	return NewChallenge;
}

ChallengeDefinition* ChallengeDefinition::GetDefinitions()
{
	return _gDefArray;
}

ChallengeDefinition* ChallengeDefinition::GetDefinition(GameMode Mode)
{
	return _gDefArray + Mode;
}

ChallengeDefinition* ChallengeDefinition::Reallocate(unsigned int NewCapacity)
{
	ChallengeDefinition* NewArray = (ChallengeDefinition*)operator new(sizeof(ChallengeDefinition) * NewCapacity);
	memset(NewArray, 0, NewCapacity * sizeof(ChallengeDefinition));
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

	NewDefAddress = (unsigned int)NewArray + sizeof(ChallengeDefinition) * NewCapacity;
	for (int i = 0; i < _aEndRefCount; i++)
	{
		auto RefP = (unsigned int*)_aEndRefs[i];
		unsigned int Ref;

		DWORD OldProt;
		VirtualProtect(RefP, 4, PAGE_EXECUTE_READWRITE, &OldProt);
		Ref = *RefP;

		unsigned int Offset = Ref - (unsigned int)_gDefArrayEnd;
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