#pragma once

enum class LogLevel { none, info, warn, error };

namespace Luna::IO {

    class ILogger {
    public:
        ILogger() = default;

        virtual void log(LogLevel level, const char* message, ...) = 0;
    };
}