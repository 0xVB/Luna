#pragma once
#include "PopStructs.h"

class Sexy::Buffer
{
public:
	PopVector<unsigned char> mData;
	int mDataBitSize;
	int mReadBitPos;
	int mWriteBitPos;

	inline int ByteLeftToRead() { return (mDataBitSize - mReadBitPos + 7) / 8; }
	virtual ~Buffer() {};

	PopWString UTF8ToWideString();
	void SeekFront();
	void Clear();

	void WriteByte(unsigned char);
	void WriteNumBits(int Num, int BitCount);
	void WriteBool(bool);
	void WriteShort(short);
	void WriteLong(long);
	void WriteString(const PopString&);
	void WriteLine(const PopString&);
	void WriteLongString(const PopString&);
	void WriteBytes(const unsigned char* Bytes, int Count);
	void SetData(unsigned char* Ptr, int Count);

	unsigned char ReadByte();
	int ReadNumBits(int Bits, bool Signed);
	bool ReadBool();
	short ReadShort();
	long ReadLong();
	PopString ReadString();
	PopString ReadLine();
	PopString ReadLongString();
	void ReadBytes(unsigned char* Out, int Count);

	const unsigned char* GetDataPtr();
	int GetDataLen();
	bool AtEnd();
};

struct SaveGameContext
{
	Sexy::Buffer mBuffer;
	bool mFailed;
	bool mReading;
};