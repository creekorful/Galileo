#include "Source/Graphics/Window.h"
#include "Source/Graphics/ShaderFactory.h"
#include "Source/Graphics/MeshFactory.h"
#include "Source/GameObject.h"
#include "Source/IO/Files.h"

#define PROJECTION_MATRIX_UNIFORM "projectionMatrix"
#define VIEW_MATRIX_UNIFORM "viewMatrix"

Shader* LoadShader()
{
    // Initialize shader
    Shader* pShader = ShaderFactory::p().Load("simple");
    if (pShader == nullptr)
    {
        return nullptr;
    }

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
    Mesh mesh = MeshFactory::BuildPlaneMesh();

    // Create gameObject
    GameObject gameObject(&mesh);

    // Create matrices
    float fov = BaseMath::toRadians(60.f);
    Matrix4f projectionMatrix = Matrix4f::CreateProjectionMatrix(fov, window.Size(), .01f, 1000.0f);
    Matrix4f viewMatrix;

    Shader* pShader = LoadShader();
    if (pShader == nullptr)
    {
        fprintf(stderr, "Unable to load shader");
        return -1;
    }

    glClearColor(0.0, 0.0, 0.0, 1.0);

    //gameObject.Move(Vector3f(0, 0, -200.f));

    pShader->Bind();
    while (!window.ShouldClose())
    {
        gameObject.Move(Vector3f(0, 0, -0.02f));
        // Update view matrix
        gameObject.UpdateViewMatrix(&viewMatrix);

        // Update shader uniforms
        pShader->SetUniform(PROJECTION_MATRIX_UNIFORM, projectionMatrix);
        pShader->SetUniform(VIEW_MATRIX_UNIFORM, viewMatrix);

        // Here draw
        glClear(GL_COLOR_BUFFER_BIT);
        gameObject.Render();
        window.Render();
    }
    pShader->Unbind();

    // Resources cleanup
    glBindVertexArray(0);

    return 0;
}