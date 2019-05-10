#include "GameState.h"

void GameState::Update(Window& window, float dt)
{

}

void GameState::Render()
{
    // Get camera view matrix
    _camera.UpdateViewMatrix(_viewMatrix);

    _shader.Bind();
    for (auto& gameObject: _gameObjects)
    {
        _shader.SetUniform(VIEW_MATRIX_UNIFORM, gameObject.GetModelViewMatrix(_viewMatrix));
        gameObject.Render();
    }
    _shader.Unbind();
}
