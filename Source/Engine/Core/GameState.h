#ifndef GALILEO_GAMESTATE_H
#define GALILEO_GAMESTATE_H

#include <vector>

#include "Window.h"

class GameState
{
public:

    /**
     * Initialize state resources like matrices, textures, shaders, map, etc...
     *
     * @param window linked window
     * @return true if state has been successfully initialized false otherwise
     */
    virtual bool Initialize(Window& window) = 0;

    /**
     * Update state physics / controller
     *
     * @param window linked window
     * @param dt elapsed time between last update (in ms)
     */
    virtual void Update(Window& window, float dt) = 0;

    /**
     * Render the state to the screen
     */
    virtual void Render() = 0;
};


#endif //GALILEO_GAMESTATE_H
