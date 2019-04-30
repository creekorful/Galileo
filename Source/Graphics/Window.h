#ifndef GALILEO_WINDOW_H
#define GALILEO_WINDOW_H

#include <iostream>

#include "../Common.h"
#include "../Math/Vector2i.h"

/**
 * This class represent the active render window
 * used to wrap OpenGL initialization and stuff
 */
class Window
{
public:

    virtual ~Window();

    /**
     * Initialize the GLFW window and OpenGL context
     *
     * @param width window width
     * @param height window height
     * @param title window title
     * @return true if initialization successful false otherwise
     */
    bool Initialize(int width, int height, std::string &title);

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
    Vector2i size();

private:
    GLFWwindow *_pWindow;
};


#endif //GALILEO_WINDOW_H
