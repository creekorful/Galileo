#include "GameState.h"

void GameState::Update(Window& window, float dt)
{

}

void GameState::Render()
{
    for (auto& drawable : _gameObjects)
    {
        drawable.first->Bind();

        for (auto& gameObject : drawable.second)
        {
            gameObject.Render();
        }

        drawable.first->Unbind();
    }
}
