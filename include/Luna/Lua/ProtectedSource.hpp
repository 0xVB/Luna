#pragma once

#include <string>

namespace Luna {
    class ProtectedSource {
        private:
        std::string _source;
        public:
        ProtectedSource(std::string source) : _source(source) {};
        inline std::string getSource() { return _source; }
        std::string decompress();
    };
}