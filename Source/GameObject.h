#ifndef GALILEO_GAMEOBJECT_H
#define GALILEO_GAMEOBJECT_H

#include "Graphics/Mesh.h"
#include "Math/Matrix4f.h"

class GameObject
{
public:
    explicit GameObject(Mesh* mesh);

    void Render();

    void UpdateViewMatrix(Matrix4f* matrix);

    void Move(const Vector3f& offset);

private:
    Mesh* _mesh;

    Vector3f _position;
    Vector3f _rotation;
    Vector3f _scale;
};


#endif //GALILEO_GAMEOBJECT_H
