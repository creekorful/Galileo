#ifndef GALILEO_MESH_H
#define GALILEO_MESH_H

#include <vector>

#include "../../Common.h"
#include "../Texture/Texture.h"

class Mesh
{
public:
    Mesh(std::vector<GLfloat> vertices,
         std::vector<GLfloat> uvs,
         std::vector<GLfloat> normals,
         std::vector<GLint> indices);

    virtual ~Mesh();

    void Render();

private:
    int _vertexCount;
    GLuint _vaoId;
    std::vector<GLuint> _vbosIds;

    /**
     * Generate & register a vbo
     * @return generated vbo id
     */
    GLuint GenerateVbo();
};


#endif //GALILEO_MESH_H
