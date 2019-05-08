#ifndef GALILEO_GAMEOBJECT_H
#define GALILEO_GAMEOBJECT_H

#include "../Graphics/Mesh/Mesh.h"
#include "../Math/BaseMath.h"
#include "../Math/Matrix4f.h"

class GameObject
{
public:
    explicit GameObject(Mesh* mesh);

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

    void Scale(float factor);

    Vector3f Position() const;

private:
    Mesh* _mesh;

    Vector3f _position;
    Vector3f _rotation;
    float _scale;
};


#endif //GALILEO_GAMEOBJECT_H
