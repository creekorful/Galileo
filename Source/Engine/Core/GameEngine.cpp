#include "GameEngine.h"

GameEngine::GameEngine(int width, int height, const std::string& windowTitle, bool fullscreen, float fps) :
        _pGameState(nullptr), _logger(LoggerFactory::CreateLogger("GameEngine")), _baseTitle(windowTitle),
        _frameRate(1000.f / fps)
{
    // if running in fullscreen mode, bypass provided width/height
    Vector2i screenSize = fullscreen ? Window::GetDefaultScreenSize() : Vector2i(width, height);

    _initialized = _window.Initialize(screenSize, windowTitle, fullscreen);
}

void GameEngine::Execute()
{
    float time = GetTime();
    float elapsed = 0.f;

    while (!_window.ShouldClose())
    {
        // First of all synchronize to wanted frame rate
        elapsed = GetTime() - time;
        time = GetTime();

        if (elapsed < _frameRate)
        {
            Delay(_frameRate - elapsed);
            elapsed = _frameRate;
        }

        if (_pGameState != nullptr)
        {
            _pGameState->Update(_window, elapsed);
            _pGameState->Render(_window);
            _window.Render();
        }

        _window.SetTitle(_baseTitle + " (FPS: " + std::to_string(1000 / elapsed) + ")");
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

float GameEngine::GetTime() const
{
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
}

void GameEngine::Delay(float time)
{
    std::this_thread::sleep_for(std::chrono::milliseconds((int)time));
}
