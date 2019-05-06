#ifndef GALILEO_CAMERA_H
#define GALILEO_CAMERA_H

#include "../Common.h"
#include "../Math/Vector3.h"
#include "../Math/Matrix4f.h"

/**
 * Represent the camera in the 3d scene
 */
class Camera
{
public:
    Camera();

    void UpdateViewMatrix(Matrix4f& matrix);

    void Move(float x, float y, float z);

private:
    Vector3f _position;
    Vector3f _rotation;
};


#endif //GALILEO_CAMERA_H
