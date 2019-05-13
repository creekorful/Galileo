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
#define Z_FAR 300.f

#define MAP_WIDTH 20
#define MAP_LENGTH 20
#define MAP_HEIGHT 20
#define BLOCK_SIZE 2

#define CAMERA_SPEED 0.05f

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

    Matrix4f _projectionMatrix;
    Matrix4f _viewMatrix;

    Camera _camera;
    Vector2d _mousePos;

    std::vector<GameObject> _gameObjects;

    void GenerateMap(Mesh& mesh);
};


#endif //GALILEO_MYGAMESTATE_H
