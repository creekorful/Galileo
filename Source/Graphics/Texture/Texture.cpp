#include "Texture.h"

Texture::Texture()
{
    _textureId = 0;
}

Texture::~Texture()
{
    glDeleteTextures(1, &_textureId);
}

Texture::Texture(const GLuint textureId)
{
    _textureId = textureId;
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureId);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::IsValid() const
{
    return _textureId != 0;
}