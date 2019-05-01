#include "Source/Graphics/Window.h"
#include "Source/Graphics/Shader.h"
#include "Source/GameObject.h"
#include "Source/IO/Files.h"

#define PROJECTION_MATRIX_UNIFORM "projectionMatrix"
#define VIEW_MATRIX_UNIFORM "viewMatrix"

int main()
{
    // position of the vertices
    std::vector<GLfloat> vertices = {
            // front
            -1.0, -1.0, 1.0,
            1.0, -1.0, 1.0,
            1.0, 1.0, 1.0,
            -1.0, 1.0, 1.0,
            // back
            -1.0, -1.0, -1.0,
            1.0, -1.0, -1.0,
            1.0, 1.0, -1.0,
            -1.0, 1.0, -1.0
    };

    // drawing indices/order of the vertices
    std::vector<GLint> indices = {
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3
    };


    std::string title = "Hello world";
    auto* pWindow = new Window();
    if (!pWindow->Initialize(640, 480, title))
    {
        fprintf(stderr, "Unable to Initialize window");
        return -1;
    }

    fprintf(stdout, "Window initialization successful");

    // Initialize object to be drawn
    auto pMesh = new Mesh(vertices, indices);

    // Initialize shader
    std::string vertexShader = Files::Read("Shaders/vertex.vs");
    std::string fragmentShader = Files::Read("Shaders/fragment.fs");

    // Load shader
    auto pShader = new Shader();
    if (!pShader->Initialize(vertexShader, fragmentShader))
    {
        fprintf(stderr, "Unable to initialise shader");
        return -1;
    }

    // Create gameObjects
    auto pGameObject = new GameObject(pMesh);

    // Create projection matrix
    Vector2i windowSize = pWindow->size();
    double aspectRatio = windowSize.x / windowSize.y;
    Matrix4f projectionMatrix =
            Matrix4f::CreateProjectionMatrix((float) BaseMath::toRadians(60.0f), aspectRatio, 1.f, 1000.0f);
    Matrix4f viewMatrix;

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
    delete pMesh;
    delete pShader;
    delete pWindow;

    return 0;
}