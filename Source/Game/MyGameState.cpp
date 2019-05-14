#include "MyGameState.h"
#include "CameraController.h"

MyGameState::MyGameState() : _logger(LoggerFactory::CreateLogger("MyGameState")), _pShader(nullptr), _pCubeMesh(nullptr)
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
    _camera.AddComponent(new CameraController());

    return true;
}

void MyGameState::Update(Window& window, float dt)
{
    if (window.IsKeyPressed(GLFW_KEY_ESCAPE))
    {
        window.Close();
    }

    // Update camera
    _camera.Update(window, dt);

    // Update projection matrix
    _projectionMatrix = Matrix4f::CreateProjectionMatrix(FOV, window.Size(), Z_NEAR, Z_FAR);

    Vector2i cameraChunkPos = GetCameraChunkPos();

    // Manage chunks to be drawn
    _activeChunkPos.clear();
    for (int x = 0; x < VIEW_DISTANCE; x++)
    {
        for (int z = 0; z < VIEW_DISTANCE; z++)
        {
            Vector2i topLeftChunkPos = cameraChunkPos + Vector2i(-x, z);
            Vector2i topRightChunkPos = cameraChunkPos + Vector2i(x, z);
            Vector2i bottomLeftChunkPos = cameraChunkPos - Vector2i(-x, z);
            Vector2i bottomRightChunkPos = cameraChunkPos - Vector2i(x, z);

            // Chunk not present : generate new ones
            if (_chunks.find(topLeftChunkPos) == _chunks.end())
                GenerateChunk(topLeftChunkPos);
            if (_chunks.find(topRightChunkPos) == _chunks.end())
                GenerateChunk(topRightChunkPos);
            if (_chunks.find(bottomLeftChunkPos) == _chunks.end())
                GenerateChunk(bottomLeftChunkPos);
            if (_chunks.find(bottomRightChunkPos) == _chunks.end())
                GenerateChunk(bottomRightChunkPos);

            // From now on we know that the chunk is present
            _activeChunkPos.push_back(topLeftChunkPos);
            _activeChunkPos.push_back(topRightChunkPos);
            _activeChunkPos.push_back(bottomLeftChunkPos);
            _activeChunkPos.push_back(bottomRightChunkPos);
        }
    }

    // Update them
    for (auto& chunkPos : _activeChunkPos)
    {
        for (auto& block : _chunks[chunkPos])
        {
            block.Update(window, dt);
        }
    }
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

    // Finally draw them
    for (auto& chunkPos : _activeChunkPos)
    {
        for (auto& block : _chunks[chunkPos])
        {
           if (ShouldRender(block, BLOCK_SIZE))
           {
               _pShader->SetUniform(VIEW_MATRIX_UNIFORM, block.GetModelViewMatrix(_viewMatrix));
               block.Render();
           }
        }
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

Vector2i MyGameState::GetCameraChunkPos() const
{
    // todo offset to make change at middle of chunk? or offset in calling method
    return Vector2i(_camera.Position().x / CHUNK_LENGTH, _camera.Position().z / CHUNK_WIDTH);
}

bool MyGameState::ShouldRender(GameObject& gameObject, float size) const
{
    return true;
}
