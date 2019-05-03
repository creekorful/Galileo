#include "TextureFactory.h"

bool TextureFactory::Load(const std::string& file, const std::string& name)
{
    // Compute extension
    std::string ext = file.substr(file.find_last_of('.'));

    Texture texture;
    if (ext == ".bmp")
    {
        BmpTextureLoader loader;
        texture = loader.LoadTexture(file);
    }
    else if (ext == ".png")
    {
        PngTextureLoader loader;
        texture = loader.LoadTexture(file);
    }

    if (texture.IsValid())
    {
        _textures[name] = texture;
    }

    return texture.IsValid();
}

Texture& TextureFactory::Get(const std::string& name)
{
    return _textures[name];
}
