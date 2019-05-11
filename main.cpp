#include "Source/Core/Window.h"
#include "Source/Graphics/Shader/ShaderFactory.h"
#include "Source/Graphics/Mesh/MeshFactory.h"
#include "Source/Core/GameObject.h"
#include "Source/IO/Files.h"
#include "Source/Graphics/Texture/TextureFactory.h"
#include "Source/Graphics/Mesh/Loader/ObjFileLoader.h"
#include "Source/Core/Camera.h"

#define SHADER_NAME "textured"

#define GAMEOBJECTS_COUNT 10

#define PROJECTION_MATRIX_UNIFORM "projectionMatrix"
#define VIEW_MATRIX_UNIFORM "viewMatrix"
#define TEXTURE_SAMPLER_UNIFORM "textureSampler"

#define FOV BaseMath::ToRadians(60.f)
#define Z_NEAR .01f
#define Z_FAR 300.f

#define CAMERA_SPEED 0.01f

Shader* LoadShader()
{
    // Initialize shader
    if (!ShaderFactory::p().Load(SHADER_NAME))
    {
        return nullptr;
    }

    Shader* pShader = &ShaderFactory::p().Get(SHADER_NAME);

    // Set projection matrix uniform
    if (!pShader->CreateUniform(PROJECTION_MATRIX_UNIFORM))
    {
        fprintf(stderr, "Error while creating PROJECTION_MATRIX_UNIFORM");
        return nullptr;
    }
    if (!pShader->CreateUniform(VIEW_MATRIX_UNIFORM))
    {
        fprintf(stderr, "Error while creating uniform");
        return nullptr;
    }
    if (!pShader->CreateUniform(TEXTURE_SAMPLER_UNIFORM))
    {
        fprintf(stderr, "Error while creating uniform TEXTURE_SAMPLER_UNIFORM");
        return nullptr;
    }
    return pShader;
}

Texture* LoadTexture()
{
    if (!TextureFactory::p().Load("Resources/Textures/grassblock.png", "grass"))
    {
        return nullptr;
    }

    return TextureFactory::p().Get("grass");
}

int main()
{
    Logger logger = LoggerFactory::CreateLogger("Main");
    Window window;

    if (!window.Initialize(640, 480, "Hello world ! :D"))
    {
        logger.Error("Unable to initialize window");
        return -1;
    }

    logger.Info("Window initialization successful");

    // Load shader
    Shader* pShader = LoadShader();
    if (pShader == nullptr)
    {
        logger.Error("Unable to load shader");
        return -1;
    }

    // Load texture
    Texture* pTexture = LoadTexture();
    if (pTexture == nullptr)
    {
        fprintf(stderr, "Unable to load texture");
        return -1;
    }

    // Load mesh from file
    if (!MeshFactory::p().LoadMesh("Resources/Models/cube.obj", "cube", pTexture))
    {
        logger.Error("Unable to load mesh");
        return -1;
    }

    Mesh mesh = MeshFactory::p().GetMesh("cube");

    // Create matrices
    Matrix4f projectionMatrix = Matrix4f::CreateProjectionMatrix(FOV, window.Size(), Z_NEAR, Z_FAR);
    Matrix4f modelViewMatrix, viewMatrix;

    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Create camera
    Camera camera(Vector3f(0.f, 5.f, 10.f));

    Vector2d mousePosition = window.GetMousePos();

    // Create gameObjects
    std::vector<GameObject> gameObjects;
    gameObjects.reserve(GAMEOBJECTS_COUNT);
    for (int x = 0; x < GAMEOBJECTS_COUNT/2; x++)
    {
        for (int y = 0; y < GAMEOBJECTS_COUNT/2; y++)
        {
            gameObjects.emplace_back(&mesh);
            gameObjects[gameObjects.size() - 1].Move(x * 2, 0, - y * 2);
        }
    }

    pShader->Bind();
    while (!window.ShouldClose())
    {
        if (window.IsKeyPressed(GLFW_KEY_ESCAPE))
            window.Close();

        // Update position if needed
        if (window.IsKeyPressed(GLFW_KEY_Q))
            camera.Move(-CAMERA_SPEED, 0, 0);
        else if (window.IsKeyPressed(GLFW_KEY_D))
            camera.Move(CAMERA_SPEED, 0, 0);
        else if (window.IsKeyPressed(GLFW_KEY_Z))
            camera.Move(0, 0, -CAMERA_SPEED);
        else if (window.IsKeyPressed(GLFW_KEY_S))
            camera.Move(0, 0, CAMERA_SPEED);
        else if (window.IsKeyPressed(GLFW_KEY_SPACE))
            camera.Move(0, CAMERA_SPEED, 0);
        else if (window.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
            camera.Move(0, -CAMERA_SPEED, 0);

        // Compute mouse movement
        Vector2d newMousePosition = window.GetMousePos();
        Vector2d mouseOffset = (newMousePosition - mousePosition).Normalize();
        mousePosition = newMousePosition;

        if (mouseOffset.y < 0)
            camera.Rotate(-1, 0, 0);
        else if (mouseOffset.y > 0)
            camera.Rotate(1, 0, 0);
        else if (mouseOffset.x < 0)
            camera.Rotate(0, -1, 0);
        else if (mouseOffset.x > 0)
            camera.Rotate(0, 1, 0);

        // Clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update global uniforms
        pShader->SetUniform(PROJECTION_MATRIX_UNIFORM, projectionMatrix);
        pShader->SetUniform(TEXTURE_SAMPLER_UNIFORM, 0);

        // Get camera view matrix
        camera.UpdateViewMatrix(viewMatrix);

        // Draw objects
        for (auto& gameObject : gameObjects)
        {
            pShader->SetUniform(VIEW_MATRIX_UNIFORM, gameObject.GetModelViewMatrix(viewMatrix));
            gameObject.Render();
        }

        // Render whole window to screen
        window.Render();
    }
    pShader->Unbind();

    // Resources cleanup
    glBindVertexArray(0);

    return 0;
}