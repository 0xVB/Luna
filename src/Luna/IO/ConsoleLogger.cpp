#include "Luna/IO/ConsoleLogger.hpp"
#include <Windows.h>
#include <sstream>

using namespace Luna::IO;

#define BLACK         0
#define DARK_BLUE     1
#define DARK_GREEN    2
#define DARK_CYAN     3
#define DARK_RED      4
#define DARK_MAGENTA  5
#define DARK_YELLOW   6
#define LIGHT_GREY    7
#define DARK_GREY     8
#define BLUE          9
#define GREEN         10
#define CYAN          11
#define RED           12
#define MAGENTA       13
#define YELLOW        14
#define WHITE         15

HANDLE CONSOLE_HANDLE = nullptr;

void allocateConsole() {
    if (CONSOLE_HANDLE) return;
	AllocConsole();

	FILE* O = nullptr;
	freopen_s(&O, "CONOUT$", "w", stdout);

	CONSOLE_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitleA("LunaIO");
}

void applyColor(LogLevel level) {
    switch (level) {
    case LogLevel::info:
        SetConsoleTextAttribute(CONSOLE_HANDLE, CYAN);
        break;
    case LogLevel::warn:
        SetConsoleTextAttribute(CONSOLE_HANDLE, YELLOW);
        break;
    case LogLevel::error:
        SetConsoleTextAttribute(CONSOLE_HANDLE, RED);
        break;
    default:
        SetConsoleTextAttribute(CONSOLE_HANDLE, WHITE);
        break;
    }

}

void ConsoleLogger::log(LogLevel level, const char* message, ...)
{
    va_list args;
    va_start(args, message);
    
    applyColor(level);

    std::stringstream ss;
    ss << "[Luna] ";
    ss << message << "\n";

    vprintf(ss.str().c_str(), args);

    va_end(args);
}

ConsoleLogger::ConsoleLogger()
{
    allocateConsole();
    SetConsoleTitleA("Luna " LUNA_VERSION);
    SetConsoleTextAttribute(CONSOLE_HANDLE, WHITE);
}