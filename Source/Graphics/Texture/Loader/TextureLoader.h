#ifndef GALILEO_TEXTURELOADER_H
#define GALILEO_TEXTURELOADER_H

#include <iostream>

#include "../Texture.h"
#include "../../../IO/Files.h"

/**
 * Base class for texture loader
 */
class TextureLoader
{
public:
    virtual Texture LoadTexture(const std::string& filePath) = 0;
};

#endif //GALILEO_TEXTURELOADER_H
