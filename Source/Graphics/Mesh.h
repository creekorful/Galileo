#ifndef GALILEO_MESH_H
#define GALILEO_MESH_H

#include <vector>

#include "../Common.h"

class Mesh
{
public:
    explicit Mesh(GLfloat **vertices, int verticeCount);

    virtual ~Mesh();

    void Draw();

private:
    GLuint _vaoId;
    std::vector<GLuint> _vbosIds;
    int _verticeCount;
};


#endif //GALILEO_MESH_H
