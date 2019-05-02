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
    //matrix->Identity()->Translate(_position)->Rotate(_rotation)->Scale(_scale);
    matrix->Identity()->Translate(_position)->Scale(_scale)->Transpose();
}

void GameObject::Move(const Vector3f& offset)
{
    _position += offset;
}
