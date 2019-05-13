#include "MyGameState.h"
#include "KeyboardController.h"

MyGameState::MyGameState() : _logger(LoggerFactory::CreateLogger("MyGameState")), _pShader(nullptr)
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
    _pCubeMesh = MeshFactory::p().Load("Resources/Models/cube.obj", "cube");
    if (_pCubeMesh == nullptr)
    {
        _logger.Error("Unable to load mesh");
        return false;
    }

    // Setup linked texture
    _pCubeMesh->SetTexture(pTexture);

    // Create projection matrix
    _projectionMatrix = Matrix4f::CreateProjectionMatrix(FOV, window.Size(), Z_NEAR, Z_FAR);

    // Set clear color
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Create camera
    _camera = Camera(Vector3f(0.f, 5.f, 10.f));
    _camera.AddComponent(new KeyboardController());

    // Finally generate initial chunks
    for (int x = 0; x < 3; x++)
    {
        for (int z = 0; z < 3; z++)
        {
            GenerateChunk(Vector2i(x, z));
        }
    }

    return true;
}

void MyGameState::Update(Window& window, float dt)
{
    if (window.IsKeyPressed(GLFW_KEY_ESCAPE))
    {
        window.Close();
    }

/*    // Update game objects
    for (auto gameObject : _gameObjects)
    {
        gameObject.Update(window, dt);
    }*/

    // Update camera
    _camera.Update(window, dt);

    // Update projection matrix
    _projectionMatrix = Matrix4f::CreateProjectionMatrix(FOV, window.Size(), Z_NEAR, Z_FAR);
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

    // Draw active chunk
    for (auto& block : _chunks[Vector2i(0, 0)])
    {
        _pShader->SetUniform(VIEW_MATRIX_UNIFORM, block.GetModelViewMatrix(_viewMatrix));
        block.Render();
    }

    for (auto& block : _chunks[Vector2i(0, 1)])
    {
        _pShader->SetUniform(VIEW_MATRIX_UNIFORM, block.GetModelViewMatrix(_viewMatrix));
        block.Render();
    }

    for (auto& block : _chunks[Vector2i(0, 2)])
    {
        _pShader->SetUniform(VIEW_MATRIX_UNIFORM, block.GetModelViewMatrix(_viewMatrix));
        block.Render();
    }

    // Unbind the shader
    _pShader->Unbind();
}

void MyGameState::GenerateChunk(const Vector2i& position)
{
    _logger.Debug("Generate chunk at x:" + std::to_string(position.x) + " y:" + std::to_string(position.y));

    std::vector<GameObject>& chunk = _chunks[position];

    chunk.reserve(CHUNK_LENGTH * CHUNK_WIDTH);
    for (int x = 0; x < CHUNK_LENGTH; x++)
    {
        for (int z = 0; z < CHUNK_WIDTH; z++)
        {
            int worldPosX = (position.x * CHUNK_LENGTH) + (x * BLOCK_SIZE);
            int worldPosZ = (position.y * CHUNK_WIDTH) + (z * BLOCK_SIZE);

            float noise = BaseMath::Noise((float) worldPosX / HEIGHT_SCALE, (float) worldPosZ / HEIGHT_SCALE);
            int height = ((int) (noise * 10) * BLOCK_SIZE);

            chunk.emplace_back(_pCubeMesh, worldPosX, height, worldPosZ);
        }
    }
}
