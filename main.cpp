#include "Source/Graphics/Core/Window.h"
#include "Source/Graphics/Shader/ShaderFactory.h"
#include "Source/Graphics/Mesh/MeshFactory.h"
#include "Source/GameObject.h"
#include "Source/IO/Files.h"
#include "Source/Graphics/Texture/TextureFactory.h"
#include "Source/Graphics/Core/Camera.h"
#include "Source/Graphics/Mesh/Loader/ObjFileLoader.h"

#define SHADER_NAME "textured"

#define PROJECTION_MATRIX_UNIFORM "projectionMatrix"
#define VIEW_MATRIX_UNIFORM "viewMatrix"
#define TEXTURE_SAMPLER_UNIFORM "textureSampler"

#define FOV BaseMath::toRadians(60.f)
#define Z_NEAR .01f
#define Z_FAR 1000.f

#define CAMERA_SPEED 0.005f

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
    if (!TextureFactory::p().Load("Textures/grassblock.png", "grass"))
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

    ObjFileLoader loader("Models/cube.obj");
    Mesh mesh = loader.ReadMesh(pTexture);

    return 0;

    // Create matrices
    Matrix4f projectionMatrix = Matrix4f::CreateProjectionMatrix(FOV, window.Size(), Z_NEAR, Z_FAR);
    Matrix4f modelViewMatrix, viewMatrix;

    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Create camera
    Camera camera;

    // Create gameObjects
    GameObject firstGameObject(&mesh), secondGameObject(&mesh), thirdGameObject(&mesh);

    // Move objects
    firstGameObject.Move(Vector3f(0, 0, -7.f));
    firstGameObject.Scale(2.f);

    secondGameObject.Move(Vector3f(-2.f, 0, -7.f));
    thirdGameObject.Move(Vector3f(-4.f, 0, -10.f));

    pShader->Bind();
    while (!window.ShouldClose())
    {
        // Update position if needed
        if (window.IsKeyPressed(GLFW_KEY_Q))
            camera.Move(-CAMERA_SPEED, 0, 0);
        else if (window.IsKeyPressed(GLFW_KEY_D))
            camera.Move(CAMERA_SPEED, 0, 0);
        else if (window.IsKeyPressed(GLFW_KEY_Z))
            camera.Move(0, 0, CAMERA_SPEED);
        else if (window.IsKeyPressed(GLFW_KEY_S))
            camera.Move(0, 0, -CAMERA_SPEED);
        else if (window.IsKeyPressed(GLFW_KEY_SPACE))
            camera.Move(0, CAMERA_SPEED, 0);
        else if (window.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
            camera.Move(0, -CAMERA_SPEED, 0);

        // Clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update global uniforms
        pShader->SetUniform(PROJECTION_MATRIX_UNIFORM, projectionMatrix);
        pShader->SetUniform(TEXTURE_SAMPLER_UNIFORM, 0);

        // Get camera view matrix
        camera.UpdateViewMatrix(viewMatrix);

        // Draw first object
        firstGameObject.Rotate(Vector3f(.05f, 0, 0));
        modelViewMatrix = firstGameObject.GetModelViewMatrix(viewMatrix);
        pShader->SetUniform(VIEW_MATRIX_UNIFORM, modelViewMatrix);
        firstGameObject.Render();

        // Draw second object
        secondGameObject.Rotate(Vector3f(0, .06f, 0.4f));
        modelViewMatrix = secondGameObject.GetModelViewMatrix(viewMatrix);
        pShader->SetUniform(VIEW_MATRIX_UNIFORM, modelViewMatrix);
        secondGameObject.Render();

        // Draw third object
        modelViewMatrix = thirdGameObject.GetModelViewMatrix(viewMatrix);
        pShader->SetUniform(VIEW_MATRIX_UNIFORM, modelViewMatrix);
        thirdGameObject.Render();

        // Render whole window to screen
        window.Render();
    }
    pShader->Unbind();

    // Resources cleanup
    glBindVertexArray(0);

    return 0;
}