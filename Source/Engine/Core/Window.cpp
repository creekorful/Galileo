#include "Window.h"

Window::Window() : _pWindow(nullptr), _logger(LoggerFactory::CreateLogger("Window"))
{
    // Initialize GLFW
    if (!glfwInit())
    {
        _logger.Error("Unable to initialize GLFW");
    }
}

bool Window::Initialize(Vector2i screenSize, const std::string& title, bool fullscreen)
{
    // Configure OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window and his OpenGL context
    _pWindow = glfwCreateWindow(screenSize.x, screenSize.y, title.c_str(),
                                fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
    if (!_pWindow)
    {
        _logger.Error("Unable to create window");
        glfwTerminate();
        return false;
    }

    // Make window context current
    glfwMakeContextCurrent(_pWindow);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    _logger.Info("Window initialized");

    return true;
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(_pWindow);
}

void Window::Close()
{
    glfwSetWindowShouldClose(_pWindow, GLFW_TRUE);
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

Vector2i Window::Size() const
{
    Vector2i size;
    glfwGetWindowSize(_pWindow, &size.x, &size.y);
    return size;
}

bool Window::IsKeyPressed(GLenum keyCode) const
{
    return glfwGetKey(_pWindow, keyCode) == GLFW_PRESS;
}

Vector2d Window::GetMousePos() const
{
    Vector2d pos;
    glfwGetCursorPos(_pWindow, &pos.x, &pos.y);
    return pos;
}

void Window::SetTitle(const std::string& title)
{
    glfwSetWindowTitle(_pWindow, title.c_str());
}

Vector2i Window::GetDefaultScreenSize()
{
    const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    return Vector2i(videoMode->width, videoMode->height);
}
