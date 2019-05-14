#include "Camera.h"

Camera::Camera() : GameObject(nullptr)
{
}

Camera::Camera(const Vector3f& position) : GameObject(nullptr, position.x, position.y, position.z)
{
}

void Camera::UpdateViewMatrix(Matrix4f& matrix)
{
    matrix.Identity()
            .Rotate(BaseMath::ToRadians(_rotation.x),
                    BaseMath::ToRadians(_rotation.y),
                    BaseMath::ToRadians(_rotation.z))
            .Translate(-_position)
            .Transpose();
}