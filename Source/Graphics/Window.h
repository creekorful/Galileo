#ifndef GALILEO_WINDOW_H
#define GALILEO_WINDOW_H

#include <iostream>

#include "../Common.h"

/**
 * This class represent the active render window
 * used to wrap OpenGL initialization and stuff
 */
class Window
{
public:

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
     * Gracefully close the window
     */
    void Close();

private:
    GLFWwindow *_pWindow;
};


#endif //GALILEO_WINDOW_H
