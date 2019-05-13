#ifndef GALILEO_CAMERA_H
#define GALILEO_CAMERA_H

#include "../Common.h"
#include "../Math/Vector3.h"
#include "../Math/Matrix4f.h"
#include "GameObject.h"

/**
 * Represent the camera in the 3d scene
 */
class Camera : public GameObject
{
public:
    Camera();

    explicit Camera(const Vector3f& position);

    void UpdateViewMatrix(Matrix4f& matrix);
};


#endif //GALILEO_CAMERA_H
