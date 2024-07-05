#include "Luna/IO/FileLogger.hpp"

#include <stdarg.h>
#include <memory.h>
#include <filesystem>
#include <fstream>

namespace Luna::IO {
    FileLogger::FileLogger(const char* path) {
        _path = path;
        std::ofstream file(_path, std::ios::trunc);
    }
}

using namespace Luna::IO;

void FileLogger::log(LogLevel level, const char* message, ...) {
    std::ofstream file(_path, std::ios::app);
    if (!file.is_open()) {
        return;
    }
   
    va_list args;
    va_start(args, message);
    int size = vsnprintf(nullptr, 0, message, args);
    va_end(args);

    char* formattedMessage = new char[size + 1];
    va_start(args, message);
    vsnprintf(formattedMessage, size + 1, message, args);
    va_end(args);

    file << formattedMessage << std::endl;
    delete[] formattedMessage;
}