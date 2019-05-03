#ifndef GALILEO_PNGTEXTURELOADER_H
#define GALILEO_PNGTEXTURELOADER_H

#include "TextureLoader.h"

class PngTextureLoader : public TextureLoader
{
public:
    Texture LoadTexture(const std::string& filePath) override;
};


#endif //GALILEO_PNGTEXTURELOADER_H
