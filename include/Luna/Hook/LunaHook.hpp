#include <Windows.h>
#define usize size_t
#define u8 unsigned char
#define i32 int
usize getInstructionSize(const u8* bytes, i32** rel32 = nullptr);

class LunaHookThread
{
public:
    enum Register32 : unsigned char
    {
        EAX,
        ECX,
        EDX,
        EBX,

        ESP,
        EBP,
        ESI,
        EDI,

        NUM = 8
    };

    struct Parameter
    {
        union
        {
            struct
            {
                bool isRegister : 1;
                Register32 mRegister : 7;
            };
            unsigned char mStackOffset;
        };

        bool IsRegisterParam();
        bool IsStackParam();

        unsigned char AddToBuffer(unsigned char* BufferStart, unsigned short Offset);

        Parameter(unsigned char StackOffset = 0);
        Parameter(Register32);
    };
    struct FunctionSignature
    {
    private:
        LunaHookThread* _parentThread;

    public:
        DWORD mAddress;
        DWORD mOldProt;
        bool hasReturn;
        Parameter mParameters[128];
        unsigned char mParameterCount;
        unsigned char mOriginalCode[32];
        unsigned char mOriginalCodeSize;

        void AddParameter(Register32);
        void AddParameter(unsigned char StackOffset);
        void Hook(void* DetourTo);

        FunctionSignature(DWORD FunctionAddress = 0, bool Returns = false);
    };

private:
    static const u8 _SaveRegisters = 0x00;
    static const u8 _LoadRegPresEAX = 0x04;
    static const u8 _LoadReg = 0x08;
    static const u8 _Reset = 0x0C;

    static const u8 _SetReg = 0x10;
    static const u8 _SetRet = 0x14;
    static const u8 _Skip = 0x18;

    static const u8 _IsChanged = 0x04;
    static const u8 _RetAddr = 0x08;

    static const u8 _eax = 0x0C;
    static const u8 _ecx = 0x10;
    static const u8 _edx = 0x14;
    static const u8 _ebx = 0x18;
    static const u8 _esp = 0x1C;
    static const u8 _ebp = 0x20;
    static const u8 _esi = 0x24;
    static const u8 _edi = 0x28;


    bool _isChanged;
    DWORD _mReturnAddress;
    DWORD _mRegisters[NUM];

    virtual void SaveRegisters(DWORD eax, DWORD ecx, DWORD edx);// 00
    virtual void LoadRegistersPreserveEAX();// 04
    virtual void LoadRegisters();// 08
    virtual void ResetState();// 0C

public:
    virtual void SetRegister(Register32, DWORD Value);// 10
    virtual void SetReturnAddress(DWORD);// 14
    virtual void SkipOriginalCode();// 18
};