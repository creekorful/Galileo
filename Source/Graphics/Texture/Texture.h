#ifndef GALILEO_TEXTURE_H
#define GALILEO_TEXTURE_H

#include "../../Common.h"

class Texture
{
public:
    /**
     * create an invalid texture object
     */
    Texture();

    explicit Texture(GLint textureId);

    void Bind();

    void Unbind();

    // Check if texture is valid
    bool IsValid() const;

    /**
     * Copy texture by coping texture id
     */
    Texture& operator=(const Texture& other);

private:
    GLint _textureId;
};


#endif //GALILEO_TEXTURE_H
