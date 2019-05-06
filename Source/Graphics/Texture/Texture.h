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

    explicit Texture(GLuint textureId);

    ~Texture();

    void Bind();

    void Unbind();

    // Check if texture is valid
    bool IsValid() const;

private:
    GLuint _textureId;
};


#endif //GALILEO_TEXTURE_H
