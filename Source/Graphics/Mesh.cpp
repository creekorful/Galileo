#include "Mesh.h"

Mesh::Mesh(GLfloat **vertices, int count)
{
    // 3 because 3 dimensions
    _verticesCount = count * 3;

    // Generate and bind VAO
    glGenVertexArrays(1, &_vaoId);
    glBindVertexArray(_vaoId);

    // Generate and bind VBO
    GLuint vboId;
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);

    // Copy data to the buffers + specify coordinate data
    glBufferData(GL_ARRAY_BUFFER, _verticesCount * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Unbind the VBO + register it
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    _vbosIds.push_back(vboId);

    // Unbind the VAO
    glBindVertexArray(0);
}

void Mesh::Draw()
{
    glBindVertexArray(_vaoId);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, _verticesCount);
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    // Delete VBOs
    glDeleteBuffers(_vbosIds.size(), _vbosIds.data());
    // Delete VAO
    glDeleteVertexArrays(1, &_vaoId);
}
