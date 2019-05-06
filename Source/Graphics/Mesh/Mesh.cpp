#include "Mesh.h"

Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLfloat> uvs, std::vector<GLint> indices, Texture* pTexture)
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
    _vbosIds.push_back(vboId);

    // Generate VBO to store indices
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLint), indices.data(), GL_STATIC_DRAW);
    _vbosIds.push_back(vboId);

    // Generate VBO to store textures coordinates
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);

    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(GLfloat), uvs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    _vbosIds.push_back(vboId);
    _pTexture = pTexture;

    // Unbind the VAO + VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); // optional but may increase performance (to check)
}

void Mesh::Render()
{
    _pTexture->Bind();

    glBindVertexArray(_vaoId);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    int size;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

    // last parameter is set to (0) because it represent the offset into the index buffer object
    // OpenGL will use the buffer GL_ELEMENT_ARRAY_BUFFER of the VAO automatically
    // see https://www.khronos.org/opengl/wiki/Vertex_Rendering#Basic_Drawing
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0); //??
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    // Delete VBOs
    glDeleteBuffers(_vbosIds.size(), _vbosIds.data());
    // Delete VAO
    glDeleteVertexArrays(1, &_vaoId);
}
