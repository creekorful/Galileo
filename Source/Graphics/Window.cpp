#include "Window.h"

bool Window::Initialize(int width, int height, const std::string& title)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Unable to Initialize GLFW");
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

    // Enable special options
    glEnable(GL_DEPTH_TEST);

    // Make window context current
    glfwMakeContextCurrent(_pWindow);

    return true;
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(_pWindow);
}

void Window::Render()
{
    glfwSwapBuffers(_pWindow);
    glfwPollEvents();
}

Window::~Window()
{
    glfwTerminate();
}

Vector2i Window::Size()
{
    Vector2i size;
    glfwGetWindowSize(_pWindow, &size.x, &size.y);
    return size;
}
