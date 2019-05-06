#include "TextureFactory.h"

TextureFactory::TextureFactory() : _logger(LoggerFactory::CreateLogger("TextureFactory"))
{
}

TextureFactory::~TextureFactory()
{
    for (const auto&[name, value] : _textures)
    {
        delete value;
    }
}

bool TextureFactory::Load(const std::string& file, const std::string& name)
{
    _logger.Info("Loading texture with path: " + file + " and name: " + name);

    // Compute extension
    std::string ext = file.substr(file.find_last_of('.'));

    Texture* pTexture = nullptr;
    if (ext == ".png")
    {
        PngTextureLoader loader;
        pTexture = loader.LoadTexture(file);
    }

    if (pTexture == nullptr || !pTexture->IsValid())
    {
        _logger.Error("Invalid texture");
        delete pTexture;
    }

    _textures[name] = pTexture;
    _logger.Info("Texture loaded");
    return pTexture;
}

Texture* TextureFactory::Get(const std::string& name)
{
    _logger.Debug("Accessing texture with name: " + name);
    return _textures[name];
}
