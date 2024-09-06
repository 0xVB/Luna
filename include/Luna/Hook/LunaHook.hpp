#include <Windows.h>
#define usize size_t
#define u8 unsigned char
#define i32 int
usize getInstructionSize(const u8* bytes, i32** rel32 = nullptr);

#define LUNAHOOK_MAX_PARAMS 128

#ifndef LUNAHOOK_PARAM_COUNT
#define LUNAHOOK_PARAM_COUNT LUNAHOOK_MAX_PARAMS
#endif

class LunaHookThread
{
    LunaHookThread();

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

        NUM_REGISTERS = 8
    };

private:
    DWORD _registers[NUM_REGISTERS];
    bool _skip;

    static void DetourHeader(LunaHookThread*);
    static void DetourFooter(LunaHookThread*);
    class CodeBuffer;

public:
    typedef unsigned int (__cdecl* LunaWrapper)(...);

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

        bool inline isStackParam() const { return !isRegister; }
        bool inline isRegisterParam() const { return isRegister; }

        size_t GetCodeSize();
        unsigned char AddToBuffer(unsigned char* BufferStart, unsigned short StackOffset);
        void Encode(CodeBuffer*, char StackOffset = 0);
        char EncodeIn(CodeBuffer*, char StackOffset);
        Parameter(u8 StackOffset = 0);
        Parameter(Register32);
    };
    struct FunctionSignature
    {
    private:
        LunaHookThread* _parentThread;
        DWORD _addr;
        DWORD _oldProt;
        
        Parameter _parameters[LUNAHOOK_PARAM_COUNT];
        unsigned char _paramCount;
        size_t _paramCodeSize;
        size_t _stackSize;

        unsigned char _origCode[32];
        unsigned char _origCodeSize;

        FunctionSignature();
        void GetStackSize();
        void GetParamCodeSize();

    public:
        void AddParameter(Register32);
        void AddParameter(u8 StackOffset);
        void AddParameter();
        void AddStackParameters(u8 ParamCount);
        
        void Finalize(void* DetourTo);
        LunaWrapper AllocateWrapper();
        LunaWrapper FinalizeAndWrap(void* DetourTo);
        static FunctionSignature* New(LunaHookThread*, DWORD Address);
    };

    FunctionSignature* NewFunction(DWORD Address);
    void SetRegister(Register32, DWORD);
    DWORD GetRegister(Register32);
    void SetSkip(bool DoSkip);
    void SetReturn(DWORD);

    static LunaHookThread* New();
};