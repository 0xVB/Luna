#pragma once

namespace Luna::IO {
    enum class LogLevel { none, info, warn, error };

    class ILogger {
    public:
        ILogger() = default;

        virtual void log(LogLevel level, const char* message, ...) = 0;
    };
}