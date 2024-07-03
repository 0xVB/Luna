#include "Luna/LocalModExplorer.hpp"

using namespace Luna;

LocalModExplorer::LocalModExplorer(std::filesystem::path path)
{
    modsPath = path;
    if (!std::filesystem::is_directory(modsPath))
        std::filesystem::create_directory(modsPath);
}

std::vector<ModInfo> LocalModExplorer::getMods()
{
    std::vector<ModInfo> mods;
    for(auto& p: std::filesystem::directory_iterator(modsPath))
    {
        if(!p.is_directory()) continue;
        // TODO: Implement ModParser
    }
    return mods;
}