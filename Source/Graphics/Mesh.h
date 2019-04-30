#ifndef GALILEO_MESH_H
#define GALILEO_MESH_H

#include <vector>

#include "../Common.h"

class Mesh
{
public:
    Mesh(std::vector<GLfloat> vertices, std::vector<GLint> indices);

    virtual ~Mesh();

    void Draw();

private:
    GLuint _vaoId;
    std::vector<GLuint> _vbosIds;
};


#endif //GALILEO_MESH_H
