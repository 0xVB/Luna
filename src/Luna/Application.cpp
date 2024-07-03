#include "Luna/Application.hpp"
#include "Luna/IO/ConsoleLogger.hpp"
#include "Luna/LocalModExplorer.hpp"
#include <kiero.h>

using namespace Luna;


Application::Application()
{
    logger = std::make_shared<IO::ConsoleLogger>();
    localModExplorer = std::make_shared<LocalModExplorer>("mods");
}

Application::~Application()
{
}

std::shared_ptr<IO::ILogger> Application::getLogger()
{
    return logger;
}

bool Application::initialize()
{
    if(kiero::init(kiero::RenderType::Auto) != kiero::Status::Success) return false;
    return true;
}
