#ifndef GALILEO_GAMEENGINE_H
#define GALILEO_GAMEENGINE_H

#include <chrono>
#include <thread>

#include "../Window.h"
#include "GameState.h"

class GameEngine
{
public:
    GameEngine(int width, int height, const std::string& windowTitle, bool fullscreen = false, float fps = 120.f);

    bool IsInitialized();

    void Execute();

    void SetActiveState(GameState* pGameState);

private:
    Window _window;
    bool _initialized;
    float _frameRate;
    std::string _baseTitle;

    Logger _logger;

    GameState* _pGameState;

    /**
     * @return current time, as milliseconds
     */
    float GetTime() const;

    /**
     * Sleep current thread for given time in milliseconds
     *
     * @param time time to sleep current thread, in milliseconds
     */
    void Delay(float time);
};


#endif //GALILEO_GAMEENGINE_H
