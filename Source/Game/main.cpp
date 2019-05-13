

#include "../Engine/Core/GameEngine.h"
#include "MyGameState.h"

int main()
{
    GameEngine engine(640, 480, "Hello world ! :D");

    if (!engine.IsInitialized())
    {
        // todo log
        return -1;
    }

    // Set active state
    engine.SetActiveState(new MyGameState());

    engine.Execute();

    return 0;
}