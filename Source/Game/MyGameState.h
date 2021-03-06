#ifndef GALILEO_MYGAMESTATE_H
#define GALILEO_MYGAMESTATE_H

#include <thread>

#include "../Engine/Core/Engine/GameState.h"
#include "../Engine/Graphics/Shader/ShaderFactory.h"
#include "../Engine/Graphics/Texture/TextureFactory.h"
#include "../Engine/Graphics/Mesh/MeshFactory.h"
#include "../Engine/Core/Object/Camera.h"
#include "../Engine/Core/Object/GameObject.h"
#include "Chunk.h"

#define SHADER_NAME "textured"
#define PROJECTION_MATRIX_UNIFORM "projectionMatrix"
#define VIEW_MATRIX_UNIFORM "viewMatrix"
#define TEXTURE_SAMPLER_UNIFORM "textureSampler"

#define FOV BaseMath::ToRadians(60.f)
#define Z_NEAR .01f
#define Z_FAR 600.f

#define VIEW_DISTANCE 10
#define PRELOAD_DISTANCE 20

#define HEIGHT_SCALE 25

struct VectorCompare
{
    bool operator() (const Vector2i& lhs, const Vector2i& rhs) const
    {
        if (lhs.x < rhs.x)
            return true;
        if (lhs.x > rhs.x)
            return false;

        if (lhs.y < rhs.y)
            return true;
        if (lhs.y > rhs.y)
            return false;

        return false;
    }
};

class MyGameState : public GameState
{
public:
    MyGameState();

    ~MyGameState() override;

    bool Initialize(Window& window) override;

    void Update(Window& window, float dt) override;

    void Render() override;

private:
    Logger _logger;
    Shader* _pShader;

    Mesh* _pCubeMesh;
    Texture* _pTexture;

    Matrix4f _projectionMatrix;
    Matrix4f _viewMatrix;

    Camera _camera;

    std::map<Vector2i, Chunk, VectorCompare> _chunks;
    std::vector<Vector2i> _activeChunkPos;
    std::thread _generateChunkThread;
    std::atomic<bool> _continueGeneration;

    /**
     * Generate and store chunk at given position
     *
     * @param position chunk coordinate position
     */
    void GenerateChunk(const Vector2i& position);

    /**
     * @return camera chunk location
     */
    Vector2i GetCameraChunkPos() const;

    /**
     * Method called in thread responsible of background chunk generation
     */
    void GenerateChunkThread();
};


#endif //GALILEO_MYGAMESTATE_H
