#include "Source/Graphics/Window.h"
#include "Source/Graphics/ShaderFactory.h"
#include "Source/Graphics/MeshFactory.h"
#include "Source/GameObject.h"
#include "Source/IO/Files.h"

#define PROJECTION_MATRIX_UNIFORM "projectionMatrix"
#define VIEW_MATRIX_UNIFORM "viewMatrix"

#define FOV BaseMath::toRadians(60.f)
#define Z_NEAR .01f
#define Z_FAR 100.f

Shader* LoadShader()
{
    // Initialize shader
    if (!ShaderFactory::p().Load("simple"))
    {
        return nullptr;
    }

    Shader* pShader = &ShaderFactory::p().Get("simple");

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
    return pShader;
}

int main()
{
    Window window;
    if (!window.Initialize(640, 480, "Hello world ! :D"))
    {
        fprintf(stderr, "Unable to Initialize window");
        return -1;
    }

    fprintf(stdout, "Window initialization successful");

    // Initialize mesh to be drawn
    Mesh mesh = MeshFactory::BuildCubeMesh();

    // Create gameObjects
    GameObject firstGameObject(&mesh), secondGameObject(&mesh);

    // Create matrices
    Matrix4f projectionMatrix = Matrix4f::CreateProjectionMatrix(FOV, window.Size(), Z_NEAR, Z_FAR);

    Matrix4f viewMatrix;

    Shader* pShader = LoadShader();
    if (pShader == nullptr)
    {
        fprintf(stderr, "Unable to load shader");
        return -1;
    }

    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Move objects
    firstGameObject.Move(Vector3f(0, 0, -2.f));
    firstGameObject.Scale(0.2f);

    secondGameObject.Move(Vector3f(-2.f, 0, -7.f));

    pShader->Bind();
    while (!window.ShouldClose())
    {
        // Clear + set window to polygon mode
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update global projection matrix
        pShader->SetUniform(PROJECTION_MATRIX_UNIFORM, projectionMatrix);

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