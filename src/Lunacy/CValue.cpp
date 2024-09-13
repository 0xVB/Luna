#include "Lunacy/CValue.h"
#include <iostream>

void DebugSOut(std::string aStr)
{
	for (int i = 0; i < aStr.length(); i++)
		std::cout << (int)(unsigned char)(aStr[i]) << " ";
	std::cout << "\n";
}

#pragma region CValue
std::string CValue::GetString()
{
	if (GetType() != CVL_STRING) return "";
	unsigned short sLen = *((unsigned short*)(val.c_str() + 1));

	return std::string(val.c_str() + 3, sLen);
}
void CValue::Print()
{
	auto aType = val[0];

	switch (aType)
	{
	case (NUM_CVL_TYPES):
		std::cout << "CVL_TERMINATOR";
		break;

	case (CVL_CHAR):
		std::cout << "CHAR(" << val[1] << ", " << (short)val[1] << ")";
		break;

	case (CVL_UCHAR):
		std::cout << "UCHAR(" << val[1] << ", " << (unsigned short)val[1] << ")";
		break;

	case (CVL_SHORT):
		std::cout << "SHORT(" << GetShort() << ")";
		break;

	case (CVL_USHORT):
		std::cout << "USHORT(" << GetUShort() << ")";
		break;

	case (CVL_INT):
		std::cout << "INT(" << GetInt() << ")";
		break;

	case (CVL_UINT):
		std::cout << "UINT(" << GetUInt() << ")";
		break;

	case (CVL_FLT):
		std::cout << "FLT(" << GetFloat() << ")";
		break;

	case (CVL_DBL):
		std::cout << "DBL(" << GetDouble() << ")";
		break;

	case (CVL_STRING):
		std::cout << "STR(" << GetString() << ")";
		break;

	default:
		std::cout << "OBJ(" << (int)aType << ", " << *((int*)(val.c_str() + 1)) << ")";
		break;
	}
}
char CValue::GetChar()
{
	if (GetType() != CVL_CHAR) return 0;
	return val[1];
}
unsigned char CValue::GetUChar()
{
	if (GetType() != CVL_UCHAR) return 0;
	return (unsigned char)val[1];
}
short CValue::GetShort()
{
	if (GetType() != CVL_SHORT) return 0;
	return *((short*)(val.c_str() + 1));
}
unsigned short CValue::GetUShort()
{
	if (GetType() != CVL_USHORT) return 0;
	return *((unsigned short*)(val.c_str() + 1));
}
int CValue::GetInt()
{
	if (GetType() != CVL_INT) return 0;
	return *((int*)(val.c_str() + 1));
}
unsigned int CValue::GetUInt()
{
	if (GetType() != CVL_UINT) return 0;
	return *((unsigned int*)(val.c_str() + 1));
}
float CValue::GetFloat()
{
	if (GetType() != CVL_FLT) return 0;
	return *((float*)(val.c_str() + 1));
}
double CValue::GetDouble()
{
	if (GetType() != CVL_DBL) return 0;
	return *((double*)(val.c_str() + 1));
}

ParticleSystem* CValue::GetParticleSystem()
{
	if (GetType() != CVL_PARTICLESYSTEM) return 0;
	auto aID = (ParticleSystemID)GetInt();
	return TryToGet(aID);
}
Reanimation* CValue::GetReanimation()
{
	if (GetType() != CVL_REANIMATION) return 0;
	auto aID = (ReanimationID)GetInt();
	return TryToGet(aID);
}
ParticleEmitter* CValue::GetEmitter()
{
	if (GetType() != CVL_EMITTER) return 0;
	auto aID = (ParticleEmitterID)GetInt();
	return TryToGet(aID);
}
Attachment* CValue::GetAttachment()
{
	if (GetType() != CVL_ATTACHMENT) return 0;
	auto aID = (AttachmentID)GetInt();
	return TryToGet(aID);
}
Projectile* CValue::GetProjectile()
{
	if (GetType() != CVL_PROJECTILE) return 0;
	auto aID = (ProjectileID)GetInt();
	return TryToGet(aID);
}
LawnMower* CValue::GetLawnMower()
{
	if (GetType() != CVL_LAWNMOWER) return 0;
	auto aID = (LawnMowerID)GetInt();
	return TryToGet(aID);
}
Particle* CValue::GetParticle()
{
	if (GetType() != CVL_PARTICLE) return 0;
	auto aID = (ParticleID)GetInt();
	return TryToGet(aID);
}
GridItem* CValue::GetGridItem()
{
	if (GetType() != CVL_GRIDITEM) return 0;
	auto aID = (GridItemID)GetInt();
	return TryToGet(aID);
}
Pickup* CValue::GetPickup()
{
	if (GetType() != CVL_PICKUP) return 0;
	auto aID = (PickupID)GetInt();
	return TryToGet(aID);
}
Zombie* CValue::GetZombie()
{
	if (GetType() != CVL_ZOMBIE) return 0;
	auto aID = (ZombieID)GetInt();
	return TryToGet(aID);
}
Plant* CValue::GetPlant()
{
	if (GetType() != CVL_PLANT) return 0;
	auto aID = (PlantID)GetInt();
	return TryToGet(aID);
}
Trail* CValue::GetTrail()
{
	if (GetType() != CVL_TRAIL) return 0;
	auto aID = (TrailID)GetInt();
	return TryToGet(aID);
}

CValue::CValue(char v)
{
	val = "";
	val += CVL_CHAR;
	val += v;
}
CValue::CValue(unsigned char v)
{
	val = "";
	val += CVL_UCHAR;
	val += v;
}
CValue::CValue(short v)
{
	val = "";
	val += CVL_SHORT;
	val.append((const char*)(&v), sizeof(v));
}
CValue::CValue(unsigned short v)
{
	val = "";
	val += CVL_USHORT;
	val.append((const char*)(&v), sizeof(v));
}
CValue::CValue(int v)
{
	val = "";
	val += CVL_INT;
	val.append((const char*)(&v), sizeof(v));
}
CValue::CValue(unsigned int v)
{
	val = "";
	val += CVL_UINT;
	val.append((const char*)(&v), sizeof(v));
}
CValue::CValue(float v)
{
	val = "";
	val += CVL_FLT;
	val.append((const char*)(&v), sizeof(v));
}
CValue::CValue(double v)
{
	val = "";
	val += CVL_DBL;
	val.append((const char*)(&v), sizeof(v));
}

void CValue::SetInt(unsigned int v)
{
	val.append((const char*)(&v), sizeof(v));
}
#define GetValueID(aObj) *((unsigned int*)(aObj + 1))
CValue::CValue(ParticleEmitter* v)
{
	val = "";
	val += CVL_EMITTER;
	SetInt(GetValueID(v));
}
CValue::CValue(ParticleSystem* v)
{
	val = "";
	val += CVL_PARTICLESYSTEM;
	SetInt(GetValueID(v));
}
#include "Lunacy/Reanimation.h"
CValue::CValue(Reanimation* v)
{
	val = "";
	val += CVL_REANIMATION;
	SetInt(GetValueID(v));
}
#include "Lunacy/Attachment.h"
CValue::CValue(Attachment* v)
{
	val = "";
	val += CVL_ATTACHMENT;
	SetInt(GetValueID(v));
}
#include "Lunacy/Projectile.h"
CValue::CValue(Projectile* v)
{
	val = "";
	val += CVL_PROJECTILE;
	SetInt(GetValueID(v));
}
#include "Lunacy/LawnMower.h"
CValue::CValue(LawnMower* v)
{
	val = "";
	val += CVL_LAWNMOWER;
	SetInt(GetValueID(v));
}
CValue::CValue(Particle* v)
{
	val = "";
	val += CVL_PARTICLE;
	SetInt(GetValueID(v));
}
#include "Lunacy/GridItem.h"
CValue::CValue(GridItem* v)
{
	val = "";
	val += CVL_GRIDITEM;
	SetInt(GetValueID(v));
}
#include "Lunacy/Pickup.h"
CValue::CValue(Pickup* v)
{
	val = "";
	val += CVL_PICKUP;
	SetInt(GetValueID(v));
}
#include "Lunacy/Zombie.h"
CValue::CValue(Zombie* v)
{
	val = "";
	val += CVL_ZOMBIE;
	SetInt(GetValueID(v));
}
#include "Lunacy/Plant.h"
CValue::CValue(Plant* v)
{
	val = "";
	val += CVL_PLANT;
	SetInt(GetValueID(v));
}
CValue::CValue(Trail* v)
{
	val = "";
	val += CVL_TRAIL;
	SetInt(GetValueID(v));
}
CValue::CValue()
{
	val = "" + NUM_CVL_TYPES;
}
CValue::CValue(const char* aPtr)
{
	auto aType = *aPtr;
	val = aType;
	aPtr++;

	switch (aType)
	{
	case CVL_CHAR:
	case CVL_UCHAR:
		val += *aPtr;
		break;

	case CVL_SHORT:
	case CVL_USHORT:
		val.append(aPtr, 2);
		break;

	case CVL_DBL:
		val.append(aPtr, 8);
		break;

	case CVL_STRING:
		val.append(aPtr, (*(unsigned short*)aPtr) + 2);
		break;

	default:
		val.append(aPtr, 4);
		break;
	}
}
CValue::CValue(std::string aStr)
{
	auto aLen = aStr.length();
	val = CVL_STRING;
	val.append((const char*)&aLen, 2);
	val.append(aStr.c_str(), aLen);
}
#pragma endregion


#pragma region CValueManager
CValueManager* CValueManager::_manager = nullptr;
CValueManager* CValueManager::GetSingleton()
{
	if (_manager) return _manager;
	_manager = new CValueManager();
	return _manager;
}

std::string CValueManager::GetSaveString()
{
	std::string aStr = "";
	for (auto& aObject : *_values)
	{
		aStr += aObject.first;
		for (auto& aKV : *aObject.second)
			aStr += aKV.first + aKV.second;
		aStr += _cvl_terminator;
	}
	aStr += _cvl_terminator;

	return aStr;
}
void CValueManager::LoadSaveString(const std::string& aStr)
{
	Flush();
	if (aStr.size() == 0)
		return;

	auto aPtr = aStr.c_str();
	CValue oVal, kVal, vVal;
	std::map<std::string, std::string>* aMap = nullptr;

LoadObject:
	if (*aPtr == _cvl_terminator) goto TerminateCVL;

	aMap = nullptr;
	oVal = CValue(aPtr);
	aPtr += oVal.GetSize();

LoadKV:
	if (*aPtr == _cvl_terminator)
	{
		aPtr++;
		goto LoadObject;
	}
	if (!aMap)
	{
		// Construct the map only if fields exist to avoid stray pointers
		aMap = new std::map<std::string, std::string>();
		(*_values)[oVal.GetEncode()] = aMap;
	}

	kVal = CValue(aPtr); aPtr += kVal.GetSize();
	vVal = CValue(aPtr); aPtr += vVal.GetSize();
	(*aMap)[kVal.GetEncode()] = vVal.GetEncode();
	goto LoadKV;

TerminateCVL:
	return;
}
void CValueManager::SyncValues(SaveGameContext* aContext)
{
	if (aContext->mReading)
		// Game is loading
		LoadSaveString(aContext->mBuffer.ReadLongString());
	else
		// Game is saving
		aContext->mBuffer.WriteLongString(GetSaveString());
}

CValueManager::CValueManager()
{
	_values = new std::map<std::string, std::map<std::string, std::string>*>();
}

void CValueManager::Flush()
{
	if (_values->empty())
		return;

	for (auto& aObject : *_values)
		delete aObject.second;
	_values->clear();
}
bool CValueManager::MapExists(CValue ObjectValue)
{
	return _values->find(ObjectValue.GetEncode()) != _values->end();
}
void CValueManager::CreateMap(CValue Object)
{
	RemoveMap(Object);
	(*_values)[Object.GetEncode()] = new std::map<std::string, std::string>();
}
void CValueManager::RemoveMap(CValue Object)
{
	auto it = _values->find(Object.GetEncode());
	if (it != _values->end())
	{
		delete it->second;
		_values->erase(it);
	}
}

bool CValueManager::HasValue(CValue Object, std::string Key)
{
	CValue aKey = CValue(Key);

	// Check if Object map exists
	auto objIt = _values->find(Object.GetEncode());
	if (objIt == _values->end())  // Object map does not exist
		return false;

	// Check if Key exists in the object map
	auto& aMap = objIt->second;  // Use a reference to the map
	auto keyIt = aMap->find(aKey.GetEncode());
	if (keyIt == aMap->end())  // Key does not exist
		return false;

	// Key & object map exists
	return true;
}
CValue CValueManager::GetValue(CValue Object, std::string Key)
{
	CValue aRes, aKey;
	aKey = CValue(Key);

	// Check if Object map exists
	auto objIt = _values->find(Object.GetEncode());
	if (objIt == _values->end())  // Object map does not exist
		return CValue();

	// Check if Key exists in the object map
	auto& aMap = objIt->second;  // Use a reference to the map
	auto keyIt = aMap->find(aKey.GetEncode());
	if (keyIt == aMap->end())  // Key does not exist
		return CValue();

	// Return the value associated with the Key
	aRes.SetEncode(keyIt->second);
	return aRes;
}
void CValueManager::SetValue(CValue Object, std::string Key, CValue Value)
{
	// Ensure map for the object exists
	if (!MapExists(Object))
		CreateMap(Object);

	// Insert or update the key-value pair in the map
	auto& aMap = (*_values)[Object.GetEncode()];
	(*aMap)[CValue(Key).GetEncode()] = Value.GetEncode();  // Use [] for update or insert
}

bool CValueManager::HasCVL(CValue Object, CValue aKey)
{
	// Check if Object map exists
	auto objIt = _values->find(Object.GetEncode());
	if (objIt == _values->end())  // Object map does not exist
		return false;

	// Check if Key exists in the object map
	auto& aMap = objIt->second;  // Use a reference to the map
	auto keyIt = aMap->find(aKey.GetEncode());
	if (keyIt == aMap->end())  // Key does not exist
		return false;

	// Key & object map exists
	return true;
}
CValue CValueManager::GetCVL(CValue Object, CValue aKey)
{
	CValue aRes;

	// Check if Object map exists
	auto objIt = _values->find(Object.GetEncode());
	if (objIt == _values->end())  // Object map does not exist
		return CValue();

	// Check if Key exists in the object map
	auto& aMap = objIt->second;  // Use a reference to the map
	auto keyIt = aMap->find(aKey.GetEncode());
	if (keyIt == aMap->end())  // Key does not exist
		return CValue();

	// Return the value associated with the Key
	aRes.SetEncode(keyIt->second);
	return aRes;
}
void CValueManager::SetCVL(CValue Object, CValue aKey, CValue Value)
{
	// Ensure map for the object exists
	if (!MapExists(Object))
		CreateMap(Object);

	// Insert or update the key-value pair in the map
	auto& aMap = (*_values)[Object.GetEncode()];
	(*aMap)[aKey.GetEncode()] = Value.GetEncode();  // Use [] for update or insert
}
#pragma endregion