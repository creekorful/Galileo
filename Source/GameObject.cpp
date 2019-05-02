#include "GameObject.h"

GameObject::GameObject(Mesh* mesh)
{
    _mesh = mesh;
}

void GameObject::Render()
{
    _mesh->Render();
}

void GameObject::UpdateViewMatrix(Matrix4f& matrix)
{
    matrix.Identity()
            .Scale(_scale)
            .Translate(_position)
            .Rotate(Vector3f(BaseMath::toRadians(-_rotation.x),
                             BaseMath::toRadians(-_rotation.y),
                             BaseMath::toRadians(-_rotation.z)))
            .Transpose();
}

void GameObject::Move(const Vector3f& offset)
{
    _position += offset;
}

void GameObject::Move(float x, float y, float z)
{
    _position.x += x;
    _position.y += y;
    _position.z += z;
}

void GameObject::Rotate(const Vector3f& offset)
{
    _rotation += offset;
}

void GameObject::Scale(float factor)
{
    _scale = factor;
}

Vector3f GameObject::Position() const
{
    return _position;
}
