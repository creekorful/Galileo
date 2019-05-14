#include "Chunk.h"

Chunk::Chunk(std::vector<float>& rawBlocks, const Vector3f& worldPos, Mesh* pCubeMesh, Texture* pTexture) :
        GameObject(nullptr, worldPos.x, worldPos.y, worldPos.z), _rawBlocks(rawBlocks), _pTexture(pTexture)
{
    _rawBlocks = rawBlocks;
    _pCubeMesh = pCubeMesh;

    GenerateMesh();
}

void Chunk::GenerateMesh()
{
    // First of all delete previous mesh
    delete _pMesh;

    std::vector<GLfloat> vertices;
    std::vector<GLfloat> uvs;
    std::vector<GLfloat> normals;
    std::vector<GLint> indices;

    int indiceOffset = 0;

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            // compute height at given pos
            float height = _rawBlocks[x * CHUNK_SIZE + z];

            // Insert vertices
            std::vector<GLfloat> srcVertices = _pCubeMesh->Vertices();
            for (int t = 0; t < srcVertices.size(); t += 3)
            {
                vertices.push_back(srcVertices[t] + x * 2); // x
                vertices.push_back(srcVertices[t + 1] + height); // y
                vertices.push_back(srcVertices[t + 2] + z * 2); // z
            }
            // Insert uvs
            for (float srcUv : _pCubeMesh->Uvs())
            {
                uvs.push_back(srcUv);
            }
            // Insert normals
            std::vector<GLfloat> srcNormals = _pCubeMesh->Normals();
            for (int t = 0; t < srcNormals.size(); t += 3)
            {
                normals.push_back(srcNormals[t] + x); // x
                normals.push_back(srcNormals[t + 1] + height); // y
                normals.push_back(srcNormals[t + 2] + z); // z
            }
            // Insert indices
            for (int srcIndice : _pCubeMesh->Indices())
            {
                indices.push_back(srcIndice + indiceOffset);
            }
            indiceOffset += srcVertices.size() / 3;
        }
    }

    // then assign mesh
    _pMesh = new Mesh(vertices, uvs, normals, indices);
    _pMesh->SetTexture(_pTexture);
}
