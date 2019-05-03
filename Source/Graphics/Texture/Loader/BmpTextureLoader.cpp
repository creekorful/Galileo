#include "BmpTextureLoader.h"

Texture BmpTextureLoader::LoadTexture(const std::string& filePath)
{
    Texture texture;

    // First of all load content from BMP file
    std::string content = Files::Read(filePath);

    return texture;
}
