#pragma once

#include <string>

namespace Luna {
    class ProtectedSource {
        private:
        std::string _source;
        public:
        ProtectedSource(std::string source) : _source(source) {};
        std::string decompress();
    };
}