#include "Lunacy/Image.h"
#include "Lunacy/CGeometry.h"
#define FUNCTION const unsigned int

FUNCTION IMAGE_CONSTRUCTOR = 0x588800;
FUNCTION IMAGE_COPY = 0x588850;

FUNCTION MEMIMG_CONSTRUCTOR = 0x5900F0;
FUNCTION MEMIMG_APP_CONST = 0x590170;
FUNCTION MEMIMG_COPY = 0x5901D0;

FUNCTION DDIMG_CONSTRUCTOR = 0x56B910;
FUNCTION DDINT_CONSTRUCTOR = 0x56B890;

using namespace Sexy;

#pragma warning(push)
#pragma warning(disable: 26495) // Disables warning C26495

Image::bColor::bColor(Color aCol)
{
	a = aCol.mAlpha;
	r = aCol.mRed;
	g = aCol.mGreen;
	b = aCol.mBlue;
}

Image::bColor::operator Sexy::Color() const
{
	return Color(r, g, b, a);
}

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

Image::bColor* MemoryImage::GetPixels()
{
	return (bColor*)GetBits();
}

MemoryImage* Image::GetHReflect()
{
	auto aImage = MemoryImage::New(mWidth, mHeight);
	auto aMat = Matrix3();
	auto aRect = IRect(0, 0, mWidth, mHeight);

	aMat.SetScale(-1, 1);
	aImage->BltMatrix(this, mWidth, 0, aMat, aRect, Color(255, 255, 255), 0, aRect, false);
	return aImage;
}

MemoryImage* Image::GetVReflect()
{
	auto aImage = MemoryImage::New(mWidth, mHeight);
	auto aMat = Matrix3();
	auto aRect = IRect(0, 0, mWidth, mHeight);

	aMat.SetScale(1, -1);
	aImage->BltMatrix(this, 0, mHeight, aMat, aRect, Color(255, 255, 255), 0, aRect, false);
	return aImage;
}

MemoryImage* Image::GetOReflect()
{
	auto aImage = MemoryImage::New(mWidth, mHeight);
	auto aMat = Matrix3();
	auto aRect = IRect(0, 0, mWidth, mHeight);

	aMat.SetScale(-1, -1);
	aImage->BltMatrix(this, mWidth, mHeight, aMat, aRect, Color(255, 255, 255), 0, aRect, false);
	return aImage;
}

MemoryImage* Image::GetRotated(float r, int w, int h)
{
	w = (w == -1) ? mWidth : w;
	h = (h == -1) ? mHeight : h;

	auto aImage = MemoryImage::New(w, h);
	auto aMat = Matrix3();
	auto aRect = IRect(0, 0, mWidth, mHeight);

	aMat.RotateByRadians(r);
	aImage->BltMatrix(this, 0, 0, aMat, aRect, Color(255, 255, 255), 0, aRect, false);
	return aImage;
}

MemoryImage* Image::GetScaled(int sx, int sy)
{
	auto aImage = MemoryImage::New(sx, sy);
	auto aRect = IRect(0, 0, mWidth, mHeight);
	aImage->StretchBlt(this, aRect, aRect, IRect(0, 0, sx, sy), Color(255, 255, 255), 0, false);
	return aImage;
}

MemoryImage* Image::GetCropped(IRect src)
{
	auto aImage = MemoryImage::New(src.mW, src.mH);
	aImage->StretchBlt(this, src, IRect(0, 0, src.mW, src.mH), IRect(0, 0, src.mW, src.mH), Color(255, 255, 255), 0, false);
	return aImage;
}

void MemoryImage::CopyImage(MemoryImage* Other, bool CommitBits)
{
	SetBits(Other->GetBits(), Other->mWidth, Other->mHeight, CommitBits);
}

MemoryImage* MemoryImage::Blend(MemoryImage* aMapImage, MemoryImage* aDestImage, float sAlpha, int X, int Y)
{
	if (!aDestImage)
		aDestImage = MemoryImage::New(mWidth, mHeight);

	auto aMap = aMapImage->GetPixels();
	auto aDest = aDestImage->GetPixels();
	auto aSource = (aDestImage == this) ? aDest : GetPixels();

	for (int aPixel = 0; aPixel < mSize; aPixel++)
	{
		auto aDestPixel = aDest + aPixel;
		Color aMapPixel = aMap[aPixel];
		Color aSourcePixel = aSource[aPixel];

		auto Alpha = sAlpha * aMapPixel.mAlpha / 255.0f;
		auto iAlpha = 1 - Alpha;
		aDestPixel->a = aSourcePixel.mAlpha;
		aDestPixel->r = aSourcePixel.mRed * iAlpha + aMapPixel.mRed * Alpha;
		aDestPixel->g = aSourcePixel.mGreen * iAlpha + aMapPixel.mGreen * Alpha;
		aDestPixel->b = aSourcePixel.mBlue * iAlpha + aMapPixel.mRed * Alpha;
	}

	aMapImage->CommitBits();
	aDestImage->CommitBits();
	if (aDestImage != this)
		CommitBits();

	return aDestImage;
}

void MemoryImage::BlendWith(MemoryImage* aMapImage, float Alpha, int X, int Y)
{
	Blend(aMapImage, this, Alpha, X, Y);
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

DDImage* DDImage::New(int W, int H)
{
	auto NewImage = (DDImage*) new char[sizeof(DDImage)];
	DDIMG_CONSTRUCT(NewImage);
	NewImage->Create(W, H);

	return NewImage;
}

__declspec(naked) MemoryImage* __stdcall MemoryImage::New(int, int)
{
	__asm
	{
		push ebx
		mov ecx, [esp + 0xC]
		mov ebx, [esp + 0x8]
		mov eax, 0x46F280
		call eax
		pop ebx
		ret 0x8
	}
}
#pragma warning(pop)