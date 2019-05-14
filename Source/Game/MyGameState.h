#ifndef GALILEO_MYGAMESTATE_H
#define GALILEO_MYGAMESTATE_H

#include "../Engine/Core/GameState.h"
#include "../Engine/Graphics/Shader/ShaderFactory.h"
#include "../Engine/Graphics/Texture/TextureFactory.h"
#include "../Engine/Graphics/Mesh/MeshFactory.h"
#include "../Engine/Core/Camera.h"
#include "../Engine/Core/GameObject.h"

#define SHADER_NAME "textured"
#define PROJECTION_MATRIX_UNIFORM "projectionMatrix"
#define VIEW_MATRIX_UNIFORM "viewMatrix"
#define TEXTURE_SAMPLER_UNIFORM "textureSampler"

#define FOV BaseMath::ToRadians(60.f)
#define Z_NEAR .01f
#define Z_FAR 600.f

#define CHUNK_WIDTH 16
#define CHUNK_LENGTH 16
#define VIEW_DISTANCE 5

#define HEIGHT_SCALE 20

#define BLOCK_SIZE 2

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

    Matrix4f _projectionMatrix;
    Matrix4f _viewMatrix;

    Camera _camera;

    std::map<Vector2i, std::vector<GameObject>, VectorCompare> _chunks;

    std::vector<Vector2i> _activeChunkPos;

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

    // todo : force inline?
    bool ShouldRender(GameObject& gameObject, float size) const;
};


#endif //GALILEO_MYGAMESTATE_H
