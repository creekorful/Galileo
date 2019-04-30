#ifndef GALILEO_WINDOW_H
#define GALILEO_WINDOW_H

#include <GLFW/glfw3.h>
#include <iostream>

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
    bool initialize(int width, int height, std::string &title);

    /**
     * @return true if window should be closed
     */
    bool shouldClose();

    /**
     * Render / update the window
     */
    void render();

    /**
     * Gracefully close the window
     */
    void close();

private:
    GLFWwindow *_pWindow;
};


#endif //GALILEO_WINDOW_H
