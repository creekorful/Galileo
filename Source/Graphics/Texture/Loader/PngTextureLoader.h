#ifndef GALILEO_PNGTEXTURELOADER_H
#define GALILEO_PNGTEXTURELOADER_H

#include <iostream>
#include <vector>

#include "TextureLoader.h"

/**
 * Texture loaded that load from png file
 */
class PngTextureLoader : public TextureLoader
{
public:
    PngTextureLoader();

    Texture LoadTexture(const std::string& filePath) override;

private:
    Logger _logger;
};


#endif //GALILEO_PNGTEXTURELOADER_H