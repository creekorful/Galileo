#ifndef GALILEO_GAMESTATE_H
#define GALILEO_GAMESTATE_H

#include <vector>

#include "Window.h"
#include "GameObject.h"
#include "Camera.h"
#include "../Graphics/Shader/Shader.h"

#define VIEW_MATRIX_UNIFORM "viewMatrix"

class GameState
{
public:
    virtual void Update(Window& window, float dt) = 0;

    virtual void Render() = 0;
};


#endif //GALILEO_GAMESTATE_H
