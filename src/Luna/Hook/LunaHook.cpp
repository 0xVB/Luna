#include "Luna/Hook/LunaHook.hpp"

#pragma region Internal
class LunaHookThread::CodeBuffer
{
	union
	{
		void* vPtr;
		unsigned char* cPtr;
		unsigned short* sPtr;
		unsigned int* iPtr;
	};

public:

	DWORD oPtr;// Contains the original buffer pointer

	CodeBuffer(size_t CodeSize)
	{
		vPtr = operator new(CodeSize);
		oPtr = (DWORD)vPtr;
	}

	void Copy(unsigned char* From, size_t Size)
	{
		memcpy(vPtr, From, Size);
		cPtr += Size;
	}

	void EncodePush(DWORD Value)
	{
		*cPtr = 0x68;// push opcode
		cPtr++;

		*iPtr = Value;// Number
		iPtr++;
	}

	void EncodeByte(char Value)
	{
		*cPtr = Value;
		cPtr++;
	}

	void EncodePop(LunaHookThread::Register32 Reg)
	{
		*cPtr = (0x58 + Reg);
		cPtr++;
	}

	void EncodePush(LunaHookThread::Register32 Reg)
	{
		*cPtr = (0x50 + Reg);
		cPtr++;
	}

	void EncodeStackPush(DWORD StackOffset)
	{
		*cPtr = 0xFF;
		cPtr++;

		*cPtr = 0x74;
		cPtr++;

		*cPtr = 0x24;
		cPtr++;

		*cPtr = StackOffset;
		cPtr++;
	}

	void EncodeRet()
	{
		*cPtr = 0xC3;
		cPtr++;
	}

	void EncodeRet(unsigned short pop)
	{
		*cPtr = 0xC2;
		cPtr++;

		*sPtr = pop;
		sPtr++;
	}

	void EncodeJE(char JumpAmount)
	{
		*cPtr = 0x74;
		cPtr++;

		*cPtr = JumpAmount;
		cPtr++;
	}
};
#pragma endregion

#pragma region Simple stuff
LunaHookThread::LunaHookThread()
{
	for (int i = 0; i < NUM_REGISTERS; i++)
		_registers[i] = 0;
	_skip = false;
}

LunaHookThread* LunaHookThread::New()
{
	return new LunaHookThread();
}

LunaHookThread::FunctionSignature* LunaHookThread::NewFunction(DWORD Address)
{
	return FunctionSignature::New(this, Address);
}

void LunaHookThread::SetRegister(Register32 Reg, DWORD Value)
{
	_registers[Reg] = Value;
}

DWORD LunaHookThread::GetRegister(Register32 Reg)
{
	return _registers[Reg];
}

// Parameter
LunaHookThread::Parameter::Parameter(Register32 Reg)
{
	isRegister = true;
	mRegister = Reg;
}

LunaHookThread::Parameter::Parameter(u8 Reg)
{
	isRegister = false;
	mStackOffset = Reg;
}

unsigned char LunaHookThread::Parameter::AddToBuffer(unsigned char* Buffer, unsigned short Offset)
{
	if (isRegister)
	{
		*Buffer = (0x50 + mRegister);
		return 1;
	}

	*Buffer = 0xFF;
	Buffer++;

	*Buffer = 0x74;
	Buffer++;

	*Buffer = 0x24;
	Buffer++;

	*Buffer = mStackOffset + Offset;
	return 4;
}

// Function Signature
LunaHookThread::FunctionSignature::FunctionSignature()
{
	_parentThread = nullptr;

	_addr = 0;
	_oldProt = 0;
	_paramCount = 0;
	_origCodeSize = 0;

	_paramCodeSize = 0;
	_stackSize = 0;

	memset(_parameters, 0, sizeof(_parameters));
	memset(_origCode, 0, sizeof(_origCode));
}

void LunaHookThread::FunctionSignature::AddParameter(Register32 Reg)
{
	_parameters[_paramCount] = Parameter(Reg);
	_paramCount++;
}

void LunaHookThread::FunctionSignature::AddParameter(u8 Offset)
{
	_parameters[_paramCount] = Parameter(Offset);
	_paramCount++;
}

void LunaHookThread::FunctionSignature::AddParameter()
{
	GetStackSize();
	AddParameter(_stackSize + 4U);
}

void LunaHookThread::FunctionSignature::AddStackParameters(u8 Count)
{
	for (int i = 0; i < Count; i++)
		AddParameter();
}

LunaHookThread::FunctionSignature* LunaHookThread::FunctionSignature::New(LunaHookThread* Parent, DWORD Address)
{
	auto Signature = new FunctionSignature();
	Signature->_parentThread = Parent;
	Signature->_addr = Address;
	return Signature;
}

void LunaHookThread::SetSkip(bool DoSkip)
{
	_skip = DoSkip >= 1;
}

size_t LunaHookThread::Parameter::GetCodeSize()
{
	if (isRegister) return 1;
	return 4;
}

void LunaHookThread::FunctionSignature::GetParamCodeSize()
{
	_paramCodeSize = 0;
	for (int i = 0; i < _paramCount; i++)
		_paramCodeSize += _parameters[i].GetCodeSize();
}

void LunaHookThread::FunctionSignature::GetStackSize()
{
	_stackSize = 0;
	for (int i = 0; i < _paramCount; i++)
		_stackSize += _parameters[i].isStackParam() * 4;
}

void LunaHookThread::Parameter::Encode(CodeBuffer* Buffer, char StackOffset)
{
	if (isRegister)
		Buffer->EncodePush(mRegister);
	else
		Buffer->EncodeStackPush(mStackOffset + StackOffset);
}

char LunaHookThread::Parameter::EncodeIn(CodeBuffer* Buffer, char StackOffset)
{
	if (isRegister)
	{
		Buffer->EncodeByte(0x8B);
		Buffer->EncodeByte(0x44 + 0x8 * mRegister);
		Buffer->EncodeByte(0x24);
		Buffer->EncodeByte(StackOffset);
		return 0x00;
	}
	else
	{
		Buffer->EncodeByte(0xFF);
		Buffer->EncodeByte(0x74);
		Buffer->EncodeByte(0x24);
		Buffer->EncodeByte(StackOffset);
		return 0x04;
	}
}

void LunaHookThread::SetReturn(DWORD Value)
{
	_registers[EAX] = Value;
}
#pragma endregion

#pragma region Declarations
#define _vtoffset  0U

#define _rtable _vtoffset + 0x00U
#define _eax _rtable + 0x00U
#define _ecx _rtable + 0x04U
#define _edx _rtable + 0x08U
#define _ebx _rtable + 0x0CU

#define _esp _rtable + 0x10U
#define _ebp _rtable + 0x14U
#define _esi _rtable + 0x18U
#define _edi _rtable + 0x1CU
#define _rtable_end _edi

#define _skipad _rtable_end + 0x04U
#pragma endregion


// Complex stuff
__declspec(naked) void LunaHookThread::DetourHeader(LunaHookThread*)
{
	__asm
	{
		push eax// +08
		push ecx// +0C
		push edx// +10

		// edx: [esp + 0x00]
		// ecx: [esp + 0x04]
		// eax: [esp + 0x08]
		// ret: [esp + 0x0C]
		// self: [esp + 0x10]
		mov ecx, [esp + 0x10]// this*
		
		mov [ecx + _eax], eax// 1
		mov [ecx + _edx], edx// 2
		mov [ecx + _ebx], ebx// 3
		mov [ecx + _ebp], ebp// 4
		mov [ecx + _esi], esi// 5
		mov [ecx + _edi], edi// 6
		// ecx & esp left

		mov eax, [esp + 0x04]
		mov [ecx + _ecx], eax// ecx saved

		// params		:		+04
		// ret addr		:		+04
		// reg backup	:		+0C
		// total		:		+14
		mov eax, esp
		add eax, 0x14
		mov [ecx + _esp], eax// esp saved

		xor al, al
		mov byte ptr [ecx + _skipad], al// Restore _skip to false

		// Restore registers
		pop edx
		pop ecx
		pop eax
		ret 0x4// Return and pop this*
	}
}

__declspec(naked) void LunaHookThread::DetourFooter(LunaHookThread*)
{
	__asm
	{
		mov ecx, [esp + 0x04]// this*
		push [ecx + _ecx]
		push [ecx + _eax]

		mov al, byte ptr [ecx + _skipad]
		cmp al, 00

		mov edx, [ecx + _edx]
		mov ebx, [ecx + _ebx]
		mov ebp, [ecx + _ebp]
		mov esi, [ecx + _esi]
		mov edi, [ecx + _edi]

		pop eax
		pop ecx
		ret 0x4// Return and pop this*
	}
}

size_t GetHookSize(DWORD Address)
{
	size_t TotalSize = 0;
	while (TotalSize < 5)
	{
		size_t iSize = getInstructionSize((const u8*)Address);
		TotalSize += iSize;
		Address += iSize;
	}

	return TotalSize;
}

void LunaHookThread::FunctionSignature::Finalize(void* DetourTo)
{
	/* Base Function:
	* push parent														0x0005	(oPtr + 0x0000)
	* push L0 (return address)											0x000A	(oPtr + 0x0005)
	* push DetourHeader													0x000F	(oPtr + 0x000A)
	* ret (absolute call to DetourHeader)								0x0010	(oPtr + 0x000F)
	* 
	* L0:
	* [push all params]													0x0010	(oPtr + 0x0010) (L0)
	* push L1 (return address)											0x0015	(oPtr + 0x0010 + _paramCodeSize)
	* push DetourTo														0x001A	(oPtr + 0x0015 + _paramCodeSize)
	* ret (absolute call to DetourTo)									0x001B	(oPtr + 0x001A + _paramCodeSize)
	* 
	* L1:
	* push parent														0x0020	(oPtr + 0x001B + _paramCodeSize) (L1)
	* push CHECK														0x0025	(oPtr + 0x0020 + _paramCodeSize)
	* push DetourFooter													0x002A	(oPtr + 0x0025 + _paramCodeSize)
	* ret (absolute call to DetourFooter)								0x002B	(oPtr + 0x002A + _paramCodeSize)
	* 
	* CHECK:
	* je L2 (If _skip == false then go to original code instantly)		0x002D	(oPtr + 0x002B + _paramCodeSize) (CHECK)
	* ret [amount of stack params] (Otherwise, go abort func and ret)	0x002E	(oPtr + 0x002D + _paramCodeSize)
	* 
	* L2:
	* [original code]													0x002E	(oPtr + 0x002E + _paramCodeSize) (L2)
	* push original function retpoint									0x0033	(oPtr + 0x002E + _paramCodeSize + _origCodeSize)
	* ret																0x0034	(oPtr + 0x0033 + _paramCodeSize + _origCodeSize)
	*																	(END)	(oPtr + 0x0034 + _paramCodeSize + _origCodeSize)
	*/
	// Base function size: 0x34 Bytes
	// Total function size: Base + Param Code Size + Original Code Size
	CONST DWORD BASE_FUNC_SIZE = 0x34;
	// Unlock bytes near hook 
	VirtualProtect((LPVOID)_addr, 0xFF, PAGE_EXECUTE_READWRITE, &_oldProt);
	// Store size of code that needs to be saved
	_origCodeSize = GetHookSize(_addr);
	// Backup original code
	memcpy(_origCode, (const void*)_addr, _origCodeSize);

	// Calculate bytes required for param pushing and total stack size for this function's params
	GetParamCodeSize();
	GetStackSize();

	// Total bytes that need to be allocated to instantiate the middleman function
	size_t TotalFunctionSize = BASE_FUNC_SIZE + _origCodeSize + _paramCodeSize;
	CodeBuffer Middleman = CodeBuffer(TotalFunctionSize);

	// Start
	Middleman.EncodePush((DWORD)_parentThread);
	Middleman.EncodePush(Middleman.oPtr + 0x0010);
	Middleman.EncodePush((DWORD)DetourHeader);
	Middleman.EncodeRet();

	// L0: Push all params
	int cParam = _paramCount - 1;
	size_t StackOffset = 0;
	while (cParam >= 0)
	{
		auto aParam = _parameters[cParam];
		aParam.Encode(&Middleman, StackOffset);
		StackOffset += 0x4;
		cParam--;
	}
	// Call DetourTo (the function being detoured to)
	Middleman.EncodePush(Middleman.oPtr + 0x001B + _paramCodeSize);
	Middleman.EncodePush((DWORD)DetourTo);
	Middleman.EncodeRet();

	// L1: Call DetourFooter, restore registers & perform the cmp _skip, 00
	Middleman.EncodePush((DWORD)_parentThread);
	Middleman.EncodePush(Middleman.oPtr + 0x002B + _paramCodeSize);
	Middleman.EncodePush((DWORD)DetourFooter);
	Middleman.EncodeRet();

	// CHECK: Check if should skip vanilla code or not
	Middleman.EncodeJE(3);// Skip the ret [Param Count]
	Middleman.EncodeRet(_stackSize);// Pop _stackSize bytes off stack and return

	// L2: Original function code & handle returning
	Middleman.Copy(_origCode, _origCodeSize);// Copy original code & offset buffer ptr by _origCodeSize
	Middleman.EncodePush(_addr + _origCodeSize);// Push address to return to to resume vanilla code after hook
	Middleman.EncodeRet();// Return to original code & abort hook
	// END
	
	// Make function jump to destination
	DWORD rel32o = Middleman.oPtr - _addr - 5;// Relative offset
	*(BYTE*)_addr = 0xE9;// Set to jmp
	*(DWORD*)(_addr + 1) = rel32o;// Set relative offset
	
	for (DWORD cByte = _addr + 5; cByte < _addr + _origCodeSize; cByte++)
		*(BYTE*)cByte = 0x90;// NOP

	// Restore mem access
	VirtualProtect((LPVOID)_addr, 0xFF, _oldProt, &_oldProt);

	// Free signature memory after hook
	delete this;
}

LunaHookThread::LunaWrapper LunaHookThread::FunctionSignature::AllocateWrapper()
{
	/* Base Wrapper:
	* push non-volatile registers (ebx, ebp, esi, edi)                // Preserving non-volatile registers (0x04)
	*
	* mov & push params in correct order                              // Moving and pushing function parameters (_paramCodeSize)
	* push L0                                                         // Pushing return address for cleanup (L0) (0x05)
	*
	* original hook code                                               // Executing the code that was overwritten (_origCodeSize)
	*
	* push funcaddr + hook code size                                   // Pushing the address to return to after the original function call (0x05)
	* ret                                                              // Returning from the function (0x01)
	*
	* L0:
	* pop non-volatile registers                                       // Restoring the saved registers (0x04)
	* ret                                                              // Returning from the wrapper (0x01)
	*/

	// Unlock bytes near hook for execution
	VirtualProtect((LPVOID)_addr, 0xFF, PAGE_EXECUTE_READWRITE, &_oldProt);

	// Store size of the original code that was overwritten
	_origCodeSize = GetHookSize(_addr);

	// Backup the original code
	memcpy(_origCode, (const void*)_addr, _origCodeSize);

	// Calculate _paramCodeSize
	_paramCodeSize = _paramCount * 4;

	// Calculate the total size of the generated wrapper
	size_t WrapperSize = 0x0F + _paramCodeSize + _origCodeSize; // Base size + params + original overwritten code
	CodeBuffer Wrapper(WrapperSize);

	// 1. Push non-volatile registers (ebx, ebp, esi, edi)
	Wrapper.EncodePush(EBX);
	Wrapper.EncodePush(EBP);
	Wrapper.EncodePush(ESI);
	Wrapper.EncodePush(EDI);

	// 2. Push all parameters in reverse order (stack parameters first, then registers)
	int cParam = _paramCount - 1;
	size_t StackOffset = 0x14;// non-volatile registers padded the stack by 0x10 bytes. Return address +0x04 bytes.
	while (cParam >= 0)
	{
		// Param = StackOffset + 0x4 * ParamIndex
		size_t ParamLocation = StackOffset + (0x04 * cParam);// Location of the parameter on the stack
		auto aParam = _parameters[cParam];
		StackOffset += aParam.EncodeIn(&Wrapper, ParamLocation);
		cParam--;

		// aParam._isRegister:
		// Encodes a mov reg, [esp + ParamLocation] and returns 0
		// else:
		// Encodes a push [esp + ParamLocation] and returns 4
	}

	// 3. Push L0 (return address for cleanup after function call)
	Wrapper.EncodePush(Wrapper.oPtr + 0x0F + _paramCodeSize + _origCodeSize);

	// 4. Copy the original code (that was overwritten by the hook) into the wrapper
	Wrapper.Copy(_origCode, _origCodeSize);

	// 5. Push the original function return address (where the original function continues)
	Wrapper.EncodePush(_addr + _origCodeSize);
	Wrapper.EncodeRet();  // Return to the original function

	// L0 (Cleanup section):
	// 6. Restore non-volatile registers (pop them in reverse order)
	Wrapper.EncodePop(EDI);
	Wrapper.EncodePop(ESI);
	Wrapper.EncodePop(EBP);
	Wrapper.EncodePop(EBX);
	Wrapper.EncodeRet();

	// Restore memory protection for the original code
	VirtualProtect((LPVOID)_addr, 0xFF, _oldProt, &_oldProt);

	// Return the wrapper function (cast it as a LunaWrapper function pointer)
	return (LunaWrapper)Wrapper.oPtr;
}

LunaHookThread::LunaWrapper LunaHookThread::FunctionSignature::FinalizeAndWrap(void* DetourTo)
{
	auto Wrapper = AllocateWrapper();
	Finalize(DetourTo);
	return Wrapper;
}