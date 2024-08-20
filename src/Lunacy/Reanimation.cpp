#include "Lunacy/Reanimation.h"
#include "Lunacy/Graphics.h"
#include "Lunacy/Image.h"

CONST DWORD CONSTRUCT = 0x471920;
__declspec(naked) void __stdcall Reanimation::CreateReanim(Reanimation*)
{
	__asm
	{
		pop eax// Ret
		pop edx// Reanim
		push eax
		jmp CONSTRUCT
	}
}

Reanimation::Reanimation()
{
	Reanimation::CreateReanim(this);
}

Reanimation::~Reanimation()
{
	Die();
}

CONST DWORD INITTYPE = 0x471A60;
__declspec(naked) void Reanimation::Initialize(float, float, ReanimationType)
{
	__asm
	{
		push edi
		push esi
		mov edi, ecx
		mov esi, [esp + 0x14]
		push [esp + 0x10]
		push [esp + 0x10]
		call INITTYPE
		pop esi
		pop edi
		ret 0xC
	}
}

CONST DWORD INITDEF = 0x471B00;
__declspec(naked) void Reanimation::Initialize(float, float, ReanimatorDefinition*)
{
	__asm
	{
		mov eax, [esp + 0xC]
		push [esp + 0x8]
		push [esp + 0x8]
		push ecx
		call INITDEF
		ret 0xC
	}
}

CONST DWORD UPDATE = 0x471BC0;
__declspec(naked) void Reanimation::Update()
{
	__asm
	{
		jmp UPDATE
	}
}

CONST DWORD DIE = 0x4733F0;
__declspec(naked) void Reanimation::Die()
{
	__asm
	{
		jmp DIE
	}
}

CONST DWORD DRAW = 0x472E40;
__declspec(naked) void Reanimation::Draw(Sexy::Graphics*, int)
{
	__asm
	{
		jmp DRAW
	}
}

CONST DWORD ATTANIM = 0x472F80;
__declspec(naked) void Reanimation::AttachToAnotherReanim(Reanimation*, const char*)
{
	__asm
	{
		push esi
		mov esi, ecx
		mov eax, [esp + 0x8]
		mov edx, [esp + 0xC]
		call ATTANIM
		pop esi
		ret 0x8
	}
}

CONST DWORD OVERRIDE = 0x473490;
__declspec(naked) void Reanimation::SetImageOverride(const char*, Sexy::Image*)
{
	__asm
	{
		pop edx// Ret
		pop eax// TrackName
		push edx
		jmp OVERRIDE
	}
}

CONST DWORD GETOVER = 0x473470;
__declspec(naked) Sexy::Image* Reanimation::GetImageOverride(const char*)
{
	__asm
	{
		pop edx// Ret
		pop eax// TrackName
		push edx
		jmp GETOVER
	}
}

CONST DWORD ATTPART = 0x473070;
__declspec(naked) AttachEffect* Reanimation::AttachParticleToTrack(const char*, ParticleSystem*, float, float)
{
	__asm
	{
		pop edx// Ret
		pop eax// TrackName
		push edx
		jmp ATTPART
	}
}

void Reanimation::SetTranslation(float X, float Y)
{
	mOverlayMatrix.SetTranslation(X, Y);
}

void Reanimation::TranslateBy(float X, float Y)
{
	mOverlayMatrix.TranslateBy(X, Y);
}

Sexy::FVector2 Reanimation::GetTranslation()
{
	return mOverlayMatrix.GetTranslation();
}

void Reanimation::SetScale(float X, float Y)
{
	mOverlayMatrix.SetScale(X, Y);
}

void Reanimation::ScaleBy(float X, float Y)
{
	mOverlayMatrix.ScaleBy(X, Y);
}

Sexy::FVector2 Reanimation::GetScale()
{
	return mOverlayMatrix.GetScale();
}

void Reanimation::SetSkew(float X, float Y)
{
	mOverlayMatrix.SetSkew(X, Y);
}

void Reanimation::SkewBy(float X, float Y)
{
	mOverlayMatrix.SkewBy(X, Y);
}

Sexy::FVector2 Reanimation::GetSkew()
{
	return mOverlayMatrix.GetSkew();
}

void Reanimation::RotateByDegrees(float Deg)
{
	mOverlayMatrix.RotateByDegrees(Deg);
}

void Reanimation::RotateByRadians(float Rad)
{
	mOverlayMatrix.RotateByRadians(Rad);
}

void Reanimation::SetRotationDegrees(float Deg)
{
	mOverlayMatrix.SetRotationDegrees(Deg);
}

void Reanimation::SetRotationRadians(float Rad)
{
	mOverlayMatrix.SetRotationRadians(Rad);
}

float Reanimation::GetRotationDegrees()
{
	return mOverlayMatrix.GetRotationDegrees();
}

float Reanimation::GetRotationRadians()
{
	return mOverlayMatrix.GetRotationRadians();
}

CONST DWORD DTRACK = 0x4723B0;
__declspec(naked) bool Reanimation::DrawTrack(Sexy::Graphics*, int, Sexy::TriangleGroup*)
{
	__asm
	{
		pop edx// Ret
		push ecx
		push edx
		jmp DTRACK
	}
}

Sexy::DDImage* Reanimation::ExtractFrame(Sexy::DDImage* Out, int RenderGroup)
{
	if (!Out)
		Out = Sexy::DDImage::New(200, 200);
	auto G = Sexy::Graphics::New(Out->mWidth, Out->mHeight);

	Sexy::TriangleGroup aTriangleGroup;
	for (int aTrackIndex = 0; aTrackIndex < mDefinition->mTrackCount; aTrackIndex++)
	{
		ReanimatorTrackInstance* aTrackInstance = &mTrackInstances[aTrackIndex];
		if (aTrackInstance->mRenderGroup == RenderGroup)
			bool aTrackDrawn = DrawTrack(G, aTrackIndex, &aTriangleGroup);
	}
	aTriangleGroup.DrawGroup(G);

	Out->Blt(G->mDestImage, 0, 0, Out->mSize.ToSize(), Sexy::Color(255, 255, 255), 0);
	Out->CommitBits();

	auto aDest = G->mDestImage;
	G->~Graphics();
	aDest->~Image();

	return Out;
}