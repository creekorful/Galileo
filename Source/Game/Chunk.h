#ifndef GALILEO_CHUNK_H
#define GALILEO_CHUNK_H

#define CHUNK_SIZE 16
#define BLOCK_SIZE 2

#include <vector>
#include "../Engine/Graphics/Mesh/Mesh.h"
#include "../Engine/Core/Object/GameObject.h"

class Chunk : public GameObject
{
public:
    Chunk(std::vector<float>& rawBlocks, const Vector3f& worldPos, Mesh* pCubeMesh, Texture* pTexture);

private:
    std::vector<float> _rawBlocks;
    Mesh *_pCubeMesh;
    Texture* _pTexture;

    void GenerateMesh();
};


#endif //GALILEO_CHUNK_H
