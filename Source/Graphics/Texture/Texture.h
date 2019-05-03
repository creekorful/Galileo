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

    // Check if texture is valid
    bool IsValid() const;

private:
    GLint _textureId;
};


#endif //GALILEO_TEXTURE_H
