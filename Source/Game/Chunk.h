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

    /**
     * Build the actual mesh
     * should be called ONLY from render thread
     */
    void BuildMesh();

    /**
     * Determinate if the mesh need to be build / instantiated
     * this will NOT generate the mesh only built it
     *
     * @return true if mesh is not instantiated / builded
     */
    bool IsBuilt() const;

private:
    std::vector<float> _rawBlocks;
    Mesh *_pCubeMesh;
    Texture* _pTexture;

    std::vector<GLfloat> _vertices;
    std::vector<GLfloat> _uvs;
    std::vector<GLfloat> _normals;
    std::vector<GLint> _indices;

    /**
     * Generate/fill the vertices/uvs/normals/indices array by merging all cube in mesh together
     * this does NOT generate the actual mesh since this method can be called in background thread
     * and mesh generation need to be in rendering thread
     */
    void GenerateMesh();
};


#endif //GALILEO_CHUNK_H
