#pragma once
#include "PopStructs.h"

class Sexy::Buffer
{
public:
	PopVector<unsigned char> mData;
	int mDataBitSize;
	int mReadBitPos;
	int mWriteBitPos;

	virtual ~Buffer() {};
};