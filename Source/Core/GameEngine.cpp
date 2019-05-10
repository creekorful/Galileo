#include "GameEngine.h"

GameEngine::GameEngine(int width, int height, const std::string& windowTitle)
{
    _initialized = _window.Initialize(width, height, windowTitle);
}

void GameEngine::Execute()
{
    while (_window.ShouldClose())
    {
        // todo state & co
        _window.Render();
    }
}

bool GameEngine::IsInitialized()
{
    return _initialized;
}
