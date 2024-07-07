#include "Luna/Job/ModInitJob.hpp"

using namespace Luna;

void ModInitJob::run(TaskScheduler* ts) {
    // TODO: run loaded mods safely
    // job can be removed from running jobs
    markForRemoval();
}