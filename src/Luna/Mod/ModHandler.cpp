#include "Luna/Mod/ModHandler.hpp"

using namespace Luna;

void ModHandler::addMod(ModParserPtr mod)
{
    mods.push_back(mod);
}

void ModHandler::removeMod(ModParserPtr mod)
{
    mods.erase(std::remove(mods.begin(), mods.end(), mod), mods.end());
}

void ModHandler::addMods(std::vector<ModParserPtr> mods)
{
    this->mods.insert(this->mods.end(), mods.begin(), mods.end());
}

std::vector<ModParserPtr> ModHandler::getMods()
{
    return mods;
}