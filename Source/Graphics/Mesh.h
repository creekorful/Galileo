#ifndef GALILEO_MESH_H
#define GALILEO_MESH_H

#include <vector>

#include "../Common.h"

class Mesh
{
public:
    Mesh(GLfloat **vertices, GLint *indices, int count);

    virtual ~Mesh();

    void Draw();

private:
    GLuint _vaoId;
    std::vector<GLuint> _vbosIds;
    int _verticesCount;
};


#endif //GALILEO_MESH_H
