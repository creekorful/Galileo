#include "PngTextureLoader.h"

Texture PngTextureLoader::LoadTexture(const std::string& filePath)
{
    Texture texture;

    // First of all read file content
    std::string content = Files::Read(filePath);

    std::cout << "Start address: " << (size_t) &content[0] << std::endl;
    std::cout << "End address: " << (size_t) &content[content.size()-1] << std::endl;

    PngHeader header{};
    std::vector<PngChunk> chunks;

    std::memcpy((void*) &header, &content[0], sizeof(PngHeader));
    std::cout << "Infos from png file" << std::endl;
    std::cout << "Size: " << content.size() << " bytes" << std::endl;
    std::cout << "Magic number valid : " << ((int) header.magic == 0x89) << std::endl;
    std::cout << "Png tag: " << header.png[0] << header.png[1] << header.png[2] << std::endl;
    std::cout << "Reading chunks" << std::endl;

    // make sure magic number is valid
    if (header.magic != 0x89)
    {
        return texture;
    }

    // process with chunk reading

    // offset ptr at end of png header
    char* ptr = &content[0];
    ptr += (sizeof(PngHeader));

    // read size + type of current chunk
    PngChunk current;
    do
    {
        ReadChunk(current, ptr);
        chunks.push_back(current);
    } while (current.type[0] != 'I' || current.type[1] != 'E' || current.type[2] != 'N' || current.type[3] != 'D');

    // todo free memory

    return texture;
}

void PngTextureLoader::SwapBytes(void* pv, size_t n)
{
    assert(n > 0);

    char* p = (char*) pv;
    size_t lo, hi;
    for (lo = 0, hi = n - 1; hi > lo; lo++, hi--)
    {
        char tmp = p[lo];
        p[lo] = p[hi];
        p[hi] = tmp;
    }
}

void PngTextureLoader::ReadChunk(PngChunk& chunk, char*& ptr)
{
    // First of all pre-copy length + type because it's fixed size
    std::memcpy((void*) &chunk, ptr, sizeof(unsigned int) + (sizeof(char) * 4));
    ptr += sizeof(unsigned int) + (sizeof(char) * 4); // advance pointer to data

    // convert length to little endian
    SwapBytes((void*) &chunk.length, 4);

    std::cout << "Chunk type: " << chunk.type[0] << chunk.type[1] << chunk.type[2] << chunk.type[3] << std::endl;
    std::cout << "Chunk size: " << (int) chunk.length << std::endl;

    // Now we have size, we can allocate + read data buffer
    std::cout << "Current address: " << (size_t) ptr << std::endl;
    chunk.data = new unsigned char[chunk.length];
    std::memcpy((void*) &chunk.data, ptr, chunk.length);
    ptr += chunk.length; // advance pointer to CRC

    // Finally CRC
    std::memcpy((void*) &chunk.crc, ptr, sizeof(unsigned int));
    ptr += sizeof(unsigned int);
}
