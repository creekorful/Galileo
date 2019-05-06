#include "PngTextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../../../../ThirdParty/stb_image.h"

PngTextureLoader::PngTextureLoader() : _logger(LoggerFactory::CreateLogger("PngTextureLoader"))
{
}

Texture PngTextureLoader::LoadTexture(const std::string& filePath)
{
    // First of all read file content
    std::string content = Files::Read(filePath);

    int width, height, bpp;
    unsigned char* rgb = stbi_load_from_memory((unsigned char*) &content[0], content.size(), &width, &height, &bpp, 0);
    if (rgb == nullptr)
    {
        _logger.Error("Error while reading " + filePath);
        return Texture();
    }

    _logger.Debug("Image size: " + std::to_string(width) + "x" + std::to_string(height));

    // Generate texture
    GLuint textureId;
    glGenTextures(1, &textureId);
    if (textureId == 0)
    {
        _logger.Error("Unable to generate texture");
        return Texture();
    }

    // store data
    glBindTexture(GL_TEXTURE_2D, textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // todo check if needed
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, rgb); // todo really rgba?

    glGenerateMipmap(GL_TEXTURE_2D);

    // cleanup
    stbi_image_free(rgb);

    return Texture(textureId);
}
