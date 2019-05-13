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
     * @param screenSize the screen size
     * @param title window title
     * @param fullscreen if true run in fullscreen mode
     * @return true if initialization successful false otherwise
     */
    bool Initialize(Vector2i screenSize, const std::string& title, bool fullscreen = false);

    /**
     * @return true if window should be closed
     */
    bool ShouldClose() const;

    /**
     * Close the window gracefully
     */
    void Close();

    /**
     * Render / update the window
     */
    void Render();

    /**
     * @return size of current window
     */
    Vector2i Size() const;

    /**
     * @return mouse position
     */
    Vector2d GetMousePos() const;

    /**
     * Check if given key is pressed
     *
     * @param keyCode the key code
     * @return true if key is pressed, false otherwise
     */
    bool IsKeyPressed(GLenum keyCode) const;

    /**
     * Set the window title
     *
     * @param title window title
     */
    void SetTitle(const std::string& title);

    /**
     * Helper method to retrieve size of default monitor
     *
     * @return size of default monitor
     */
    static Vector2i GetDefaultScreenSize();

private:
    GLFWwindow* _pWindow;
    Logger _logger;
};


#endif //GALILEO_WINDOW_H
