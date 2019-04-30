#ifndef GALILEO_MESH_H
#define GALILEO_MESH_H

#include <vector>

#include "../Common.h"

class Mesh
{
public:
    explicit Mesh(GLfloat vertices[4][3]);

    virtual ~Mesh();

    void Draw();

private:
    GLuint _vaoId;
    std::vector<GLuint> _vbosIds;
};


#endif //GALILEO_MESH_H
