#pragma once
#include "ForwardDefinitions.h"
#include "GameObject.h"

class SeedPacket : public GameObject
{
public:
	int mRefreshCounter;
	int mRefreshTime;
	int mIndex;
	int mOffsetX;
	SeedType mPacketType;
	SeedType mImitaterType;
	int mSlotMachineCountDown;
	SeedType mSlotMachiningNextSeed;
	float mSlotMachiningPosition;
	bool mActive;
	bool mRefreshing;
	int mTimesUsed;

	SeedPacket(SeedType = SEED_NONE, SeedType = SEED_NONE);

	void SetPacketType(SeedType, SeedType Imitater = SEED_NONE);
	void PickNextSlotMachineSeed();
	void FlashIfReady();
	void Update();
	void Draw(Sexy::Graphics*);
	bool CanPickUp();
	void MouseDown();
	void OnPlanted();
	bool MouseHitTest(int X, int Y, HitResult*);

	static void __stdcall DrawSeed(Sexy::Graphics*, float X, float Y, SeedType, SeedType Imitater, float OffsetX, float OffsetY, float Scale);
	static void __cdecl DrawSeedPacket(Sexy::Graphics*, float X, float Y, SeedType, SeedType Imitater, float DarkPercent, int Grayness, bool DrawCost, bool UseCurrentCost);
};


class SeedBank : public GameObject
{
public:
	int mNumPackets;
	SeedPacket mSeedPackets[10];
	int mCutSceneDarken;
	int mConveyorBeltCounter;

	SeedBank();
	
	void Draw(Sexy::Graphics*);
	bool MouseHitTest(int X, int Y, HitResult*);
	bool ContainsPoint(int X, int Y);
	void AddSeed(SeedType);
	void RemoveSeed(int Index);
	int GetNumSeedsOnConveyorBelt();
	void UpdateConveyorBelt();
	void UpdateWidth();
	void RefreshAllPackets();
};