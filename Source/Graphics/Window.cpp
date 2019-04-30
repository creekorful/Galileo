#include <utility>

#include "Window.h"

bool Window::initialize(int width, int height, std::string &title)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Unable to initialize GLFW");
        return false;
    }

    // Configure OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window and his OpenGL context
    _pWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!_pWindow)
    {
        fprintf(stderr, "Unable to create window");
        glfwTerminate();
        return false;
    }

    // Make window context current
    glfwMakeContextCurrent(_pWindow);
    return true;
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(_pWindow);
}

void Window::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(_pWindow);
    glfwPollEvents();
}

void Window::close()
{
    glfwTerminate();
}
