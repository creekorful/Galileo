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
    _pMesh = nullptr;

    _vertices.clear();
    _uvs.clear();
    _normals.clear();
    _indices.clear();

    int indiceOffset = 0;

    // todo discard blocks that are hidden( not visible at all)
    // todo discard block common face

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            // compute height at given pos
            float height = _rawBlocks[x * CHUNK_SIZE + z];

            for (int y = 0; y < 2; y++) // todo CHUNK_SIZE INSTEAD
            {
                // Insert vertices
                std::vector<GLfloat> srcVertices = _pCubeMesh->Vertices();
                for (int t = 0; t < srcVertices.size(); t += 3)
                {
                    _vertices.push_back(srcVertices[t] + x * BLOCK_SIZE); // x
                    _vertices.push_back(srcVertices[t + 1] + height - y * BLOCK_SIZE); // y
                    _vertices.push_back(srcVertices[t + 2] + z * BLOCK_SIZE); // z
                }
                // Insert uvs
                for (float srcUv : _pCubeMesh->Uvs())
                {
                    _uvs.push_back(srcUv);
                }
                // Insert normals
                std::vector<GLfloat> srcNormals = _pCubeMesh->Normals();
                for (int t = 0; t < srcNormals.size(); t += 3)
                {
                    _normals.push_back(srcNormals[t] + x); // x
                    _normals.push_back(srcNormals[t + 1] + height - y * BLOCK_SIZE); // y
                    _normals.push_back(srcNormals[t + 2] + z); // z
                }
                // Insert indices
                for (int srcIndice : _pCubeMesh->Indices())
                {
                    _indices.push_back(srcIndice + indiceOffset);
                }
                indiceOffset += srcVertices.size() / 3;
            }
        }
    }
}

void Chunk::BuildMesh()
{
    _pMesh = new Mesh(_vertices, _uvs, _normals, _indices);
    _pMesh->SetTexture(_pTexture);
}

bool Chunk::IsBuilt() const
{
    return _pMesh != nullptr;
}
