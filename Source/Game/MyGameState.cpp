#include "MyGameState.h"

MyGameState::MyGameState() : _logger(LoggerFactory::CreateLogger("MyGameState")), _pShader(nullptr),
                             _mousePos(Vector2d())
{
}

MyGameState::~MyGameState() = default;

bool MyGameState::Initialize(Window& window)
{
    _logger.Debug("Initializing state");

    // Load shader
    _pShader = ShaderFactory::p().Load(SHADER_NAME);
    if (_pShader == nullptr)
    {
        _logger.Error("Unable to load shader");
        return false;
    }

    // Create uniforms
    if (!_pShader->CreateUniforms({PROJECTION_MATRIX_UNIFORM, VIEW_MATRIX_UNIFORM, TEXTURE_SAMPLER_UNIFORM}))
    {
        _logger.Error("Error while creating one of the required uniform");
        return false;
    }

    // Load texture
    Texture* pTexture = TextureFactory::p().Load("Resources/Textures/grassblock.png", "grass");
    if (pTexture == nullptr)
    {
        _logger.Error("Unable to load texture");
        return false;
    }

    // Load mesh from file
    Mesh* pMesh = MeshFactory::p().Load("Resources/Models/cube.obj", "cube");
    if (pMesh == nullptr)
    {
        _logger.Error("Unable to load mesh");
        return false;
    }

    // Create projection matrix
    _projectionMatrix = Matrix4f::CreateProjectionMatrix(FOV, window.Size(), Z_NEAR, Z_FAR);

    // Set clear color
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Create camera and get mouse position
    _camera = Camera(Vector3f(0.f, 5.f, 10.f));
    _mousePos = window.GetMousePos();

    // Finally generate the map
    GenerateMap(pMesh, pTexture);

    return true;
}

void MyGameState::Update(Window& window, float dt)
{
    if (window.IsKeyPressed(GLFW_KEY_ESCAPE))
        window.Close();

    // Update position if needed
    if (window.IsKeyPressed(GLFW_KEY_Q))
        _camera.Move(-CAMERA_SPEED, 0, 0);
    else if (window.IsKeyPressed(GLFW_KEY_D))
        _camera.Move(CAMERA_SPEED, 0, 0);
    else if (window.IsKeyPressed(GLFW_KEY_Z))
        _camera.Move(0, 0, -CAMERA_SPEED);
    else if (window.IsKeyPressed(GLFW_KEY_S))
        _camera.Move(0, 0, CAMERA_SPEED);
    else if (window.IsKeyPressed(GLFW_KEY_SPACE))
        _camera.Move(0, CAMERA_SPEED, 0);
    else if (window.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
        _camera.Move(0, -CAMERA_SPEED, 0);

    // Compute mouse movement
    Vector2d newMousePosition = window.GetMousePos();
    Vector2d mouseOffset = (newMousePosition - _mousePos).Normalize();
    _mousePos = newMousePosition;

    // Update camera rotation based on mouse
    if (mouseOffset.y < 0)
        _camera.Rotate(-1, 0, 0);
    else if (mouseOffset.y > 0)
        _camera.Rotate(1, 0, 0);
    else if (mouseOffset.x < 0)
        _camera.Rotate(0, -1, 0);
    else if (mouseOffset.x > 0)
        _camera.Rotate(0, 1, 0);

    // Update projection matrix
    _projectionMatrix = Matrix4f::CreateProjectionMatrix(FOV, window.Size(), Z_NEAR, Z_FAR);
}

void MyGameState::Render(Window& window)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Bind shader for drawing
    _pShader->Bind();

    // Update global uniform
    _pShader->SetUniform(PROJECTION_MATRIX_UNIFORM, _projectionMatrix);
    _pShader->SetUniform(TEXTURE_SAMPLER_UNIFORM, 0);

    // Get camera view matrix
    _camera.UpdateViewMatrix(_viewMatrix);

    // Draw objects
    for (auto& gameObject : _gameObjects)
    {
        _pShader->SetUniform(VIEW_MATRIX_UNIFORM, gameObject.GetModelViewMatrix(_viewMatrix));
        gameObject.Render();
    }

    //window.Render();

    // Unbind the shader
    _pShader->Unbind();
}

void MyGameState::GenerateMap(Mesh* mesh, Texture* pTexture)
{
    _gameObjects.reserve(MAP_LENGTH * MAP_WIDTH);
    for (int x = 0; x < MAP_LENGTH; x++)
    {
        for (int z = 0; z < MAP_WIDTH; z++)
        {
            float noise = BaseMath::Noise((float) x / 10, (float) z / 10);
            int height = ((int) (noise * 10) * BLOCK_SIZE) + 10;
            _gameObjects.emplace_back(mesh, pTexture, x * BLOCK_SIZE, height, z * BLOCK_SIZE);
        }
    }
}
