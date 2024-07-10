#include "Luna/Mod/FolderModParser.hpp"
#include "Luna/Mod/LocalModInfo.hpp"

using namespace Luna;

bool FolderModParser::isMod(std::filesystem::path path)
{
    if (std::filesystem::is_directory(path) && std::filesystem::exists(path / "main.lua"))
        return true;
}

ModInfoPtr FolderModParser::parse()
{
    auto info = std::shared_ptr<ModInfo>(new LocalModInfo(path.string()));
    info->setName(path.filename().string());
    

    return info;
}