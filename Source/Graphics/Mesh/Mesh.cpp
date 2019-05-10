#include "Mesh.h"

Mesh::Mesh(std::vector<GLfloat> vertices,
           std::vector<GLfloat> uvs,
           std::vector<GLfloat> normals,
           std::vector<GLint> indices, Texture* pTexture)
{
    // Generate and bind VAO
    glGenVertexArrays(1, &_vaoId);
    glBindVertexArray(_vaoId);

    // Generate VBO to store vertices
    glBindBuffer(GL_ARRAY_BUFFER, GenerateVbo());
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Generate VBO to store indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GenerateVbo());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLint), indices.data(), GL_STATIC_DRAW);

    // Generate VBO to store textures coordinates
    glBindBuffer(GL_ARRAY_BUFFER, GenerateVbo());
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(GLfloat), uvs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Generate VBO to store normals
    glBindBuffer(GL_ARRAY_BUFFER, GenerateVbo());
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    _pTexture = pTexture;
    _vertexCount = vertices.size();

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
    glEnableVertexAttribArray(2);

    // last parameter is set to (0) because it represent the offset into the index buffer object
    // OpenGL will use the buffer GL_ELEMENT_ARRAY_BUFFER of the VAO automatically
    // see https://www.khronos.org/opengl/wiki/Vertex_Rendering#Basic_Drawing
    glDrawElements(GL_TRIANGLES, _vertexCount, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    // Delete VBOs
    glDeleteBuffers(_vbosIds.size(), &_vbosIds[0]);
    // Delete VAO
    glDeleteVertexArrays(1, &_vaoId);
}

GLuint Mesh::GenerateVbo()
{
    GLuint vboId;
    glGenBuffers(1, &vboId);
    _vbosIds.push_back(vboId);
    return vboId;
}
