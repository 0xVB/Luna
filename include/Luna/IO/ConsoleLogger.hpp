#pragma once

#include "ILogger.hpp"

namespace Luna::IO {
    class ConsoleLogger : public ILogger {
    public:
        ConsoleLogger();

        void log(LogLevel level, const char* message, ...) override;
    };
}