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