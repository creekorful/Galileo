#include "Texture.h"

Texture::Texture()
{
    _textureId = 0;
}

Texture::Texture(const GLint textureId)
{
    _textureId = textureId;
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE_2D);
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

Texture& Texture::operator=(const Texture& other)
{
    _textureId = other._textureId;
    return *this;
}
