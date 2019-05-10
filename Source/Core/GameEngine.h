#ifndef GALILEO_GAMEENGINE_H
#define GALILEO_GAMEENGINE_H

#include "Window.h"

class GameEngine
{
public:
    GameEngine(int width, int height, const std::string& windowTitle);

    bool IsInitialized();

    void Execute();

private:
    Window _window;
    bool _initialized;
};


#endif //GALILEO_GAMEENGINE_H
