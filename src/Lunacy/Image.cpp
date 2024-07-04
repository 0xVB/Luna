#include "Lunacy/Image.h"
#define FUNCTION const unsigned int

FUNCTION IMAGE_CONSTRUCTOR = 0x588800;
FUNCTION IMAGE_COPY = 0x588850;

FUNCTION MEMIMG_CONSTRUCTOR = 0x5900F0;
FUNCTION MEMIMG_APP_CONST = 0x590170;
FUNCTION MEMIMG_COPY = 0x5901D0;

FUNCTION DDIMG_CONSTRUCTOR = 0x56B890;
FUNCTION DDINT_CONSTRUCTOR = 0x56B890;

using namespace Sexy;

#pragma warning(push)
#pragma warning(disable: 26495) // Disables warning C26495

__declspec(naked) void __stdcall IMAGE_CONSTRUCT(Image*)
{
	__asm
	{
		mov eax, [esp + 0x4]
		call IMAGE_CONSTRUCTOR
		ret 0x4
	}
}

__declspec(naked) void __stdcall COPY_IMAGE(Image*, const Image&)
{
	__asm
	{
		mov ecx, [esp + 0x4]
		mov eax, [esp + 0x8]

		push edi
		push ecx
		mov edi, eax
		call IMAGE_COPY

		pop edi
		ret 0x8
	}
}

Image::Image()
{
	IMAGE_CONSTRUCT(this);
}

Image::Image(const Image& Other)
{
	COPY_IMAGE(this, Other);
}

__declspec(naked) void __stdcall MEMIMG_CONSTRUCT(MemoryImage*)
{
	__asm
	{
		jmp MEMIMG_CONSTRUCTOR
	}
}

__declspec(naked) void __stdcall COPY_MEMIMG(MemoryImage*, const MemoryImage&)
{
	__asm
	{
		mov ecx, [esp + 0x4]
		mov eax, [esp + 0x8]

		push ebx
		push ecx
		mov ebx, eax
		call MEMIMG_COPY
		pop ebx
		ret 0x8
	}
}

__declspec(naked) void __stdcall MEMIMGAPP(Image*, SexyAppBase*)
{
	__asm
	{
		jmp MEMIMG_APP_CONST
	}
}

MemoryImage::MemoryImage()
{
	MEMIMG_CONSTRUCT(this);
}

MemoryImage::MemoryImage(const MemoryImage& Other)
{
	COPY_MEMIMG(this, Other);
}

MemoryImage::MemoryImage(SexyAppBase* App)
{
	MEMIMGAPP(this, App);
}

__declspec(naked) void __stdcall DDIMG_CONSTRUCT(DDImage*)
{
	__asm
	{
		jmp DDIMG_CONSTRUCTOR
	}
}

__declspec(naked) void __stdcall DDINT_CONSTRUCT(DDImage*, DDInterface*)
{
	__asm
	{
		push edi
		push [esp + 0x8]
		mov edi, [esp + 0x10]
		call DDINT_CONSTRUCTOR
		pop edi
		ret 0x8
	}
}

DDImage::DDImage()
{
	DDIMG_CONSTRUCT(this);
}

DDImage::DDImage(DDInterface* Interface)
{
	DDINT_CONSTRUCT(this, Interface);
}

#pragma warning(pop)