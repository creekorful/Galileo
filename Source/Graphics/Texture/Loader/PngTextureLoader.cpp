#include "PngTextureLoader.h"

PngTextureLoader::PngTextureLoader() : _logger(LoggerFactory::CreateLogger("PngTextureLoader"))
{
}

Texture PngTextureLoader::LoadTexture(const std::string& filePath)
{
    Texture texture;

    // First of all read file content
    std::string content = Files::Read(filePath);

    return texture;
}
