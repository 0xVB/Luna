#include "Luna/Mod/ModParserDetector.hpp"

#include "Luna/Mod/FolderModParser.hpp"

using namespace Luna;

ModParserPtr ModParserDetector::detect(std::filesystem::path path)
{
    if (FolderModParser::isMod(path))
        return std::shared_ptr<ModParserInterface>(new FolderModParser(path));
    return nullptr;
}