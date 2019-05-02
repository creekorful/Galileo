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

    // Create gameObject
    GameObject gameObject(&mesh);

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

    //gameObject.Scale(2.f);
    //gameObject.Rotate(Vector3f(0.f, 0.f, 45.f));
    gameObject.Move(Vector3f(0, 0, -2.f));

    pShader->Bind();
    while (!window.ShouldClose())
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        gameObject.Rotate(Vector3f(.05f, .05f, 0));

        // Update view matrix
        gameObject.UpdateViewMatrix(viewMatrix);
        /*std::cout << "viewMatrix =" << std::endl;
        viewMatrix.Dump();*/

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