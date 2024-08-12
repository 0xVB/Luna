#pragma once
#include <Windows.h>
#include <string>
#include <map>
/* Hi, VB here
* DataArrays allocate a large block of memory and then reuses this memory block to	|
* store classes of different types. The game uses DataArrays to store plants,		|
* zombies, grid items, etc. this makes it so that there isn't a lot of redundancy	|
* when allocating pointers too much. This however makes an issue of class pointers	|
* being reused, so you can't use the object's pointer to reference it consitently.	|
*																					|
* For this reason, the PlantID, ZombieID, etc values exist. They can be used via	|
* the Lawn->Plants->Fetch(PlantID) to get the plant with that ID or return NULL if	|
* the plant died or has been replaced by a different plant.							|
*																					|
* ID Explanation:																	|
* The higher 16 bits of mID represent a unique counter that goes up with each		|
* allocation in the DataArray. The lower 16 bits are the object's index in the		|
* array. This makes it so that each object has a unique ID and can be consistently	|
* accessed with that id.															|
*/

template <typename T>
class DataArray
{
public:
	class DataArrayItem : public T
	{
	public:
		DataArrayItem() : T() {}
		unsigned int mID = 0;

		static inline unsigned short GetCounter(unsigned int ID)
		{
			// Return the upper 16 bits of ID
			return (unsigned short)(ID >> 16);
		}

		static inline unsigned short GetIndex(unsigned int ID)
		{
			// Return the lower 16 bits of ID
			return (unsigned short)(ID);
		}

		bool IsAllocated()
		{
			return mID & 0xFFFF0000;
		}

		void Deallocate()
		{
			mID &= 0x0000FFFF;
		}
	};

private:
	DataArrayItem* mBlock;

public:
	// The highest number of elements used ever at one point of time
	unsigned int mMaxUsedCount = 0;
	// The maximum number of elements this DataArray can hold
	unsigned int mMaxSize = 0;
	// The first free index
	unsigned int mFreeListHead = 0;
	// The current number of allocated elements
	unsigned int mSize = 0;
	// The incremental ID counter
	unsigned int mNextKey = 1;
	// The DataArray name
	const char* mName = nullptr;
	
	// Allocates a new item into the data array.
	DataArrayItem* Allocate()
	{
		DataArrayItem* aItem;
		unsigned int aFreeListHead;
		unsigned int aMaxUsedCount;

		aFreeListHead = mFreeListHead;
		aMaxUsedCount = mMaxUsedCount;
		if (aFreeListHead == aMaxUsedCount)
		{
			mMaxUsedCount++;
			mFreeListHead++;
		}
		else
			mFreeListHead = (unsigned int)(unsigned short)(mBlock[aFreeListHead].mID);

		aItem = mBlock + aFreeListHead;
		memset(aItem, 0, sizeof(DataArrayItem));

		aItem->mID = mNextKey << 0x10 | aFreeListHead;
		mNextKey = mNextKey + 1;

		if (mNextKey == 0x10000)
			mNextKey = 1;

		mSize = mSize + 1;
		new (aItem) DataArrayItem();

		return aItem;
	}

	// Attempts to obtain the item with the given ID. Returns NULL if it died.
	DataArrayItem* Fetch(unsigned int ID)
	{
		auto aCounter = DataArrayItem::GetCounter(ID);
		auto aIndex = DataArrayItem::GetIndex(ID);
		if (ID == 0 || aIndex > mMaxSize) return nullptr;
		
		auto aItem = mBlock + aIndex;
		if (DataArrayItem::GetCounter(aItem->mID) != aCounter) return nullptr;

		return aItem;
	}

	// Sets CurrentItem to the next ite in the array and returns true if an item was found.
	bool Next(DataArrayItem** CurrentItem)
	{
		auto MaxItem = mBlock + mMaxUsedCount;
		DataArrayItem* Item = *CurrentItem;

		if (Item == nullptr)
			Item = mBlock;
		else
			Item++;

		while (Item <= MaxItem)
		{
			if (Item->IsAllocated())
			{
				*CurrentItem = Item;
				return true;
			}
			Item++;
		}

		*CurrentItem = (DataArrayItem*)-1;
		return false;
	}
	bool Next(T** CurrentItem)
	{
		return Next((DataArrayItem**)CurrentItem);
	}
	DataArrayItem* GetNext(DataArrayItem* Item = nullptr)
	{
		DataArrayItem* Dummy = Item;

		if (Next(&Dummy))
			return Dummy;
		return NULL;
	}

	bool IsAllocated(DataArrayItem* Item)
	{
		// If the higher 16 bits are zero, the item is unallocated.
		return Item->mID & 0xFFFF0000;
	}

	// Attempts to deallocate the item with the given ID if it exists. Returns true if the item was found and deallocated.
	bool Deallocate(unsigned int ID)
	{
		auto aItem = Fetch(ID);
		if (!aItem) return false;

		mFreeListHead = min(mFreeListHead, DataArrayItem::GetIndex(aItem->mID));
		mSize--;

		aItem->Deallocate();
	}
	
	// Deallocates all the items but does not destroy the block.
	void Flush()
	{
		DataArrayItem* aItem = mBlock;
		unsigned int aFreeListHead;

		// Iterare over all items
		while (mBlock + mMaxUsedCount > aItem) {
			// If the item is deallocated, increment it until finding an allocated item
			while (!IsAllocated(aItem))
			{
				aItem++;
			}

			aFreeListHead = mFreeListHead;
			mFreeListHead = aItem->mID & 0x0000FFFF;
			aItem->mID = aFreeListHead;
			mSize--;
		}

	Exit:
		mFreeListHead = 0;
		mMaxUsedCount = 0;
		return;
	}

	~DataArray()
	{

	}
};

class Allocator
{
public:
	void* mFreeList;
	void* mBlockList;
	int mGrowCount;
	int mTotalItems;
	int mItemSize;
};

template <typename T>
class List
{
public:
	class ListNode
	{
	public:
		T mValue;
		ListNode* mNext;
		ListNode* mPrev;
	};


	ListNode* mHead;
	ListNode* mTail;
	int mSize;
	Allocator* mAllocator;
};
