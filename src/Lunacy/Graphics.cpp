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

FUNCTION DRAWIMAGECEL = 0x587E80;
FUNCTION DRAWTRIANGLES = 0x587710;

using Sexy::Graphics;

void Sexy::GraphicsState::CopyState(const GraphicsState* State)
{
	mDestImage = State->mDestImage;
	mTransX = State->mTransX;
	mTransY = State->mTransY;
	mClipRect = State->mClipRect;
	mFont = State->mFont;
	mColor = State->mColor;
	mDrawMode = State->mDrawMode;
	mColorizeImages = State->mColorizeImages;
	mFastStretch = State->mFastStretch;
	mWriteColoredString = State->mWriteColoredString;
	mLinearBlend = State->mLinearBlend;
	mScaleX = State->mScaleX;
	mScaleY = State->mScaleY;
	mScaleOrigX = State->mScaleOrigX;
	mScaleOrigY = State->mScaleOrigY;
	mIs3D = State->mIs3D;
}

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

void Graphics::DrawImage(Image* aImage, int X, int Y, const IRect& src)
{
	mDestImage->StretchBlt(aImage, IRect(X + mTransX, Y + mTransY, src.mW * mScaleX, src.mH * mScaleY), src, mClipRect, mColorizeImages ? mColor : Color(255, 255, 255), mDrawMode, mFastStretch);
}

void Graphics::DrawImage(Image* aImage, int X, int Y, int W, int H)
{
	mDestImage->StretchBlt(aImage, IRect(X + mTransX, Y + mTransY, W * mScaleX, H * mScaleY), aImage->mSize.ToSize(), mClipRect, mColorizeImages ? mColor : Color(255, 255, 255), mDrawMode, mFastStretch);
}

void Graphics::DrawImage(Image* Img, int X, int Y, const IRect& Src, double Rotation, const IRect& Clip, Color* Col, int RotCenterX, int RotCenterY)
{
	mDestImage->BltRotated(Img, X, Y, Src, Clip, *Col, 1, Rotation, RotCenterX, RotCenterY);
}

void Graphics::DrawImage(Sexy::Image* aImage, int X, int Y)
{
	DrawImage(aImage, X, Y, aImage->mWidth, aImage->mHeight);
}

CONST DWORD CONSTG = 0x586A30;
__declspec(naked) void __stdcall GCONST(Graphics*, Sexy::Image*)
{
	__asm
	{
		pop edx// Ret
		pop eax// G
		pop ecx// Image
		push eax
		push edx
		jmp CONSTG
	}
}
Graphics* Graphics::New(Image* aDestImage)
{
	Graphics* G = new Graphics();
	GCONST(G, aDestImage);
	return G;
}
Graphics* Graphics::New(int w, int h)
{
	auto aDestImage = DDImage::New(w, h);
	Graphics* G = new Graphics();
	GCONST(G, aDestImage);
	return G;
}