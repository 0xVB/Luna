#pragma once

#include "Job.hpp"

namespace Luna {
    class ModInitJob : public Job {
        public:
            ModInitJob() : Job("ModInitJob") {};
            void run(TaskScheduler* ts) override;
    };
}