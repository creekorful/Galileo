#include "ObjFileLoader.h"

ObjFileLoader::ObjFileLoader(const std::string& filePath) : _logger(LoggerFactory::CreateLogger("ObjFileLoader"))
{
    _lines = Files::ReadLines(filePath);
    _logger.Debug(std::to_string(_lines.size()) + " lines loaded");
}

Mesh ObjFileLoader::ReadMesh(Texture* pTexture)
{
}
