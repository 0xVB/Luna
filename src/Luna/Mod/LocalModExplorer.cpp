#include "Luna/Mod/LocalModExplorer.hpp"
#include "Luna/Mod/FolderModParser.hpp"
#include "Luna/Mod/ModParserDetector.hpp"

using namespace Luna;

LocalModExplorer::LocalModExplorer(std::filesystem::path path)
{
    modsPath = path;
    if (!std::filesystem::is_directory(modsPath))
        std::filesystem::create_directory(modsPath);
}

std::vector<ModInfoPtr> LocalModExplorer::getMods()
{
    std::vector<ModInfoPtr> mods;
    for(auto& p: std::filesystem::directory_iterator(modsPath))
    {
        auto parser = ModParserDetector::detect(p);
        if (!parser.get())
            continue;
        auto mod = parser->parse();
        if (!mod.get())
            continue;
        mods.push_back(mod);
    }
    return mods;
}