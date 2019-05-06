#ifndef GALILEO_TEXTUREFACTORY_H
#define GALILEO_TEXTUREFACTORY_H

#include <iostream>
#include <map>

#include "../../Common.h"

#include "Loader/BmpTextureLoader.h"
#include "Loader/PngTextureLoader.h"

class TextureFactory
{
public:
    bool Load(const std::string& file, const std::string& name);

    Texture& Get(const std::string& name);

    static TextureFactory& p()
    {
        static TextureFactory p;
        return p;
    }

private:
    std::map<std::string, Texture> _textures;
    Logger _logger;

    TextureFactory();
};


#endif //GALILEO_TEXTUREFACTORY_H
