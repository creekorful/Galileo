#ifndef GALILEO_PNGTEXTURELOADER_H
#define GALILEO_PNGTEXTURELOADER_H

#include <iostream>
#include <vector>
#include <zlib.h>

#include "TextureLoader.h"

#define CHECK_CHUNK(x, i0, i1, i2, i3) x.type[0] == i0 && x.type[1] == i1 && x.type[2] == i2 && x.type[3] == i3
#define IS_IHDR_CHUNK(x) CHECK_CHUNK(x, 'I', 'H', 'D', 'R')
#define IS_IDAT_CHUNK(x) CHECK_CHUNK(x, 'I', 'D', 'A', 'T')

#define FILTER_NONE 0
#define FILTER_SUB 1
#define FILTER_UP 2
#define FILTER_AVG 3
#define FILTER_PAETH 4

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

struct IHDRData
{
    unsigned int width;
    unsigned int height;
    unsigned char bitDepth;
    unsigned char colorType;
    unsigned char compressionMethod;
    unsigned char filterMethod;
    unsigned char interlaceMethod;
} typedef IHDRData;

// Only manage 3 channel of 8 bit each at the moment
struct PngPixel
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} typedef PngPixel;

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