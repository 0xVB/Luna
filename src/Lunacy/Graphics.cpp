#include "Lunacy/Graphics.h"
#include "Lunacy/Image.h"
#define FUNCTION const unsigned int

// Function Addresses
FUNCTION PUSHSTATE = 0x586B40;
FUNCTION POPSTATE = 0x586BD0;
FUNCTION CREATE = 0x586C30;

FUNCTION DRAWRECT = 0x586DE0;
FUNCTION FILLRECT = 0x586D50;
FUNCTION DRAWRECTP = 0x586EF0;
FUNCTION FILLRECTP = 0x586DC0;

FUNCTION DRAWSTRING = 0x587120;
FUNCTION GETWORDHEIGHT = 0x588700;
FUNCTION WRITEWORDWRAPPED = 0x588310;

FUNCTION DRAWIMAGE = 0x587150;
FUNCTION DRAWIMAGESCALED = 0x587520;
FUNCTION DRAWIMAGESOURCED = 0x587270;

FUNCTION DRAWIMAGECEL = 0x587E80;
FUNCTION DRAWTRIANGLES = 0x587710;

using Sexy::Graphics;

void __declspec(naked) Graphics::PushState()
{
	__asm
	{
		push ecx
		call PUSHSTATE
		ret
	}
}

void __declspec(naked) Graphics::PopState()
{
	__asm
	{
		push edi
		mov edi, ecx
		call POPSTATE
		pop edi
		ret
	}
}

__declspec(naked) Graphics* Graphics::Create()
{
	__asm
	{
		push ecx
		call CREATE
		ret
	}
}

void __declspec(naked) Graphics::DrawRect(int, int, int, int)
{
	__asm
	{
		mov eax, ecx
		jmp DRAWRECT
	}
}

void __declspec(naked) Graphics::FillRect(int, int, int, int)
{
	__asm
	{
		mov eax, ecx
		jmp FILLRECT
	}
}

void __declspec(naked) Graphics::DrawRect(const IRect&)
{
	__asm
	{
		push ecx
		mov eax, [esp + 0x8]
		call DRAWRECTP
		ret 4
	}
}

void __declspec(naked) Graphics::FillRect(const IRect&)
{
	__asm
	{
		push ecx
		mov eax, [esp + 0x8]
		call FILLRECTP
		ret 4
	}
}

void __declspec(naked) Graphics::DrawImage(Image*, int, int)
{
	__asm
	{
		push ebx

		mov eax, ecx
		mov ebx, [esp + 0x8]
		push [esp + 0x10]
		push [esp + 0x10]
		call DRAWIMAGE
		
		pop ebx
		ret 0xC
	}
}

void __declspec(naked) Graphics::DrawImage(Image*, int, int, const IRect&)
{
	__asm
	{
		mov eax, [esp + 0x10]
		push [esp + 0xC]
		push [esp + 0xC]
		push [esp + 0xC]
		call DRAWIMAGESOURCED
		ret 0x10
	}
}

void __declspec(naked) Graphics::DrawImage(Image*, int, int, int, int)
{
	__asm
	{
		push edi

		mov eax, ecx
		mov edi, [esp + 0x8]
		push [esp + 0x18]
		push [esp + 0x18]
		push [esp + 0x18]
		push [esp + 0x18]
		call DRAWIMAGESCALED

		ret 0x14
	}
}

void Graphics::DrawImage(Image* Img, int X, int Y, const IRect& Src, double Rotation, const IRect& Clip, Color* Col, int RotCenterX, int RotCenterY)
{
	// TODO: Implement this function. There is no default function for this.
	// We need to implement Images before we can implement this.
	mDestImage->BltRotated(Img, X, Y, Src, Clip, *Col, 1, Rotation, RotCenterX, RotCenterY);
}

void __declspec(naked) Graphics::DrawTriangles(Image*, const TriVertex&, int)
{
	__asm
	{
		mov eax, ecx
		push [esp + 0xC]
		push [esp + 0xC]
		push [esp + 0xC]
		ret 0xC
	}
}

void __declspec(naked) Graphics::DrawImageCel(Image*, int, int, int, int)
{
	__asm
	{
		push edi

		mov eax, ecx
		mov ecx, [esp + 0x8]
		mov edi, [esp + 0x18]
		push [esp + 0x14]
		push [esp + 0x14]
		push [esp + 0x14]
		push eax
		call DRAWIMAGECEL

		pop edi
		ret 0x14
	}
}

void __declspec(naked) Graphics::DrawString(const PopString&, int, int)
{
	__asm
	{
		mov eax, ecx
		jmp DRAWSTRING
	}
}

__declspec(naked) int Graphics::WriteWordWrapped(const PopString&, const IRect&, int, Alignment)
{
	__asm
	{
		push ebx
		mov ebx, [esp + 0x8]
		mov edx, ecx

		push [esp + 0x14]
		push [esp + 0x14]
		push [esp + 0x14]
		call WRITEWORDWRAPPED

		pop ebx
		ret 0x10
	}
}

__declspec(naked) int Graphics::GetWrappedWordHeight(const PopString&, int, int)
{
	__asm
	{
		push ebx
		mov ebx, [esp + 0x8]

		push [esp + 0x10]
		push [esp + 0xC]
		push ecx
		call GETWORDHEIGHT

		pop ebx
		ret 0xC
	}
}