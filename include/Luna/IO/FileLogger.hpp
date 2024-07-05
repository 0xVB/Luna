#pragma once

#include "ILogger.hpp"

namespace Luna::IO {
    class FileLogger : public ILogger {
    public:
        FileLogger(const char* path);

        void log(LogLevel level, const char* message, ...) override;
    private:
        const char* _path;
    };
}