#ifndef GALILEO_PNGTEXTURELOADER_H
#define GALILEO_PNGTEXTURELOADER_H

#include <iostream>
#include <cstring>

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
    unsigned int length;
    unsigned char type[4]; // IHDR, PLTE, IDAT, IEND, ...
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
};


#endif //GALILEO_PNGTEXTURELOADER_H
