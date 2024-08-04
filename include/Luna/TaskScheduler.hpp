#pragma once

#include "Job/Job.hpp"
#include <vector>
#include <memory>

namespace Luna {
    class TaskScheduler {
        public:
            TaskScheduler() = default;
            static TaskScheduler* getSingleton();

            void initialize();
            void update();
            void registerJob(Job* job);
        private:
            std::vector<std::shared_ptr<Job>> _jobs = {};
    };
}
