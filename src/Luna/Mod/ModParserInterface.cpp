#include "Luna/Mod/ModParserInterface.hpp"

using namespace Luna;

ModInfoPtr ModParserInterface::getInfo()
{
    return parseInfo();
}

LunaScriptPtr ModParserInterface::getMainScript()
{
    return parseMainScript();
}