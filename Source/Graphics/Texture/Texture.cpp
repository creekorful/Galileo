#include "Texture.h"

Texture::Texture()
{
    _textureId = 0;
}

Texture::Texture(const GLint textureId)
{
    _textureId = textureId;
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
