#include <windows.h>

struct version_dll { 
	HMODULE dll;
	FARPROC OrignalGetFileVersionInfoA;
	FARPROC OrignalGetFileVersionInfoByHandle;
	FARPROC OrignalGetFileVersionInfoExA;
	FARPROC OrignalGetFileVersionInfoExW;
	FARPROC OrignalGetFileVersionInfoSizeA;
	FARPROC OrignalGetFileVersionInfoSizeExA;
	FARPROC OrignalGetFileVersionInfoSizeExW;
	FARPROC OrignalGetFileVersionInfoSizeW;
	FARPROC OrignalGetFileVersionInfoW;
	FARPROC OrignalVerFindFileA;
	FARPROC OrignalVerFindFileW;
	FARPROC OrignalVerInstallFileA;
	FARPROC OrignalVerInstallFileW;
	FARPROC OrignalVerLanguageNameA;
	FARPROC OrignalVerLanguageNameW;
	FARPROC OrignalVerQueryValueA;
	FARPROC OrignalVerQueryValueW;
} version;

__declspec(naked) void FakeGetFileVersionInfoA() { _asm { jmp[version.OrignalGetFileVersionInfoA] } }
__declspec(naked) void FakeGetFileVersionInfoByHandle() { _asm { jmp[version.OrignalGetFileVersionInfoByHandle] } }
__declspec(naked) void FakeGetFileVersionInfoExA() { _asm { jmp[version.OrignalGetFileVersionInfoExA] } }
__declspec(naked) void FakeGetFileVersionInfoExW() { _asm { jmp[version.OrignalGetFileVersionInfoExW] } }
__declspec(naked) void FakeGetFileVersionInfoSizeA() { _asm { jmp[version.OrignalGetFileVersionInfoSizeA] } }
__declspec(naked) void FakeGetFileVersionInfoSizeExA() { _asm { jmp[version.OrignalGetFileVersionInfoSizeExA] } }
__declspec(naked) void FakeGetFileVersionInfoSizeExW() { _asm { jmp[version.OrignalGetFileVersionInfoSizeExW] } }
__declspec(naked) void FakeGetFileVersionInfoSizeW() { _asm { jmp[version.OrignalGetFileVersionInfoSizeW] } }
__declspec(naked) void FakeGetFileVersionInfoW() { _asm { jmp[version.OrignalGetFileVersionInfoW] } }
__declspec(naked) void FakeVerFindFileA() { _asm { jmp[version.OrignalVerFindFileA] } }
__declspec(naked) void FakeVerFindFileW() { _asm { jmp[version.OrignalVerFindFileW] } }
__declspec(naked) void FakeVerInstallFileA() { _asm { jmp[version.OrignalVerInstallFileA] } }
__declspec(naked) void FakeVerInstallFileW() { _asm { jmp[version.OrignalVerInstallFileW] } }
__declspec(naked) void FakeVerLanguageNameA() { _asm { jmp[version.OrignalVerLanguageNameA] } }
__declspec(naked) void FakeVerLanguageNameW() { _asm { jmp[version.OrignalVerLanguageNameW] } }
__declspec(naked) void FakeVerQueryValueA() { _asm { jmp[version.OrignalVerQueryValueA] } }
__declspec(naked) void FakeVerQueryValueW() { _asm { jmp[version.OrignalVerQueryValueW] } }

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	char path[MAX_PATH];
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		CopyMemory(path + GetSystemDirectory(path, MAX_PATH - 13), "\\version.dll", 14);
		version.dll = LoadLibrary(path);
		if (version.dll == false)
		{
			MessageBox(0, "Cannot load original version.dll library", "Proxy", MB_ICONERROR);
			ExitProcess(0);
		}
		version.OrignalGetFileVersionInfoA = GetProcAddress(version.dll, "GetFileVersionInfoA");
		version.OrignalGetFileVersionInfoByHandle = GetProcAddress(version.dll, "GetFileVersionInfoByHandle");
		version.OrignalGetFileVersionInfoExA = GetProcAddress(version.dll, "GetFileVersionInfoExA");
		version.OrignalGetFileVersionInfoExW = GetProcAddress(version.dll, "GetFileVersionInfoExW");
		version.OrignalGetFileVersionInfoSizeA = GetProcAddress(version.dll, "GetFileVersionInfoSizeA");
		version.OrignalGetFileVersionInfoSizeExA = GetProcAddress(version.dll, "GetFileVersionInfoSizeExA");
		version.OrignalGetFileVersionInfoSizeExW = GetProcAddress(version.dll, "GetFileVersionInfoSizeExW");
		version.OrignalGetFileVersionInfoSizeW = GetProcAddress(version.dll, "GetFileVersionInfoSizeW");
		version.OrignalGetFileVersionInfoW = GetProcAddress(version.dll, "GetFileVersionInfoW");
		version.OrignalVerFindFileA = GetProcAddress(version.dll, "VerFindFileA");
		version.OrignalVerFindFileW = GetProcAddress(version.dll, "VerFindFileW");
		version.OrignalVerInstallFileA = GetProcAddress(version.dll, "VerInstallFileA");
		version.OrignalVerInstallFileW = GetProcAddress(version.dll, "VerInstallFileW");
		version.OrignalVerLanguageNameA = GetProcAddress(version.dll, "VerLanguageNameA");
		version.OrignalVerLanguageNameW = GetProcAddress(version.dll, "VerLanguageNameW");
		version.OrignalVerQueryValueA = GetProcAddress(version.dll, "VerQueryValueA");
		version.OrignalVerQueryValueW = GetProcAddress(version.dll, "VerQueryValueW");

		LoadLibrary("Luna.dll"); // dear Luna
		break;
	}
	case DLL_PROCESS_DETACH:
	{
		FreeLibrary(version.dll);
	}
	break;
	}
	return TRUE;
}
