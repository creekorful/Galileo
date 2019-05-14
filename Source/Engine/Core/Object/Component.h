#ifndef GALILEO_COMPONENT_H
#define GALILEO_COMPONENT_H

#include "../Window.h"
#include "GameObject.h"

class GameObject;

class Component
{
public:
    virtual ~Component() = default;

    virtual void Update(Window& window, float dt) = 0;

    virtual void SetGameObject(GameObject* pGameObject) = 0;
};


#endif //GALILEO_COMPONENT_H
