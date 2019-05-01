#include "GameObject.h"

GameObject::GameObject(Mesh* mesh)
{
    _mesh = mesh;
}

void GameObject::Render()
{
    _mesh->Render();
}
