#include "GameEngine.h"

GameEngine::GameEngine(int width, int height, const std::string& windowTitle) : _pGameState(nullptr)
{
    _initialized = _window.Initialize(width, height, windowTitle);
}

void GameEngine::Execute()
{
    while (_window.ShouldClose())
    {
        if (_pGameState != nullptr)
        {
            _pGameState->Render();
        }

        _window.Render();
    }
}

bool GameEngine::IsInitialized()
{
    return _initialized;
}

void GameEngine::setActiveScene(GameState* pGameState)
{
    _pGameState = pGameState;
}
