#include "PngTextureLoader.h"

Texture PngTextureLoader::LoadTexture(const std::string& filePath)
{
    Texture texture;

    // First of all read file content
    std::string content = Files::Read(filePath);

    PngHeader header{};

    memcpy((void*) &header, &content[0], sizeof(PngHeader));
    std::cout << "Infos from png file" << std::endl;
    std::cout << std::hex << header.magic << std::endl;
    std::cout << header.png[0] << header.png[1] << header.png[2] << std::endl;

    return texture;
}
