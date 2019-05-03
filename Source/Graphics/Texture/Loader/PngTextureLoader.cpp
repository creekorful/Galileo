#include "PngTextureLoader.h"

Texture PngTextureLoader::LoadTexture(const std::string& filePath)
{
    Texture texture;

    // First of all read file content
    std::string content = Files::Read(filePath);

    PngHeader header{};
    std::vector<PngChunk> chunks;

    memcpy((void*) &header, &content[0], sizeof(PngHeader));
    std::cout << "Infos from png file" << std::endl;
    std::cout << "Magic number valid : " << ((int) header.magic  == 0x89) << std::endl;
    std::cout << "Png tag: " << header.png[0] << header.png[1] << header.png[2] << std::endl;

    // todo check magic number + png tag

    // process with chunk reading

    // offset ptr at end of png header
    char* ptr = &content[0];
    ptr += (sizeof(PngHeader));

    // read
    PngChunk current;
    memcpy((void*) &current, ptr, sizeof(unsigned int) * sizeof(char) * 4);
    std::cout << "First chunk size: " << current.length << std::endl;
    std::cout << "First chunk type: " << current.type[0] << current.type[1] << current.type[2] << current.type[3] << std::endl;

    return texture;
}
