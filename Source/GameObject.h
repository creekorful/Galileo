#ifndef GALILEO_GAMEOBJECT_H
#define GALILEO_GAMEOBJECT_H

#include "Graphics/Mesh.h"
#include "Math/BaseMath.h"
#include "Math/Matrix4f.h"

class GameObject
{
public:
    explicit GameObject(Mesh* mesh);

    void Render();

    /**
     * Update given matrix by game object transform
     *
     * @param matrix matrix (usually view) to be updated
     */
    void UpdateViewMatrix(Matrix4f& matrix);

    void Move(const Vector3f& offset);

    void Move(float x, float y, float z);

    void Rotate(const Vector3f& offset);

    void Scale(float factor);

    Vector3f Position() const;

private:
    Mesh* _mesh;

    Vector3f _position;
    Vector3f _rotation;
    float _scale;
};


#endif //GALILEO_GAMEOBJECT_H
