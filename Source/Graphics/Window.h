#ifndef GALILEO_WINDOW_H
#define GALILEO_WINDOW_H

#include <iostream>

#include "../Common.h"
#include "../Math/Vector2.h"

/**
 * This class represent the active render window
 * used to wrap OpenGL initialization and stuff
 */
class Window
{
public:

    Window();

    virtual ~Window();

    /**
     * Initialize the GLFW window and OpenGL context
     *
     * @param width window width
     * @param height window height
     * @param title window title
     * @return true if initialization successful false otherwise
     */
    bool Initialize(int width, int height, const std::string& title);

    /**
     * @return true if window should be closed
     */
    bool ShouldClose();

    /**
     * Render / update the window
     */
    void Render();

    /**
     * @return size of current window
     */
    Vector2i Size();

private:
    GLFWwindow* _pWindow;
    Logger _logger;
};


#endif //GALILEO_WINDOW_H
