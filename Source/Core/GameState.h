#ifndef GALILEO_GAMESTATE_H
#define GALILEO_GAMESTATE_H

#include <map>
#include <vector>

#include "Window.h"
#include "GameObject.h"
#include "Camera.h"
#include "../Graphics/Shader/Shader.h"

class GameState
{
public:

    void Update(Window& window, float dt);

    void Render();

protected:
    Camera _camera;

private:
    std::map<Shader*, std::vector<GameObject>> _gameObjects;
};


#endif //GALILEO_GAMESTATE_H
