#include "GameEngine.h"

GameEngine::GameEngine(int width, int height, const std::string& windowTitle) :
        _pGameState(nullptr), _logger(LoggerFactory::CreateLogger("GameEngine"))
{
    _initialized = _window.Initialize(width, height, windowTitle);
}

void GameEngine::Execute()
{
    std::chrono::time_point last = std::chrono::high_resolution_clock::now();

    while (!_window.ShouldClose())
    {
        std::chrono::time_point now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> time = now - last;
        last = now;

        if (_pGameState != nullptr)
        {
            _pGameState->Update(_window, 0);
            _pGameState->Render(_window);
            _window.Render();
        }

        _window.SetTitle("FPS: " + std::to_string(time.count() * 1000));
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
