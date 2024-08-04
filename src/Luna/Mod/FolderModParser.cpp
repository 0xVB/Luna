#include "Luna/Mod/FolderModParser.hpp"
#include "Luna/Mod/LocalModInfo.hpp"
#include "Luna/Lua/ScriptCompiler.hpp"
#include <fstream>

using namespace Luna;

bool FolderModParser::isMod(std::filesystem::path path)
{
    if (std::filesystem::is_directory(path) && std::filesystem::exists(path / "main.lua"))
        return true;
    return false;
}

ModInfoPtr FolderModParser::parseInfo()
{
    auto info = std::shared_ptr<ModInfo>(new LocalModInfo(path.string()));
    info->setName(path.filename().string());

    return info;
}

LunaScriptPtr FolderModParser::parseMainScript()
{
    std::ifstream fileStream(path / "main.lua");
    if (!fileStream.is_open())
        return nullptr;
    std::string fileContents((std::istreambuf_iterator<char>(fileStream)),
                                std::istreambuf_iterator<char>());
    fileStream.close();
    return std::shared_ptr<LunaScript>(new LunaScript(shared_from_this(), ScriptCompiler::compileScript(fileContents)));
}