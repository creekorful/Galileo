#ifndef GALILEO_PNGTEXTURELOADER_H
#define GALILEO_PNGTEXTURELOADER_H

#include <iostream>
#include <vector>

#include "TextureLoader.h"

struct PngHeader
{
    unsigned char magic;
    char png[3];
    unsigned char lineEnding[2];
    unsigned char stopDisplay;
    unsigned char unixLineEnding;
} typedef PngHeader;

struct PngChunk
{
    int length;
    char type[4]; // IHDR, PLTE, IDAT, IEND, ...
    unsigned char* data;
    unsigned int crc;
} typedef PngChunk;


/**
 * Texture loaded that load from png file
 *
 * built using https://en.wikipedia.org/wiki/Portable_Network_Graphics as reference
 */
class PngTextureLoader : public TextureLoader
{
public:
    Texture LoadTexture(const std::string& filePath) override;

private:

    /**
     * Perform big-endian to little-endian conversion
     *
     * https://stackoverflow.com/questions/2182002/convert-big-endian-to-little-endian-in-c-without-using-provided-func
     */
    static void SwapBytes(void* pv, size_t n);

    static void ReadChunk(PngChunk& chunk, char*& ptr);
};


#endif //GALILEO_PNGTEXTURELOADER_H

// d400 0000 0173 5247