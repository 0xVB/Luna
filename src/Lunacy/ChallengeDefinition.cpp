#include "Lunacy/Challange.h"

ChallengeDefinition* const GLOBAL_DEFS = (ChallengeDefinition*)0x6A2BA0;
ChallengeDefinition* ChallengeDefinition::_gDefArray = GLOBAL_DEFS;
ChallengeDefinition* ChallengeDefinition::_gDefArrayEnd = (ChallengeDefinition*)0x6A3278;
unsigned int ChallengeDefinition::_gUsedDefs = BASE_NUM_GAMEMODES;
unsigned int ChallengeDefinition::_gMaxDefs = BASE_NUM_GAMEMODES;
size_t ChallengeDefinition::_gDefSize = 0x6A3278 - 0x6A2BA0;

unsigned int ChallengeDefinition::_aRefCount = 20;
unsigned int ChallengeDefinition::_aRefs[] =
{
	0x424A0A,
	0x424CEE,
	0x424E46,
	0x42DF7A,
	0x42E066,
	0x42E3E4,
	0x42E425,
	0x42E459,
	0x42E515,
	0x42E541,
	0x42E5AA,
	0x42E5D1,
	0x42E720,
	0x42E8B6,
	0x42E965,
	0x42F834,
	0x42F963,
	0x455BA6,
	0x455C08,
	0x42E7C9
};

ChallengeDefinition* ChallengeDefinition::AddChallenge(const char* Name, ChallengePage Page, int Row, int Col)
{
	if (_gMaxDefs >= _gUsedDefs)
		Reallocate(_gUsedDefs + 1);

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
	unsigned int NewEndAddress = (unsigned int)NewArray + sizeof(ChallengeDefinition) * NewCapacity;

	for (int i = 0; i < _aRefCount; i++)
	{
		auto RefP = (unsigned int*)_aRefs[i];
		unsigned int Ref;

		DWORD OldProt;
		VirtualProtect(RefP, 4, PAGE_EXECUTE_READWRITE, &OldProt);
		Ref = *RefP;

		int sOffset = Ref - (unsigned int)_gDefArray;// Offset from start
		int eOffset = Ref - (unsigned int)_gDefArrayEnd;// Offset from end

		// If it's closer to the start than it is to the end, redirect relative to start
		if (abs(sOffset) <= abs(eOffset))
		{
			Ref = NewDefAddress + sOffset;
			*RefP = Ref;
		}
		else// Otherwise, redirect relative to end
		{
			Ref = NewEndAddress + eOffset;
			*RefP = Ref;
		}

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