#include "TextureFactory.h"

TextureFactory::TextureFactory() : _logger(LoggerFactory::CreateLogger("TextureFactory"))
{
}

bool TextureFactory::Load(const std::string& file, const std::string& name)
{
    _logger.Info("Loading texture with path: " + file + " and name: " + name);

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
        _logger.Info("Texture is valid. Process with registering");
        _textures[name] = texture;
    }

    return texture.IsValid();
}

Texture& TextureFactory::Get(const std::string& name)
{
    _logger.Debug("Accessing texture with name: " + name);
    return _textures[name];
}
