#pragma once

#ifndef SEXY_BUFFER_DEF
#define SEXY_BUFFER_DEF
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


#endif // !SEXY_BUFFER_DEF