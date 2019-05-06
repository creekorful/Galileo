#ifndef GALILEO_MESH_H
#define GALILEO_MESH_H

#include <vector>

#include "../../Common.h"
#include "../Texture/Texture.h"

class Mesh
{
public:
    Mesh(std::vector<GLfloat> vertices, std::vector<GLint> indices);

    void SetTexture(std::vector<GLfloat> uvs, Texture* pTexture);

    virtual ~Mesh();

    void Render();

private:
    GLuint _vaoId;
    std::vector<GLuint> _vbosIds;

    Texture* _pTexture;
};


#endif //GALILEO_MESH_H
