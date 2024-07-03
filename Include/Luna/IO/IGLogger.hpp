// in game logger
#pragma once

#include "ILogger.hpp"

namespace Luna::IO {
    class ConsoleLogger : public ILogger {
    public:
        ConsoleLogger();
        virtual ~ConsoleLogger();

        void log(LogLevel level, const char* message, ...) override;
    };
}