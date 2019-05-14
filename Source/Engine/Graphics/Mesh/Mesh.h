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

    void SetTexture(Texture *pTexture);

    std::vector<GLfloat> Vertices() const;
    std::vector<GLfloat> Uvs() const;
    std::vector<GLfloat> Normals() const;
    std::vector<GLint> Indices() const;

private:
    std::vector<GLfloat> _vertices;
    std::vector<GLfloat> _uvs;
    std::vector<GLfloat> _normals;
    std::vector<GLint> _indices;

    GLuint _vaoId;
    std::vector<GLuint> _vbosIds;

    Texture* _pTexture;

    /**
     * Generate & register a vbo
     * @return generated vbo id
     */
    GLuint GenerateVbo();
};


#endif //GALILEO_MESH_H
