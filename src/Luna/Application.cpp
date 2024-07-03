#include "Luna/Application.hpp"
#include <kiero.h>

using namespace Luna;


Application::Application()
{
}

Application::~Application()
{
}

bool Application::initialize()
{
    if(kiero::init(kiero::RenderType::Auto) != kiero::Status::Success) return false;
    return true;
}
