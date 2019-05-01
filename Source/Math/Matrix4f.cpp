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
    delete[] _m;

    // set all values
    _m = new float* [4];
    for (int i = 0; i < 4; i++)
    {
        _m[i] = new float[4];

        for (int j = 0; j < 4; j++)
        {
            _m[i][j] = 0.0f;
        }
    }

    _m[0][0] = 1.0f;
    _m[1][1] = 1.0f;
    _m[2][2] = 1.0f;
    _m[3][3] = 1.0f;

    return this;
}

void Matrix4f::Scale(float x, float y, float z)
{
    // todo
}

void Matrix4f::Scale(const Vector3f& vector)
{
    Scale(vector.x, vector.y, vector.z);
}

void Matrix4f::Transform(float x, float y, float z)
{

}

void Matrix4f::Transform(const Vector3f& vector)
{
    Transform(vector.x, vector.y, vector.z);
}

void Matrix4f::Rotate(float x, float y, float z)
{

}

void Matrix4f::Rotate(const Vector3f& vector)
{
    Rotate(vector.x, vector.y, vector.z);
}

Matrix4f Matrix4f::CreateProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar)
{
    float h = tanf(fov * 0.5f);

    Matrix4f matrix4f;

    // https://jeux.developpez.com/tutoriels/OpenGL-ogldev/tutoriel-12-projection-perspective/
    matrix4f._m[0][0] = 1.0f / (h * aspectRatio);
    matrix4f._m[1][1] = 1.0f / h;
    matrix4f._m[2][2] = (-zNear - zFar) / (zNear - zFar);
    matrix4f._m[2][3] = 2.0f * zFar * zNear / (zNear - zFar);
    matrix4f._m[3][2] = 1.0f;
    matrix4f._m[3][3] = 0.0f;

    return matrix4f;
}

float* Matrix4f::First() const
{
    return &_m[0][0];
}
