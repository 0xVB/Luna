#include "Lunacy/MemUtils.hpp"

void Mem::WriteAOB(DWORD Address, std::string Bytes)
{
	// Bytes format example: "8B C8 50 E8 42 F7 03 00 84 C0 58 74 69 90"
	unsigned char* aPtr = (unsigned char*)Address;

	// 1 Byte = 3 characters except for the last byte which does not have a space.
	unsigned int ByteCount = (Bytes.length() + 1) / 3;
	DWORD old, temp;

	VirtualProtect((LPVOID)Address, ByteCount, PAGE_EXECUTE_READWRITE, &old);

	for (int i = 0; i < ByteCount; i++)
	{
		// Grab 2 letters
		std::string sByte = Bytes.substr(i * 3, 2);

		unsigned int aByte;
		std::stringstream ss;
		ss << std::hex << sByte;
		ss >> aByte;

		*aPtr = (unsigned char)aByte;// Convert this to hex
		aPtr++;
	}

	VirtualProtect((LPVOID)Address, ByteCount, old, &temp);
}

void Mem::WriteByte(DWORD Address, unsigned char Level)
{
	DWORD old, temp;
	VirtualProtect((LPVOID)Address, 1, PAGE_EXECUTE_READWRITE, &old);
	*(unsigned char*)Address = Level;
	VirtualProtect((LPVOID)Address, 1, old, &temp);
}

void Mem::Unlock(const void* Address, size_t Size)
{
	DWORD OLD;
	VirtualProtect((LPVOID)Address, Size, PAGE_EXECUTE_READWRITE, &OLD);
}

void Mem::Unlock(void* Address, size_t Size)
{
	DWORD OLD;
	VirtualProtect((LPVOID)Address, Size, PAGE_EXECUTE_READWRITE, &OLD);
}

VOID Mem::Unlock (DWORD Address, size_t Size)
{
	DWORD OLD;
	VirtualProtect((LPVOID)Address, Size, PAGE_EXECUTE_READWRITE, &OLD);
}