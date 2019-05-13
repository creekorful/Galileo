#include "GameEngine.h"

GameEngine::GameEngine(int width, int height, const std::string& windowTitle) :
        _pGameState(nullptr), _logger(LoggerFactory::CreateLogger("GameEngine"))
{
    _initialized = _window.Initialize(width, height, windowTitle);
}

void GameEngine::Execute()
{
    while (!_window.ShouldClose())
    {
        if (_pGameState != nullptr)
        {
            _pGameState->Update(_window, 0);
            _pGameState->Render(_window);
        }

        //_window.Render();
    }
}

bool GameEngine::IsInitialized()
{
    return _initialized;
}

void GameEngine::SetActiveState(GameState* pGameState)
{
    _pGameState = pGameState;

    // todo manage persistent state
    if (!_pGameState->Initialize(_window))
    {
        _logger.Error("Error while initializing state");
        _window.Close();
    }
}
