#include "Luna/TaskScheduler.hpp"

#include "Luna/Job/ModInitJob.hpp"

using namespace Luna;

TaskScheduler* TaskScheduler::getSingleton() {
    static TaskScheduler singleton;
    return &singleton;
}

void TaskScheduler::initialize() {
    registerJob(new ModInitJob());
}

void TaskScheduler::update() {
    // run jobs
    for (auto& job : _jobs) {
        job->run(this);
    }

    // remove marked jobs
    _jobs.erase(std::remove_if(_jobs.begin(), _jobs.end(), [](const auto& job) {
        return job->isMarkedForRemoval();
    }), _jobs.end());
}

void TaskScheduler::registerJob(Job* job) {
    auto sharedJob = std::shared_ptr<Job>(job);
    _jobs.push_back(sharedJob);
}

BasicLuaJob::BasicLuaJob(lua_State* g, lua_State* l, int del, const char* n) : Job(n)
{
    delay = del;
    gL = g;
    sL = l;
}

#include "Luna/Application.hpp"
#include "Luna/Lua/Utils.hpp"
void BasicLuaJob::run(TaskScheduler*)
{
    delay--;
    if (delay > 0) return;
    int state = lua_resume(sL, nullptr, 0);
    if (state == LUA_YIELD)
    {
        delay = LuaToNum(sL, -1);
        delay = (delay < 0) ? 0 : delay;
        return;
    }
    else
        markForRemoval();

    if (state != LUA_OK)
    {
        if (lua_isstring(sL, -1)) {
            const char* error = lua_tostring(sL, -1);
            Application::getSingleton()->getLogger()->log(LogLevel::error, (std::string("Error in ") + getName() + ": " + error).c_str());
        }
        lua_close(sL);
    }
}