#include "Luna/Hook/LunaHook.hpp"

LunaHookThread::Parameter::Parameter(Register32 Register)
{
	mStackOffset = 0;
	isRegister = true;
	mRegister = Register;
}

LunaHookThread::Parameter::Parameter(unsigned char StackOffset)
{
	mStackOffset = StackOffset;
}

bool LunaHookThread::Parameter::IsRegisterParam()
{
	return isRegister;
}

bool LunaHookThread::Parameter::IsStackParam()
{
	return !isRegister;
}

LunaHookThread::FunctionSignature::FunctionSignature(DWORD Address, bool Returns)
{
	VirtualProtect((LPVOID)Address, 32, PAGE_EXECUTE_READWRITE, &mOldProt);

	mAddress = Address;
	hasReturn = Returns;
	memset(&mParameters, 0, sizeof(mParameters));
	mParameterCount = 0;

	mOriginalCodeSize = 0;
	while (mOriginalCodeSize < 5)
	{
		usize iSize = getInstructionSize((unsigned char*)Address);
		mOriginalCodeSize += iSize;
		Address += iSize;
	}

	memcpy((void*)mAddress, mOriginalCode, mOriginalCodeSize);
}

void LunaHookThread::FunctionSignature::AddParameter(Register32 Register)
{
	mParameters[mParameterCount] = Parameter(Register);
	mParameterCount++;
}

void LunaHookThread::FunctionSignature::AddParameter(unsigned char StackOffset)
{
	mParameters[mParameterCount] = Parameter(StackOffset);
	mParameterCount++;
}

u8 LunaHookThread::Parameter::AddToBuffer(unsigned char* BufferStart, unsigned short StackOffset)
{
	if (IsRegisterParam())
	{
		switch (mRegister)
		{
		case EAX:
			*BufferStart = 0x50;
			return 1;
		case ECX:
			*BufferStart = 0x51;
			return 1;
		case EDX:
			*BufferStart = 0x52;
			return 1;
		case EBX:
			*BufferStart = 0x53;
			return 1;
		case ESP:
			*BufferStart = 0x54;
			return 1;
		case EBP:
			*BufferStart = 0x55;
			return 1;
		case ESI:
			*BufferStart = 0x56;
			return 1;
		case EDI:
			*BufferStart = 0x57;
			return 1;
		}
	}

	*BufferStart = 0xFF;
	BufferStart++;

	*BufferStart = 0x74;
	BufferStart++;

	*BufferStart = 0x24;
	BufferStart++;

	*BufferStart = mStackOffset + StackOffset;
	return 4;
}

void __declspec(naked) LunaHookThread::SaveRegisters(DWORD, DWORD, DWORD)
{
	__asm
	{
		// eax
		mov eax, [esp + 0x04]
		mov [ecx + 0x08], eax

		// ecx
		mov eax, [esp + 0x08]
		mov [ecx + 0x0C], eax

		// edx
		mov eax, [esp + 0x0C]
		mov [ecx + 0x10], eax
		
		// Other Registers
		mov [ecx + 0x14], ebx
		mov [ecx + 0x18], esp
		mov [ecx + 0x1C], ebp
		mov [ecx + 0x20], esi
		mov [ecx + 0x24], edi

		// Restore Scratch
		mov eax, [esp + 0x4]
		mov ecx, [esp + 0x8]
		mov edx, [esp + 0xC]

		ret 0x0C
	}
}

void __declspec(naked) LunaHookThread::LoadRegistersPreserveEAX()
{
	__asm
	{
		mov edx, [ecx + 0x14]// _edx
		mov ebx, [ecx + 0x18]// _ebx
		mov edi, [ecx + 0x28]// _edi
		mov ecx, [ecx + 0x10]// _ecx
		ret
	}
}

void __declspec(naked) LunaHookThread::LoadRegisters()
{
	__asm
	{
		mov eax, [ecx + 0x0C]// _eax
		mov edx, [ecx + 0x14]// _edx
		mov ebx, [ecx + 0x18]// _ebx
		mov edi, [ecx + 0x28]// _edi
		mov ecx, [ecx + 0x10]// _ecx
		ret
	}
}

void LunaHookThread::SetRegister(Register32 Reg, DWORD Value)
{
	_isChanged = true;
	_mRegisters[Reg] = Value;
}

void LunaHookThread::SetReturnAddress(DWORD Address)
{
	_isChanged = true;
	_mReturnAddress = Address;
}

void LunaHookThread::FunctionSignature::Hook(void* DetourTo)
{
	DWORD Detour = (DWORD)DetourTo;
	unsigned char Middleman[512];
	unsigned short BytesUsed = 3;
	unsigned short StackOff = 0xC;

	// Push the parameters to SaveRegisters
	Middleman[2] = 0x52;// push edx
	Middleman[1] = 0x51;// push ecx
	Middleman[0] = 0x50;// push eax

	// Absolute call to SaveRegisters
	Middleman[BytesUsed++] = 0xB8; // mov eax, _parentThread + _SaveRegisters
	*(DWORD*)(Middleman + BytesUsed) = (DWORD)_parentThread + _SaveRegisters;
	BytesUsed += 4;

	Middleman[BytesUsed++] = 0xFF; // call eax
	Middleman[BytesUsed++] = 0xD0;

	int CurrParamIndex = mParameterCount - 1;
	while (CurrParamIndex >= 0)
	{
		auto CurrParam = mParameters[CurrParamIndex];
		BytesUsed += CurrParam.AddToBuffer(Middleman + BytesUsed, StackOff);
		StackOff += 0x4;

		CurrParamIndex--;
	}

	// Absolute call to the detour function
	Middleman[BytesUsed++] = 0xB8; // mov eax, Detour
	*(DWORD*)(Middleman + BytesUsed) = Detour;
	BytesUsed += 4;

	Middleman[BytesUsed++] = 0xFF; // call eax
	Middleman[BytesUsed++] = 0xD0;

}