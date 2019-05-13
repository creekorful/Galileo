#ifndef GALILEO_GAMEOBJECT_H
#define GALILEO_GAMEOBJECT_H

#include <vector>

#include "../Graphics/Mesh/Mesh.h"
#include "../Math/BaseMath.h"
#include "../Math/Matrix4f.h"
#include "Component.h"

class GameObject
{
public:
    explicit GameObject(Mesh* mesh, Texture* pTexture = nullptr);

    GameObject(Mesh* mesh, Texture* pTexture, float x, float y, float z);

    ~GameObject();

    /**
     * Add a component to the game object
     * the component lifecycle is managed by the object and component will be deleted once game object goes out of scope
     *
     * @param pComponent pointer to component to add
     */
    void AddComponent(Component* pComponent);

    /**
     * Add several components to the game objects
     *
     * @param pComponents list of components to add
     */
    void AddComponents(const std::vector<Component*>& pComponents);

    /**
     * Update the game object
     * this will update the components
     *
     * @param dt elapsed time
     */
    void Update(float dt);

    /**
     * Render the game object to the screen
     */
    void Render();

    /**
     * Get the model view matrix
     *
     * @param viewMatrix camera matrix
     * @return model view matrix
     */
    Matrix4f GetModelViewMatrix(const Matrix4f& viewMatrix) const;

    void Move(const Vector3f& offset);

    void Move(float x, float y, float z);

    void Rotate(const Vector3f& offset);

    void Rotate(float x, float y, float z);

    void Scale(float factor);

    Vector3f Position() const;

protected:
    Vector3f _position;
    Vector3f _rotation;
    float _scale;

private:
    Mesh* _pMesh;
    Texture* _pTexture;

    std::vector<Component*> _pComponents;
};


#endif //GALILEO_GAMEOBJECT_H
