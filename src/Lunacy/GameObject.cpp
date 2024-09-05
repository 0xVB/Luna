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

#pragma region Convenience Stuff
int GameObject::GetColumn()
{
	auto Center = mHitbox.GetCenter();
	return mLawn->PixelToGridX(Center.mX, Center.mY);
}
int GameObject::GetLane()
{
	auto Center = mHitbox.GetCenter();
	return mLawn->PixelToGridY(Center.mX, Center.mY);
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

Projectile* GameObject::GetNearestProjectile(float MinDist, float MaxDist, ProjectileType Filter, bool IsBlacklist)
{
	return mLawn->GetNearestProjectile(mHitbox.GetCenter(), MinDist, MaxDist, Filter, IsBlacklist);
}
GridItem* GameObject::GetNearestGridItem(float MinDist, float MaxDist, GridItemType Filter, bool IsBlacklist)
{
	return mLawn->GetNearestGridItem(mHitbox.GetCenter(), MinDist, MaxDist, Filter, IsBlacklist);
}
Zombie* GameObject::GetNearestZombie(float MinDist, float MaxDist, ZombieType Filter, bool IsBlacklist)
{
	return mLawn->GetNearestZombie(mHitbox.GetCenter(), MinDist, MaxDist, Filter, IsBlacklist);
}
Pickup* GameObject::GetNearestPickup(float MinDist, float MaxDist, PickupType Filter, bool IsBlacklist)
{
	return mLawn->GetNearestPickup(mHitbox.GetCenter(), MinDist, MaxDist, Filter, IsBlacklist);
}
Plant* GameObject::GetNearestPlant(float MinDist, float MaxDist, SeedType Filter, bool IsBlacklist)
{
	return mLawn->GetNearestPlant(mHitbox.GetCenter(), MinDist, MaxDist, Filter, IsBlacklist);
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
#pragma endregion

#pragma region Association Stuff
AssociationManager* GameObject::GetManager()
{
	return GetAssociation(_cave);
}

void GameObject::AddTag(std::string N)
{
	return GetManager()->Set(N, true);
}

bool GameObject::HasTag(std::string N)
{
	return GetManager()->Get(N).Boolean;
}

void GameObject::RemoveTag(std::string N)
{
	GetManager()->Delete(N);
}

void GameObject::SetNumber(std::string N, double D)
{
	GetManager()->Set(N, D);
}

double GameObject::GetNumber(std::string N)
{
	return GetManager()->Get(N).Double;
}

void GameObject::SetVector2(std::string N, Sexy::FVector2 V2)
{
	GetManager()->Set(N, V2);
}

Sexy::FVector2 GameObject::GetVector2(std::string N)
{
	return GetManager()->Get(N).F2;
}

void GameObject::SetVector3(std::string N, Sexy::FVector3 V3)
{
	GetManager()->Set(N, V3);
}

Sexy::FVector3 GameObject::GetVector3(std::string N)
{
	return GetManager()->Get(N).F3;
}

void GameObject::SetRect(std::string N, Sexy::FRect FR)
{
	GetManager()->Set(N, FR);
}

Sexy::FRect GameObject::GetRect(std::string N)
{
	return GetManager()->Get(N).FR;
}

void GameObject::SetPointer(std::string N, void* _)
{
	GetManager()->Set(N, _);
}

void* GameObject::GetPointer(std::string N)
{
	return GetManager()->Get(N).Pointer;
}

void GameObject::DestroyFields()
{
	DeleteAssociation(_cave);
}
#pragma endregion
