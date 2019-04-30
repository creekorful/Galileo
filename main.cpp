#include <iostream>

#include <GLFW/glfw3.h>

int main()
{
    GLFWwindow *pWindow;

    // Initialize GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Unable to initialize GLFW");
        return -1;
    }

    // Create the window and his OpenGL context
    pWindow = glfwCreateWindow(640, 480, "Hello world", nullptr, nullptr);
    if (!pWindow)
    {
        fprintf(stderr, "Unable to create window");
        glfwTerminate();
        return -1;
    }

    // Make window context current
    glfwMakeContextCurrent(pWindow);

    while (!glfwWindowShouldClose(pWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}