#include "Luna/Mod/ModParserDetector.hpp"

#include "Luna/Mod/FolderModParser.hpp"

using namespace Luna;

std::shared_ptr<ModParserInterface> ModParserDetector::detect(std::filesystem::path path)
{
    if (FolderModParser::isMod(path))
        return std::make_shared<FolderModParser>(path);
    return nullptr;
}