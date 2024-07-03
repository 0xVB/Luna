#pragma once

namespace Luna
{
    class Application {
    public:
        Application();
        virtual ~Application();

        bool initialize();
    };
}