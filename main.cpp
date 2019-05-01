#include "Source/Graphics/Window.h"
#include "Source/Graphics/ShaderFactory.h"
#include "Source/Graphics/MeshFactory.h"
#include "Source/GameObject.h"
#include "Source/IO/Files.h"

#define PROJECTION_MATRIX_UNIFORM "projectionMatrix"
#define VIEW_MATRIX_UNIFORM "viewMatrix"

int main()
{
    std::string title = "Hello world";
    auto* pWindow = new Window();
    if (!pWindow->Initialize(640, 480, title))
    {
        fprintf(stderr, "Unable to Initialize window");
        return -1;
    }

    fprintf(stdout, "Window initialization successful");

    // Initialize mesh to be drawn
    Mesh mesh = MeshFactory::BuildPlaneMesh();

    // Create gameObjects
    auto pGameObject = new GameObject(&mesh);

    // Create projection matrix
    Vector2i windowSize = pWindow->size();
    double aspectRatio = windowSize.x / windowSize.y;
    Matrix4f projectionMatrix =
            Matrix4f::CreateProjectionMatrix((float) BaseMath::toRadians(60.0f), aspectRatio, 1.f, 1000.0f);
    Matrix4f viewMatrix;

    // Initialize shader
    Shader* pShader = ShaderFactory::p().Load("simple");
    if (pShader == nullptr)
    {
        return -1;
    }

    // Set projection matrix uniform
    if (!pShader->CreateUniform(PROJECTION_MATRIX_UNIFORM))
    {
        fprintf(stderr, "Error while creating uniform");
    }
    if (!pShader->CreateUniform(VIEW_MATRIX_UNIFORM))
    {
        fprintf(stderr, "Error while creating uniform");
    }

    glClearColor(0.0, 0.0, 0.0, 1.0);

    pShader->Bind();
    while (!pWindow->ShouldClose())
    {
        // Update view matrix
        pGameObject->UpdateViewMatrix(&viewMatrix);

        // Update shader uniforms
        pShader->SetUniform(PROJECTION_MATRIX_UNIFORM, projectionMatrix);
        pShader->SetUniform(VIEW_MATRIX_UNIFORM, viewMatrix);

        // Here draw
        glClear(GL_COLOR_BUFFER_BIT);
        pGameObject->Render();
        pWindow->Render();
    }
    pShader->Unbind();

    // Resources cleanup
    glBindVertexArray(0);

    delete pGameObject;
    delete pWindow;

    return 0;
}