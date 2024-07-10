#include "Luna/Job/ModInitJob.hpp"
#include "Luna/Application.hpp"
#include "Luna/ScriptContext.hpp"

using namespace Luna;

void ModInitJob::run(TaskScheduler* ts) {
    const auto app = Application::getSingleton();
    const auto sc = ScriptContext::getSingleton();
    for (const auto& mod : app->getLoadedMods()) {
        auto modData = mod->getModData();
        if (!modData.get())
            continue;
        auto mainScript = modData->getMainScript();
        if (!mainScript.get())
            continue;
        sc->startScript(mainScript);
    }
    // job can be removed from running jobs
    markForRemoval();
}