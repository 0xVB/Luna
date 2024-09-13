#pragma once
#include "Particle.h"
#include "Buffer.h"
#include "Trail.h"
#include "Lawn.h"

class CValue
{
private:
	std::string val;
	void SetInt(unsigned int);
public:
	enum CValueType : unsigned char
	{
		CVL_STRING,

		CVL_CHAR,
		CVL_UCHAR,

		CVL_SHORT,
		CVL_USHORT,

		CVL_INT,
		CVL_UINT,

		CVL_FLT,
		CVL_DBL,

		CVL_PARTICLESYSTEM,
		CVL_REANIMATION,
		CVL_ATTACHMENT,
		CVL_PROJECTILE,
		CVL_LAWNMOWER,
		CVL_PARTICLE,
		CVL_GRIDITEM,
		CVL_EMITTER,
		CVL_PICKUP,
		CVL_ZOMBIE,
		CVL_PLANT,
		CVL_TRAIL,

		NUM_CVL_TYPES
	};

	__inline CValueType GetType() { return (CValueType)((unsigned char)val[0]); }
	__inline size_t GetSize() { return val.length(); }
	__inline std::string GetEncode() { return val; }
	__inline void SetEncode(std::string Encode) { val = Encode; }
	std::string GetString();
	void Print();

	char GetChar();
	unsigned char GetUChar();

	short GetShort();
	unsigned short GetUShort();

	int GetInt();
	unsigned int GetUInt();

	float GetFloat();
	double GetDouble();

	ParticleSystem* GetParticleSystem();
	Reanimation* GetReanimation();
	ParticleEmitter* GetEmitter();
	Attachment* GetAttachment();
	Projectile* GetProjectile();
	LawnMower* GetLawnMower();
	Particle* GetParticle();
	GridItem* GetGridItem();
	Pickup* GetPickup();
	Zombie* GetZombie();
	Plant* GetPlant();
	Trail* GetTrail();

	CValue(std::string);
	CValue(const char*);
	CValue();

	CValue(char);
	CValue(unsigned char);

	CValue(short);
	CValue(unsigned short);

	CValue(int);
	CValue(unsigned int);

	CValue(float);
	CValue(double);

	CValue(ParticleEmitter*);
	CValue(ParticleSystem*);
	CValue(Reanimation*);
	CValue(Attachment*);
	CValue(Projectile*);
	CValue(LawnMower*);
	CValue(Particle*);
	CValue(GridItem*);
	CValue(Pickup*);
	CValue(Zombie*);
	CValue(Plant*);
	CValue(Trail*);

	__inline operator char() { return GetChar(); }
	__inline operator unsigned char() { return GetUChar(); }

	__inline operator short() { return GetShort(); }
	__inline operator unsigned short() { return GetUShort(); }

	__inline operator int() { return GetInt(); }
	__inline operator unsigned int() { return GetUInt(); }

	__inline operator float() { return GetFloat(); }
	__inline operator double() { return GetDouble(); }

	__inline operator ParticleSystem*() { return GetParticleSystem(); }
	__inline operator ParticleEmitter*() { return GetEmitter(); }
	__inline operator Reanimation*() { return GetReanimation(); }
	__inline operator Attachment*() { return GetAttachment(); }
	__inline operator Projectile*() { return GetProjectile(); }
	__inline operator LawnMower*() { return GetLawnMower(); }
	__inline operator Particle*() { return GetParticle(); }
	__inline operator GridItem*() { return GetGridItem(); }
	__inline operator Pickup*() { return GetPickup(); }
	__inline operator Zombie*() { return GetZombie(); }
	__inline operator Plant*() { return GetPlant(); }
	__inline operator Trail*() { return GetTrail(); }
};


/// <summary>
/// Manages your values and associations with certain classes.
/// 
/// Hooks required:
/// 1. On Object Death	(RemoveMap)
/// 2. On New Game		(Flush)
/// 3. On Kill Game		(Flush)
/// 3. On Save Game		(SyncValues)
/// 4. On Load Game		(SyncValues)
/// </summary>
class CValueManager
{
private:
	std::map<std::string, std::map<std::string, std::string>*>* _values;
	CValueManager();

	static constexpr const char* _cvl_header = "CVL_HEADER";
	static constexpr const short _cvl_header_size = 10;
	static constexpr const char _cvl_terminator = CValue::NUM_CVL_TYPES;
	static CValueManager* _manager;

public:
	static CValueManager* GetSingleton();// Gets the manager if it exists and creates one if not

	std::string GetSaveString();
	void LoadSaveString(const std::string&);
	void SyncValues(SaveGameContext*);

	void Flush();// Flushes all values in the current manager
	
	bool MapExists(CValue);// Returns true if a map exists for the given value
	void CreateMap(CValue);// Creates a new map for the given value
	void RemoveMap(CValue);// Removes the map for the given value

	bool HasValue(CValue Object, std::string Key);// Returns true if the key exists in the object
	CValue GetValue(CValue Object, std::string Key);// Returns the value with the key in the given object
	void SetValue(CValue Object, std::string Key, CValue Value);// Sets the value with the key in the given object

	// CValue keys
	bool HasCVL(CValue Object, CValue Key);
	CValue GetCVL(CValue Object, CValue Key);
	void SetCVL(CValue Object, CValue Key, CValue Value);
};