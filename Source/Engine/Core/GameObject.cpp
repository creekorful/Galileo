#include "GameObject.h"

GameObject::GameObject(Mesh* mesh) : _scale(1)
{
    _pMesh = mesh;
}

GameObject::GameObject(Mesh* mesh, float x, float y, float z) : GameObject(mesh)
{
    _position.x = x;
    _position.y = y;
    _position.z = z;
}

GameObject::~GameObject()
{
    for (auto pComponent : _pComponents)
    {
        delete pComponent;
    }
}

void GameObject::AddComponent(Component* pComponent)
{
    // link component to game object
    pComponent->SetGameObject(this);
    _pComponents.push_back(pComponent);
}

void GameObject::AddComponents(const std::vector<Component*>& pComponents)
{
    for (auto pComponent : pComponents)
    {
        AddComponent(pComponent);
    }
}

void GameObject::Update(Window& window, float dt)
{
    for (auto pComponent : _pComponents)
    {
        pComponent->Update(window, dt);
    }
}

void GameObject::Render()
{
    // Mesh is optional
    if (_pMesh != nullptr)
        _pMesh->Render();
}

Matrix4f GameObject::GetModelViewMatrix(const Matrix4f& viewMatrix) const
{
    Matrix4f modelMatrix;
    modelMatrix.Scale(_scale)
            .Translate(_position)
            .Rotate(BaseMath::ToRadians(-_rotation.x),
                    BaseMath::ToRadians(-_rotation.y),
                    BaseMath::ToRadians(-_rotation.z))
            .Transpose();
    return modelMatrix * viewMatrix;
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

void GameObject::Rotate(float x, float y, float z)
{
    _rotation.x += x;
    _rotation.y += y;
    _rotation.z += z;
}

void GameObject::Scale(float factor)
{
    _scale = factor;
}

Vector3f GameObject::Position() const
{
    return _position;
}
