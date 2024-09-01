#pragma once
#include <lua.h>

namespace Luna {
    class TaskScheduler;
    class Job {
        public:
            Job(const char* name) : _name(name) {};
            virtual void run(TaskScheduler* ts) = 0;

            inline const char* getName() { return _name; }
            inline void markForRemoval() { _canRemove = true; }
            inline bool isMarkedForRemoval() { return _canRemove; }

        private:
            const char* _name = nullptr;
            bool _canRemove = false;
    };
    class BasicLuaJob : public Job
    {
        lua_State* gL;
        lua_State* sL;
        int delay;

    public:
        virtual void run(TaskScheduler* ts) override;
        BasicLuaJob(lua_State*, lua_State*, int delay = 0, const char* n = "BASIC_LUA_JOB");
    };
}