#include "Lunacy/Reallocators/Consts.h"
#include "Lunacy/Reanimation.h"

ReanimationParams* ReanimatorDefinition::_newParams = nullptr;
void ReanimatorDefinition::Reallocate(unsigned int Capacity)
{
	_newParams = (ReanimationParams*)Constants::ReanimDef::REALLOCATE(Capacity);
}

ReanimationParams* ReanimatorDefinition::NewReanim(ReanimationType aType, const char* aFileName)
{
	if (!_newParams) Reallocate(aType * 2);
	*(_newParams + aType) = ReanimationParams(aType, aFileName);
	return _newParams + aType;
}