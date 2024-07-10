#include "Luna/Mod/ModHandler.hpp"

using namespace Luna;

void ModHandler::addMod(ModInfoPtr mod)
{
    mods.push_back(mod);
}

void ModHandler::removeMod(ModInfoPtr mod)
{
    mods.erase(std::remove(mods.begin(), mods.end(), mod), mods.end());
}

void ModHandler::addMods(std::vector<ModInfoPtr> mods)
{
    this->mods.insert(this->mods.end(), mods.begin(), mods.end());
}

std::vector<ModInfoPtr> ModHandler::getMods()
{
    return mods;
}