#include "Lunacy/Buffer.h"
using namespace Sexy;

void Buffer::WriteLongString(const PopString& aString)
{
	WriteLong(aString.length());
	for (int i = 0; i < aString.length(); i++)
		WriteByte(aString[i]);
}

PopString Buffer::ReadLongString()
{
	auto oldReadBitPos = mReadBitPos;
	if (ByteLeftToRead() <= 4)
		return "";

	PopString aString;
	int aLen = ReadLong();

	if (ByteLeftToRead() < aLen)
	{
		mReadBitPos = oldReadBitPos;
		return "";
	}

	for (int i = 0; i < aLen; i++)
		aString += (char)ReadByte();

	return aString;
}

__declspec(naked) PopWString Buffer::UTF8ToWideString()
{
	__asm
	{
		push edi

		mov edi, [esp + 0x8]
		mov eax, 0x5D60F0
		call eax

		pop edi
		ret 0x4
	}
}

__declspec(naked) void Buffer::SeekFront()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x5D61E0
		jmp ecx
	}
}

__declspec(naked) void Buffer::Clear()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x5D61F0
		jmp ecx
	}
}

__declspec(naked) void Buffer::WriteByte(unsigned char)
{
	__asm
	{
		pop eax// Ret
		push ecx
		push eax
		mov eax, 0x5D6240
		jmp eax
	}
}

__declspec(naked) void Buffer::WriteNumBits(int, int)
{
	__asm
	{
		push esi

		mov esi, ecx
		push [esp + 0xC]
		push [esp + 0xC]
		mov ecx, 0x5D62E0
		call ecx

		pop esi
		ret 0x8
	}
}

__declspec(naked) void Buffer::WriteBool(bool)
{
	__asm
	{
		mov eax, 0x5D63E0
		jmp eax
	}
}

__declspec(naked) void Buffer::WriteShort(short)
{
	__asm
	{
		push edi

		mov eax, [esp + 0x8]
		mov edi, ecx
		mov ecx, 0x5D6400
		call ecx

		pop edi
		ret 0x4
	}
}

__declspec(naked) void Buffer::WriteLong(long)
{
	__asm
	{
		push edi

		mov eax, [esp + 0x8]
		mov edi, ecx
		mov ecx, 0x5D6420
		call ecx

		pop edi
		ret 0x4
	}
}

__declspec(naked) void Buffer::WriteString(const PopString&)
{
	__asm
	{
		push ebx

		mov ebx, [esp + 0x8]
		mov eax, ecx
		mov ecx, 0x5D6450
		call ecx

		pop ebx
		ret 0x4
	}
}

__declspec(naked) void Buffer::WriteLine(const PopString&)
{
	__asm
	{
		pop edx// ret
		pop eax// str

		push ecx// this
		mov ecx, eax
		push edx
		mov eax, 0x5D64A0
		jmp eax
	}
}

__declspec(naked) void Buffer::WriteBytes(const unsigned char*, int)
{
	__asm
	{
		push edi
		push ebx

		mov ebx, [esp + 0x0C]
		mov edi, [esp + 0x10]
		push ecx
		mov ecx, 0x5D6530
		call ecx

		pop ebx
		pop edi
		ret 0x8
	}
}

__declspec(naked) void Buffer::SetData(unsigned char*, int)
{
	__asm
	{
		pop eax
		push ecx
		push eax
		mov eax, 0x5D6560
		jmp eax
	}
}

__declspec(naked) unsigned char Buffer::ReadByte()
{
	__asm
	{
		push esi

		mov esi, ecx
		mov ecx, 0x5D6600
		call ecx

		pop esi
		ret
	}
}

__declspec(naked) int Buffer::ReadNumBits(int, bool)
{
	__asm
	{
		push esi

		mov esi, ecx
		push [esp + 0x8]
		push [esp + 0x8]
		mov ecx, 0x5D66E0
		call ecx

		pop esi
		ret 0x8
	}
}

__declspec(naked) bool Buffer::ReadBool()
{
	__asm
	{
		push esi

		mov esi, ecx
		mov ecx, 0x5D67C0
		call ecx

		pop esi
		ret
	}
}

__declspec(naked) short Buffer::ReadShort()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x5D67D0
		jmp ecx
	}
}

__declspec(naked) long Buffer::ReadLong()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x5D6800
		jmp ecx
	}
}

__declspec(naked) PopString Buffer::ReadString()
{
	__asm
	{
		push edi

		mov edi, [esp + 0x8]
		mov eax, 0x5D6840
		call eax

		pop edi
		ret 0x4
	}
}

__declspec(naked) PopString Buffer::ReadLine()
{
	__asm
	{
		push edi

		mov edi, [esp + 0x8]
		mov eax, 0x5D68D0
		call eax

		pop edi
		ret 0x4
	}
}

__declspec(naked) void Buffer::ReadBytes(unsigned char*, int)
{
	__asm
	{
		push ebx

		mov eax, ecx
		mov ebx, [esp + 0x0C]
		push [esp + 0x08]
		mov ecx, 0x5D6960
		call ecx

		pop ebx
		ret 0x8
	}
}

__declspec(naked) const unsigned char* Buffer::GetDataPtr()
{
	__asm
	{
		push esi

		mov esi, ecx
		mov ecx, 0x5D6990
		call ecx

		pop esi
		ret
	}
}

__declspec(naked) int Buffer::GetDataLen()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x5D69C0
		jmp ecx
	}
}

__declspec(naked) bool Buffer::AtEnd()
{
	__asm
	{
		mov eax, ecx
		mov ecx, 0x5D69D0
		jmp ecx
	}
}