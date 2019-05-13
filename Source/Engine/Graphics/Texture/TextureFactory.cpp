#include "TextureFactory.h"

TextureFactory::TextureFactory() : _logger(LoggerFactory::CreateLogger("TextureFactory"))
{
}

TextureFactory::~TextureFactory()
{
    _logger.Debug("Cleaning up " + std::to_string(_pTextures.size()) + " textures");
    for (auto& texture : _pTextures)
    {
        delete texture.second;
    }
    _logger.Debug("Cleanup done");
}

Texture* TextureFactory::Load(const std::string& file, const std::string& name)
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

    _pTextures[name] = pTexture;
    _logger.Info("Texture loaded");
    return pTexture;
}

Texture* TextureFactory::Get(const std::string& name)
{
    _logger.Debug("Accessing texture with name: " + name);
    return _pTextures[name];
}
