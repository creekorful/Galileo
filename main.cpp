#include "Source/Graphics/Window.h"
#include "Source/Graphics/Shader/ShaderFactory.h"
#include "Source/Graphics/Mesh/MeshFactory.h"
#include "Source/GameObject.h"
#include "Source/IO/Files.h"
#include "Source/Graphics/Texture/TextureFactory.h"

#define SHADER_NAME "textured"

#define PROJECTION_MATRIX_UNIFORM "projectionMatrix"
#define VIEW_MATRIX_UNIFORM "viewMatrix"
#define TEXTURE_SAMPLER_UNIFORM "textureSampler"

#define FOV BaseMath::toRadians(60.f)
#define Z_NEAR .01f
#define Z_FAR 100.f

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

    return &TextureFactory::p().Get("grass");
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

    // Initialize mesh to be drawn
    Mesh mesh = MeshFactory::BuildCubeMesh();

    // Create matrices
    Matrix4f projectionMatrix = Matrix4f::CreateProjectionMatrix(FOV, window.Size(), Z_NEAR, Z_FAR);

    Matrix4f viewMatrix;

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

    // Set textures to object
    std::vector<GLfloat> uvs = {
            0.0f, 0.0f,
            0.0f, 0.5f,
            0.5f, 0.5f,
            0.5f, 0.0f,
            0.0f, 0.0f,
            0.5f, 0.0f,
            0.0f, 0.5f,
            0.5f, 0.5f,
            // For text coords in top face
            0.0f, 0.5f,
            0.5f, 0.5f,
            0.0f, 1.0f,
            0.5f, 1.0f,
            // For text coords in right face
            0.0f, 0.0f,
            0.0f, 0.5f,
            // For text coords in left face
            0.5f, 0.0f,
            0.5f, 0.5f,
            // For text coords in bottom face
            0.5f, 0.0f,
            1.0f, 0.0f,
            0.5f, 0.5f,
            1.0f, 0.5f
    };
    mesh.SetTexture(uvs, pTexture);

    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Create gameObjects
    GameObject firstGameObject(&mesh), secondGameObject(&mesh);

    // Move objects
    firstGameObject.Move(Vector3f(0, 0, -2.f));
    firstGameObject.Scale(0.2f);

    secondGameObject.Move(Vector3f(-2.f, 0, -7.f));

    pShader->Bind();
    while (!window.ShouldClose())
    {
        // Clear + set window to polygon mode
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update global uniforms
        pShader->SetUniform(PROJECTION_MATRIX_UNIFORM, projectionMatrix);
        pShader->SetUniform(TEXTURE_SAMPLER_UNIFORM, 0);

        // Draw first object
        firstGameObject.Rotate(Vector3f(.05f, .05f, 0));
        firstGameObject.UpdateViewMatrix(viewMatrix);
        pShader->SetUniform(VIEW_MATRIX_UNIFORM, viewMatrix);
        firstGameObject.Render();

        // Draw second object
        secondGameObject.Rotate(Vector3f(0, .06f, 0.4f));
        secondGameObject.UpdateViewMatrix(viewMatrix);
        pShader->SetUniform(VIEW_MATRIX_UNIFORM, viewMatrix);
        secondGameObject.Render();

        // Render whole window to screen
        window.Render();
    }
    pShader->Unbind();

    // Resources cleanup
    glBindVertexArray(0);

    return 0;
}