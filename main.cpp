#include "Source/Graphics/Window.h"

int main()
{
    std::string title = "Hello world";
    auto *pWindow = new Window();
    if (!pWindow->initialize(650, 480, title))
    {
        // todo
    }

    while (!pWindow->shouldClose())
    {
        pWindow->render();
    }

    pWindow->close();
    return 0;
}