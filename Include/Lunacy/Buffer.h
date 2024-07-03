#pragma once

#include "ForwardDefinitions.h"

class Sexy::Buffer
{
public:
	PopVector<unsigned char> mData;
	int mDataBitSize;
	int mReadBitPos;
	int mWriteBitPos;

	virtual ~Buffer() {};
};