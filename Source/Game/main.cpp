

#include "../Engine/Core/GameEngine.h"
#include "MyGameState.h"

int main()
{
    GameEngine engine(1280, 760, "Hello world ! :D", 120.f);

    if (!engine.IsInitialized())
    {
        // todo log
        return -1;
    }

    // Set active state
    GameState* pState = new MyGameState();
    engine.SetActiveState(pState);

    engine.Execute();

    // Finally cleanup
    delete pState;

    return 0;
}