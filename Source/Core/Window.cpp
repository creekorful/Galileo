#include "Window.h"

Window::Window() : _pWindow(nullptr), _logger(LoggerFactory::CreateLogger("Window"))
{
}

bool Window::Initialize(int width, int height, const std::string& title)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        _logger.Error("Unable to initialize GLFW");
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
        _logger.Error("Unable to create window");
        glfwTerminate();
        return false;
    }

    // Make window context current
    glfwMakeContextCurrent(_pWindow);

    glEnable(GL_DEPTH_TEST);

    _logger.Info("Window initialized");

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

bool Window::IsKeyPressed(GLenum keyCode)
{
    return glfwGetKey(_pWindow, keyCode) == GLFW_PRESS;
}

Vector2d Window::GetMousePos()
{
    Vector2d pos;
    glfwGetCursorPos(_pWindow, &pos.x, &pos.y);
    return pos;
}

void Window::SetTitle(const std::string& title)
{
    glfwSetWindowTitle(_pWindow, title.c_str());
}
