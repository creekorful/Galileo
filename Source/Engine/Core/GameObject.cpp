#include "GameObject.h"

GameObject::GameObject(Mesh* mesh, Texture* pTexture) : _scale(1)
{
    _pMesh = mesh;
    _pTexture = pTexture;
}

GameObject::GameObject(Mesh* mesh, Texture* pTexture, float x, float y, float z) : GameObject(mesh, pTexture)
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
    _pComponents.push_back(pComponent);
}

void GameObject::AddComponents(const std::vector<Component*>& pComponents)
{
    for (auto pComponent : pComponents)
    {
        AddComponent(pComponent);
    }
}

void GameObject::Update(float dt)
{
    for (auto pComponent : _pComponents)
    {
        pComponent->Update(dt);
    }
}

void GameObject::Render()
{
    if (_pTexture != nullptr)
        _pTexture->Bind();

    if (_pMesh != nullptr)
        _pMesh->Render();

    if (_pTexture != nullptr)
        _pTexture->Unbind();
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

void GameObject::Scale(float factor)
{
    _scale = factor;
}

Vector3f GameObject::Position() const
{
    return _position;
}
