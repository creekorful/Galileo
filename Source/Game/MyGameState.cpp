#include "MyGameState.h"

MyGameState::MyGameState() : _logger(LoggerFactory::CreateLogger("MyGameState")), _pShader(nullptr),
                             _mousePos(Vector2d())
{
}

bool MyGameState::Initialize(Window& window)
{
    _logger.Debug("Initializing state");

    // Load shader
    if (!ShaderFactory::p().Load(SHADER_NAME))
    {
        _logger.Error("Unable to load shader");
        return false;
    }

    _pShader = &ShaderFactory::p().Get(SHADER_NAME);

    // Set uniforms
    if (!_pShader->CreateUniform(PROJECTION_MATRIX_UNIFORM))
    {
        _logger.Error("Error while creating PROJECTION_MATRIX_UNIFORM");
        return false;
    }
    if (!_pShader->CreateUniform(VIEW_MATRIX_UNIFORM))
    {
        _logger.Error("Error while creating uniform");
        return false;
    }
    if (!_pShader->CreateUniform(TEXTURE_SAMPLER_UNIFORM))
    {
        _logger.Error("Error while creating uniform TEXTURE_SAMPLER_UNIFORM");
        return false;
    }

    // Load texture
    if (!TextureFactory::p().Load("Resources/Textures/grassblock.png", "grass"))
    {
        _logger.Error("Unable to load texture");
        return false;
    }
    Texture* pTexture = TextureFactory::p().Get("grass");

    // Load mesh from file
    if (!MeshFactory::p().LoadMesh("Resources/Models/cube.obj", "cube", pTexture))
    {
        _logger.Error("Unable to load mesh");
        return false;
    }

    Mesh mesh = MeshFactory::p().GetMesh("cube");

    // Create projection matrix
    _projectionMatrix = Matrix4f::CreateProjectionMatrix(FOV, window.Size(), Z_NEAR, Z_FAR);

    // Set clear color
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Create camera and get mouse position
    _camera = Camera(Vector3f(0.f, 5.f, 10.f));
    _mousePos = window.GetMousePos();

    // Finally generate the map
    GenerateMap(mesh);

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
}

void MyGameState::Render()
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

    // Unbind the shader
    _pShader->Unbind();
}

void MyGameState::GenerateMap(Mesh& mesh)
{
    _gameObjects.reserve(MAP_LENGTH * MAP_WIDTH * MAP_HEIGHT);
    for (int x = 0; x < MAP_LENGTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            for (int z = 0; z < MAP_WIDTH; z++)
            {
                float noise = BaseMath::Noise((float) x / 10, (float) y / 10, (float) z / 10);

                if (noise >= 0)
                {
                    _gameObjects.emplace_back(&mesh, x * BLOCK_SIZE, y * BLOCK_SIZE, z * BLOCK_SIZE);
                }
            }
        }
    }
}
