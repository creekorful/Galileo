#include "Camera.h"

Camera::Camera() : _position(Vector3f()), _rotation(Vector3f())
{
}

Camera::Camera(const Vector3f& position) : _position(position), _rotation(Vector3f())
{
}

void Camera::UpdateViewMatrix(Matrix4f& matrix)
{
    matrix.Identity()
            .Rotate(BaseMath::toRadians(_rotation.x),
                    BaseMath::toRadians(_rotation.y),
                    BaseMath::toRadians(_rotation.z))
            .Translate(-_position)
            .Transpose();
}

void Camera::Move(float x, float y, float z)
{
    _position.x += x;
    _position.y += y;
    _position.z += z;
}

Vector3f Camera::Position()
{
    return _position;
}

void Camera::Rotate(float x, float y, float z)
{
    _rotation.x += x;
    _rotation.y += y;
    _rotation.z += z;
}
