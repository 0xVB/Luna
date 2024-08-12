#include "Lunacy/LawnApp.h"
#include "Lunacy/GameObject.h"
#include "Lunacy/Lawn.h"

GameObject::GameObject()
{
	ConstructGameObject();
}

void GameObject::ConstructGameObject()
{
	mApp = LawnApp::GetApp();
	mLawn = mApp->mLawn;

	mX = 0;
	mY = 0;
	mWidth = 0;
	mHeight = 0;
	mVisible = false;
	mRow = 0;
	mRenderOrder = RENDER_LAYER_LAWN;
}

float GameObject::DistanceFrom(Sexy::IVector2 Other)
{
	return Other.GetDistance(mHitbox.GetCenter());
}
bool GameObject::CollidesWith(Sexy::IRect Other)
{
	return Other.Intersects(mHitbox);
}
GameObject::operator Sexy::Rect<int>()
{
	return mHitbox;
}
GameObject::operator Sexy::Vector2<int>()
{
	return mHitbox.GetCenter();
}
Sexy::IVector2 GameObject::GetGridPos()
{
	return mLawn->PixelToGrid(mX + mWidth / 2, mY + mHeight / 2);
}

Projectile* GameObject::GetNearestProjectile(float MinDist, ProjectileType Filter, bool IsBlacklist)
{
	return mLawn->GetNearestProjectile(mHitbox.GetCenter(), MinDist, Filter, IsBlacklist);
}
GridItem* GameObject::GetNearestGridItem(float MinDist, GridItemType Filter, bool IsBlacklist)
{
	return mLawn->GetNearestGridItem(mHitbox.GetCenter(), MinDist, Filter, IsBlacklist);
}
Zombie* GameObject::GetNearestZombie(float MinDist, ZombieType Filter, bool IsBlacklist)
{
	return mLawn->GetNearestZombie(mHitbox.GetCenter(), MinDist, Filter, IsBlacklist);
}
Pickup* GameObject::GetNearestPickup(float MinDist, PickupType Filter, bool IsBlacklist)
{
	return mLawn->GetNearestPickup(mHitbox.GetCenter(), MinDist, Filter, IsBlacklist);
}
Plant* GameObject::GetNearestPlant(float MinDist, SeedType Filter, bool IsBlacklist)
{
	return mLawn->GetNearestPlant(mHitbox.GetCenter(), MinDist, Filter, IsBlacklist);
}

std::list<Projectile*> GameObject::GetProjectilesAround(int LR, int CR, ProjectileType T, bool B)
{
	auto GridPos = GetGridPos();
	auto Area = mLawn->GridToPixelArea(GridPos.mX - CR, GridPos.mY - LR, CR * 2 + 1, LR * 2 + 1);
	return mLawn->GetProjectilesInArea(Area, T, B);
}
std::list<GridItem*> GameObject::GetGridItemsAround(int LR, int CR, GridItemType T, bool B)
{
	auto GridPos = GetGridPos();
	auto Area = mLawn->GridToPixelArea(GridPos.mX - CR, GridPos.mY - LR, CR * 2 + 1, LR * 2 + 1);
	return mLawn->GetGridItemsInArea(Area, T, B);
}
std::list<Zombie*> GameObject::GetZombiesAround(int LR, int CR, ZombieType T, bool B)
{
	auto GridPos = GetGridPos();
	auto Area = mLawn->GridToPixelArea(GridPos.mX - CR, GridPos.mY - LR, CR * 2 + 1, LR * 2 + 1);
	return mLawn->GetZombiesInArea(Area, T, B);
}
std::list<Pickup*> GameObject::GetPickupsAround(int LR, int CR, PickupType T, bool B)
{
	auto GridPos = GetGridPos();
	auto Area = mLawn->GridToPixelArea(GridPos.mX - CR, GridPos.mY - LR, CR * 2 + 1, LR * 2 + 1);
	return mLawn->GetPickupsInArea(Area, T, B);
}
std::list<Plant*> GameObject::GetPlantsAround(int LR, int CR, SeedType T, bool B)
{
	auto GridPos = GetGridPos();
	auto Area = mLawn->GridToPixelArea(GridPos.mX - CR, GridPos.mY - LR, CR * 2 + 1, LR * 2 + 1);
	return mLawn->GetPlantsInArea(Area, T, B);
}