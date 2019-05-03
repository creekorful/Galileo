#include "TextureFactory.h"

bool TextureFactory::Load(const std::string& file, const std::string& name)
{
    // Compute extension
    std::string ext = file.substr(file.find_last_of('.'));

    if (ext == ".bmp")
    {
        BmpTextureLoader loader;
        Texture texture = loader.LoadTexture(file);
        if (texture.IsValid())
        {
            _textures[name] = texture;
        }

        return texture.IsValid();
    }

    return false;
}

Texture& TextureFactory::Get(const std::string& name)
{
    return _textures[name];
}
