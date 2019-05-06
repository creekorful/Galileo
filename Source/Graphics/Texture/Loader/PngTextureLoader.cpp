#include "PngTextureLoader.h"

Texture PngTextureLoader::LoadTexture(const std::string& filePath)
{
    Texture texture;

    // First of all read file content
    std::string content = Files::Read(filePath);

    // Useful datas
    PngHeader header{};
    IHDRData ihdrData;
    std::vector<PngChunk> chunks;
    std::vector<PngPixel> pixels;

    std::memcpy((void*) &header, &content[0], sizeof(PngHeader));
    std::cout << "Infos from png file" << std::endl;
    std::cout << "Size: " << content.size() << " bytes" << std::endl;
    std::cout << "Magic number valid : " << ((int) header.magic == 0x89) << std::endl;
    std::cout << "Png tag: " << header.png[0] << header.png[1] << header.png[2] << std::endl;

    // make sure magic number is valid
    if (header.magic != 0x89 || header.png[0] != 'P' || header.png[1] != 'N' || header.png[2] != 'G')
    {
        return texture;
    }

    // offset ptr at end of png header
    char* ptr = &content[0];
    ptr += (sizeof(PngHeader));

    // read size + type of current chunk
    PngChunk current;
    do
    {
        ReadChunk(current, ptr);
        if (IS_IHDR_CHUNK(current))
        {
            std::memcpy((void*) &ihdrData, current.data, sizeof(IHDRData));
            SwapBytes(&ihdrData.height, 4);
            SwapBytes(&ihdrData.width, 4);

            // only allow truecolor mode (8bits per pixel : red, green, blue)
            if (ihdrData.bitDepth != 8 || ihdrData.colorType != 2)
            {
                // todo log error
                return texture;
            }
        } else if (IS_IDAT_CHUNK(current))
        {
            for (int i = 0; i < current.length; i += 3)
            {
                PngPixel pixel{};
                pixel.red = current.data[i];
                pixel.green = current.data[i + 1];
                pixel.blue = current.data[i + 2];
                pixels.push_back(pixel);
            }
        }
        chunks.push_back(current);
    } while (current.type[0] != 'I' || current.type[1] != 'E' || current.type[2] != 'N' || current.type[3] != 'D');

    std::cout << "PNG file read successful. Process with decoding" << std::endl;
    std::cout << "Size: " << ihdrData.width << "x" << ihdrData.height << std::endl;
    std::cout << "Depth: " << (int) ihdrData.bitDepth << std::endl;
    std::cout << "Color type: " << (int) ihdrData.colorType << std::endl;
    std::cout << "Filter method: " << (int) ihdrData.filterMethod << std::endl;
    std::cout << "Compression method: " << (int) ihdrData.compressionMethod << std::endl;
    std::cout << "Interlace method: " << (int) ihdrData.interlaceMethod << std::endl;
    std::cout << "Total pixels: " << pixels.size() << std::endl;

    std::cout << "A: " << pixels.size() % ihdrData.width << std::endl;
    std::cout << "B: " << pixels.size() % ihdrData.height << std::endl;

    // Free chunks
    for (auto& chunk : chunks)
    {
        delete[] chunk.data;
    }

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

    // Now we have size, we can allocate + read data buffer
    chunk.data = new unsigned char[chunk.length];
    std::memcpy((void*) chunk.data, ptr, chunk.length);
    ptr += chunk.length; // advance pointer to CRC

    // Finally CRC
    std::memcpy((void*) &chunk.crc, ptr, sizeof(unsigned int));
    ptr += sizeof(unsigned int);
}
