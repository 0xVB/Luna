#include "Lunacy/Associations.h"
#include <stack>

unsigned int MaxIndex = 0;
std::vector<AssociationManager> Managers = std::vector<AssociationManager>();
std::stack<unsigned int> Indices = std::stack<unsigned int>();

unsigned int AllocateAssociation()
{
	if (Indices.empty())
		return MaxIndex++;

	auto Result = Indices.top();
	Indices.pop();
	return Result;
}

AssociationManager* GetAssociation(char* Cave)
{
	unsigned int Index = ((*(unsigned int*)Cave) & 0x00FFFFFF);

	if (Index == 0)// Unallocated
	{
		Index = AllocateAssociation() + 1;

		Cave[0] = Index;
		Cave[1] = Index >> 8;
		Cave[2] = Index >> 16;

		Index--;
		if (Index == Managers.size())
			Managers.push_back(AssociationManager());// Allocate new manager
		else
			Managers[Index] = AssociationManager();// Clear old manager

		return &Managers[Index];
	}

	return &Managers[Index];
}

void DeleteAssociation(char* Cave)
{
	unsigned int Index = ((*(unsigned int*)Cave) & 0x00FFFFFF);
	if (Index == 0) return;// Unallocated

	Cave[0] = 0;
	Cave[1] = 0;
	Cave[2] = 0;
	Indices.push(Index);
}

AssociationManager::Association::Association(const Association& _)
{
	FR = _.FR;
}

AssociationManager::Association& AssociationManager::Association::operator=(const Association& _)
{
	if (this != &_)
		FR = _.FR;
	return *this;
}

AssociationManager::Association AssociationManager::Get(std::string Key)
{
	auto _ = Associations.find(Key);
	if (_ != Associations.end())
		return _->second;
	else
		return Association();
}

void AssociationManager::Set(std::string Key, Association Val)
{
	Associations[Key] = Val;
}

void AssociationManager::Delete(std::string Key)
{
	auto _ = Associations.find(Key);
	if (_ != Associations.end())
		Associations.erase(_);
}

AssociationManager::Association::Association(bool _)
{
	Boolean = _;
}

AssociationManager::Association::Association(void* _)
{
	Pointer = _;
}

AssociationManager::Association::Association(double _)
{
	Double = _;
}

AssociationManager::Association::Association(Sexy::FRect _)
{
	FR = _;
}

AssociationManager::Association::Association(Sexy::FVector2 _)
{
	F2 = _;
}

AssociationManager::Association::Association(Sexy::FVector3 _)
{
	F3 = _;
}