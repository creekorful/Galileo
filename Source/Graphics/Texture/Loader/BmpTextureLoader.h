#ifndef GALILEO_BMPTEXTURELOADER_H
#define GALILEO_BMPTEXTURELOADER_H

#include "TextureLoader.h"
#include "../../../IO/Files.h"

/**
 * Texture loaded that load from bmp file
 */
class BmpTextureLoader : public TextureLoader
{
public:
    Texture LoadTexture(const std::string& filePath) override;
};


#endif //GALILEO_BMPTEXTURELOADER_H
