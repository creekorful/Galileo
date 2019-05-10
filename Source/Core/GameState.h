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

    void Update(Window& window, float dt);

    void Render();

protected:
    Camera _camera;

private:
    std::vector<GameObject> _gameObjects;
    Shader _shader;

    Matrix4f _projectionMatrix;
    Matrix4f _modelViewMatrix;
    Matrix4f _viewMatrix;
};


#endif //GALILEO_GAMESTATE_H
