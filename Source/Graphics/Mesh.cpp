#include "Mesh.h"

Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLint> indices)
{
    // Generate and bind VAO
    glGenVertexArrays(1, &_vaoId);
    glBindVertexArray(_vaoId);

    // Generate and bind VBO
    GLuint vboId;
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);

    // Copy data to the buffers + specify coordinate data
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Unbind the VBO + register it
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    _vbosIds.push_back(vboId);

    // Generate VBO to store indices
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLint), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    _vbosIds.push_back(vboId);

    // Unbind the VAO
    glBindVertexArray(0);
}

void Mesh::Render()
{
    glBindVertexArray(_vaoId);
    glEnableVertexAttribArray(0);

    int size;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

    // last parameter is set to (0) because it represent the offset into the index buffer object
    // OpenGL will use the buffer GL_ELEMENT_ARRAY_BUFFER of the VAO automatically
    // see https://www.khronos.org/opengl/wiki/Vertex_Rendering#Basic_Drawing
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0); //??
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    // Delete VBOs
    glDeleteBuffers(_vbosIds.size(), _vbosIds.data());
    // Delete VAO
    glDeleteVertexArrays(1, &_vaoId);
}