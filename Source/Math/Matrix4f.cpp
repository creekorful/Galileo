#include "Matrix4f.h"

Matrix4f::Matrix4f()
{
    m00 = 1.0f;
    m11 = 1.0f;
    m22 = 1.0f;
    m33 = 1.0f;
}

Matrix4f Matrix4f::CreateProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar)
{
    float h = (float) tanf(fov * 0.5f);
    // todo
    return Matrix4f();
}
