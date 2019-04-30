#include "Source/Graphics/Window.h"
#include "Source/Graphics/Mesh.h"
#include "Source/Graphics/Shader.h"
#include "Source/IO/Files.h"

int main()
{
    // position of the vertices
    auto vertices = new GLfloat *[4];
    vertices[0] = new GLfloat[3]{0.0, 0.0, 0.0};
    vertices[1] = new GLfloat[3]{0.0, 1.0, 0.0};
    vertices[2] = new GLfloat[3]{1.0, 0.0, 0.0};
    vertices[3] = new GLfloat[3]{1.0, 1.0, 0.0};

    // drawing indices of the vertices
    auto indices = new GLint[7]{3, 0, 1, 3, 2, 0, 3};


    std::string title = "Hello world";
    auto *pWindow = new Window();
    if (!pWindow->Initialize(650, 480, title))
    {
        fprintf(stderr, "Unable to Initialize window");
        return -1;
    }

    fprintf(stdout, "Window initialization successful");

    // Initialize object to be drawn
    auto pMesh = new Mesh(vertices, indices, 7);

    // Initialize shader
    std::string vertexShader = Files::Read("Shaders/vertex.vs");
    std::string fragmentShader = Files::Read("Shaders/fragment.fs");

    auto pShader = new Shader();
    if (!pShader->Initialize(vertexShader, fragmentShader))
    {
        fprintf(stderr, "Unable to initialise shader");
        return -1;
    }

    glClearColor(0.0, 0.0, 0.0, 1.0);

    pShader->Bind();
    while (!pWindow->ShouldClose())
    {
        // Here draw
        glClear(GL_COLOR_BUFFER_BIT);
        pMesh->Draw();
        pWindow->Render();
    }
    pShader->Unbind();

    // Resources cleanup
    glBindVertexArray(0);

    delete pMesh;
    delete pShader;
    delete pWindow;

    return 0;
}