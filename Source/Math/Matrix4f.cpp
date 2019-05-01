#include "Matrix4f.h"

#include <iostream>

Matrix4f::Matrix4f()
{
    Identity();
}

Matrix4f::~Matrix4f()
{
    delete[] _m;
}

Matrix4f* Matrix4f::Identity()
{
    //delete[] _m;

    // set all values
    _m = new float[16];
    for (int i = 0; i < 16; i++)
    {
        _m[i] = 0.0f;
    }

    _m[0] = 1.0f; // 0, 0
    _m[4 + 1] = 1.0f; // 1, 1
    _m[(4 * 2) + 2] = 1.0f; // 2, 2
    _m[(4 * 3) + 3] = 1.0f; // 3, 3

    return this;
}

Matrix4f* Matrix4f::Scale(float x, float y, float z)
{
    // todo
    return this;
}

Matrix4f* Matrix4f::Scale(const Vector3f& vector)
{
    return Scale(vector.x, vector.y, vector.z);
}

Matrix4f* Matrix4f::Translate(float x, float y, float z)
{
    // todo
    return this;
}

Matrix4f* Matrix4f::Translate(const Vector3f& vector)
{
    return Translate(vector.x, vector.y, vector.z);
}

Matrix4f* Matrix4f::Rotate(float x, float y, float z)
{
    //todo
    return this;
}

Matrix4f* Matrix4f::Rotate(const Vector3f& vector)
{
    return Rotate(vector.x, vector.y, vector.z);
}

Matrix4f Matrix4f::CreateProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar)
{
    float h = tanf(fov * 0.5f);

    Matrix4f matrix4f;

    // https://jeux.developpez.com/tutoriels/OpenGL-ogldev/tutoriel-12-projection-perspective/
    matrix4f._m[0] = 1.0f / (h * aspectRatio); // 0, 0
    matrix4f._m[4 + 1] = 1.0f / h; // 1, 1
    matrix4f._m[(4 * 2) + 2] = (-zNear - zFar) / (zNear - zFar); // 2, 2
    matrix4f._m[(4 * 2) + 3] = 2.0f * zFar * zNear / (zNear - zFar); // 2, 3
    matrix4f._m[(4 * 3) + 2] = 1.0f; // 3, 2
    matrix4f._m[(4 * 3) + 3] = 0.0f; // 3, 3

    return matrix4f;
}

float* Matrix4f::First() const
{
    return &_m[0];
}
