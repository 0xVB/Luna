#pragma once
#include "Associations.h"
#include "CGeometry.h"
#include <string>
#include <map>

class GameObject
{
public:
	LawnApp* mApp;
	Lawn* mLawn;
	union
	{
		struct
		{
			int mX;
			int mY;
			int mWidth;
			int mHeight;
		};
		struct
		{
			Sexy::IVector2 mPosition;
			Sexy::IVector2 mSize;
		};
		Sexy::IRect mHitbox;
	};
	bool mVisible;

protected:
	char _cave[3];
	AssociationManager* GetManager();

public:
	union
	{
		int mRow;
		int mLane;
	};
	int mRenderOrder;

	GameObject();
	float DistanceFrom(Sexy::IVector2);
	bool CollidesWith(Sexy::IRect);
	int GetLane();
	int GetColumn();

	Sexy::IVector2 GetGridPos();

	Projectile* GetNearestProjectile(float MinDist = 0, float MaxDist = 9e5, ProjectileType Filter = (ProjectileType)-1, bool IsBlacklist = false);
	GridItem* GetNearestGridItem(float MinDist = 0, float MaxDist = 9e5, GridItemType = GRIDITEM_NONE, bool IsBlacklist = false);
	Zombie* GetNearestZombie(float MinDist = 0, float MaxDist = 9e5, ZombieType = (ZombieType)-1, bool IsBlacklist = false);
	Pickup* GetNearestPickup(float MinDist = 0, float MaxDist = 9e5, PickupType = PICKUP_NONE, bool IsBlacklist = false);
	Plant* GetNearestPlant(float MinDist = 0, float MaxDist = 9e5, SeedType = SEED_NONE, bool IsBlacklist = false);

	std::list<Projectile*> GetProjectilesAround(int LaneRange = 1, int ColRange = 1, ProjectileType = (ProjectileType)-1, bool IsBlacklist = false);
	std::list<GridItem*> GetGridItemsAround(int LaneRange = 1, int ColRange = 1, GridItemType = GRIDITEM_NONE, bool IsBlacklist = false);
	std::list<Zombie*> GetZombiesAround(int LaneRange = 1, int ColRange = 1, ZombieType = (ZombieType)-1, bool IsBlacklist = false);
	std::list<Pickup*> GetPickupsAround(int LaneRange = 1, int ColRange = 1, PickupType = PICKUP_NONE, bool IsBlacklist = false);
	std::list<Plant*> GetPlantsAround(int LaneRange = 1, int ColRange = 1, SeedType = SEED_NONE, bool IsBlacklist = false);

	operator Sexy::IVector2();
	operator Sexy::IRect();

	void AddTag(std::string TagName);
	bool HasTag(std::string TagName);
	void RemoveTag(std::string TagName);

	void SetNumber(std::string Name, double);
	double GetNumber(std::string Name);

	void SetVector2(std::string Name, Sexy::FVector2);
	Sexy::FVector2 GetVector2(std::string Name);

	void SetVector3(std::string Name, Sexy::FVector3);
	Sexy::FVector3 GetVector3(std::string Name);

	void SetRect(std::string Name, Sexy::FRect);
	Sexy::FRect GetRect(std::string Name);

	void SetPointer(std::string Name, void*);
	void* GetPointer(std::string Name);
	void DestroyFields();

protected:
	void ConstructGameObject();
};// 36U