#ifndef GALILEO_GAMEENGINE_H
#define GALILEO_GAMEENGINE_H

#include "Window.h"
#include "GameState.h"

class GameEngine
{
public:
    GameEngine(int width, int height, const std::string& windowTitle);

    bool IsInitialized();

    void Execute();

    void setActiveScene(GameState* pGameState);

private:
    Window _window;
    bool _initialized;

    GameState* _pGameState;
};


#endif //GALILEO_GAMEENGINE_H
