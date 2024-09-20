#pragma once
#include <Windows.h>
#include <string.h>
#include <sstream>

namespace Mem
{
	void Unlock(DWORD Address, size_t Size = 4U);
	void Unlock(void* Address, size_t Size = 4U);
	void Unlock(const void* Address, size_t Size = 4U);

	void WriteAOB(DWORD Address, std::string Bytes);
	void WriteByte(DWORD Address, unsigned char NewByte);
}