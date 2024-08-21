#include "Lunacy/Attachment.h"
#include "Lunacy/DataArray.h"

AttachmentID Attachment::GetID()
{
	return *(AttachmentID*)((DWORD)this + sizeof(Attachment));
}

Attachment::operator AttachmentID()
{
	return GetID();
}

__declspec(naked) void Attachment::Update()
{
	__asm
	{
		mov eax, 0x404490
		jmp eax
	}
}

__declspec(naked) void Attachment::SetPosition(const Sexy::FVector2&)
{
	__asm
	{
		mov eax, 0x404610
		jmp eax
	}
}

__declspec(naked) void Attachment::OverrideColor(const Sexy::Color&)
{
	__asm
	{
		mov eax, 0x404780
		jmp eax
	}
}

__declspec(naked) void Attachment::PropogateColor(const Sexy::Color&, bool, const Sexy::Color&, bool, const Sexy::Color&)
{
	__asm
	{
		mov eax, 0x404890
		jmp eax
	}
}

__declspec(naked) void Attachment::OverrideScale(float)
{
	__asm
	{
		mov eax, 0x404A40
		jmp eax
	}
}

__declspec(naked) void Attachment::CrossFade()
{
	__asm
	{
		push ebx
		mov ebx, ecx
		mov ecx, 0x404B20
		call ecx
		pop ebx
		ret
	}
}

__declspec(naked) void Attachment::SetMatrix(const Sexy::Matrix3&)
{
	__asm
	{
		mov eax, 0x404B80
		jmp eax
	}
}

__declspec(naked) void Attachment::Draw(Sexy::Graphics*, bool)
{
	__asm
	{
		mov eax, 0x404D10
		jmp eax
	}
}

__declspec(naked) void Attachment::Detach()
{
	__asm
	{
		mov eax, 0x404E80
		jmp eax
	}
}

__declspec(naked) void Attachment::Die()
{
	__asm
	{
		mov eax, 0x404FC0
		jmp eax
	}
}