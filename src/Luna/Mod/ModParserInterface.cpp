#include "Luna/Mod/ModParserInterface.hpp"

using namespace Luna;

ModInfoPtr ModParserInterface::getInfo()
{
    return parseInfo();
}

ModDataPtr ModParserInterface::getModData()
{
    return parseModData();
}