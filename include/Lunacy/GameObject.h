#pragma once
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
	int mRow;
	int mRenderOrder;

	GameObject();
	float DistanceFrom(Sexy::IVector2);
	bool CollidesWith(Sexy::IRect);

	Sexy::IVector2 GetGridPos();

	Projectile* GetNearestProjectile(float MinDist = 0, ProjectileType Filter = (ProjectileType)-1, bool IsBlacklist = false);
	GridItem* GetNearestGridItem(float MinDist = 0, GridItemType = GRIDITEM_NONE, bool IsBlacklist = false);
	Zombie* GetNearestZombie(float MinDist = 0, ZombieType = (ZombieType)-1, bool IsBlacklist = false);
	Pickup* GetNearestPickup(float MinDist = 0, PickupType = PICKUP_NONE, bool IsBlacklist = false);
	Plant* GetNearestPlant(float MinDist = 0, SeedType = SEED_NONE, bool IsBlacklist = false);

	std::list<Projectile*> GetProjectilesAround(int LaneRange = 1, int ColRange = 1, ProjectileType = (ProjectileType)-1, bool IsBlacklist = false);
	std::list<GridItem*> GetGridItemsAround(int LaneRange = 1, int ColRange = 1, GridItemType = GRIDITEM_NONE, bool IsBlacklist = false);
	std::list<Zombie*> GetZombiesAround(int LaneRange = 1, int ColRange = 1, ZombieType = (ZombieType)-1, bool IsBlacklist = false);
	std::list<Pickup*> GetPickupsAround(int LaneRange = 1, int ColRange = 1, PickupType = PICKUP_NONE, bool IsBlacklist = false);
	std::list<Plant*> GetPlantsAround(int LaneRange = 1, int ColRange = 1, SeedType = SEED_NONE, bool IsBlacklist = false);

	operator Sexy::IVector2();
	operator Sexy::IRect();
protected:
	void ConstructGameObject();
};