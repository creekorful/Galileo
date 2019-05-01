#include "GameObject.h"

GameObject::GameObject(Mesh* mesh)
{
    _mesh = mesh;
}

void GameObject::Render()
{
    _mesh->Render();
}

void GameObject::UpdateViewMatrix(Matrix4f* matrix)
{
    matrix->Identity()->Translate(_position)->Rotate(_rotation)->Scale(_scale);
}

void GameObject::Move(const Vector3f& offset)
{
    _position += offset;
}
