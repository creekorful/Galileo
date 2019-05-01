#ifndef GALILEO_GAMEOBJECT_H
#define GALILEO_GAMEOBJECT_H

#include "Graphics/Mesh.h"
#include "Math/Vector3f.h"

class GameObject
{
public:
    explicit GameObject(Mesh* mesh);

    void Render();

private:
    Mesh* _mesh;

    Vector3f _position;
    Vector3f _rotation;
    Vector3f _scale;
};


#endif //GALILEO_GAMEOBJECT_H
