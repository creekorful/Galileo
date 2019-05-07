#include "Matrix4f.h"

Matrix4f::Matrix4f() : _m(nullptr)
{
    Identity();
}

Matrix4f::Matrix4f(const Matrix4f& other) : _m(nullptr)
{
    _m = new float[16];
    for (int i = 0; i < 16; i++)
    {
        _m[i] = other.First()[i];
    }
}

Matrix4f::~Matrix4f()
{
    delete[] _m;
}

Matrix4f& Matrix4f::Identity()
{
    delete[] _m;

    // set all values
    _m = new float[16];
    for (int i = 0; i < 16; i++)
    {
        _m[i] = 0.0f;
    }

    Set(0, 0, 1.0f);
    Set(1, 1, 1.0f);
    Set(2, 2, 1.0f);
    Set(3, 3, 1.0f);

    return *this;
}

Matrix4f& Matrix4f::Scale(float x, float y, float z)
{
    (*this) *= MakeScaleMatrix(x, y, z);

    return *this;
}

Matrix4f& Matrix4f::Scale(const Vector3f& vector)
{
    return Scale(vector.x, vector.y, vector.z);
}

Matrix4f& Matrix4f::Scale(float factor)
{
    return Scale(factor, factor, factor);
}

Matrix4f& Matrix4f::Translate(float x, float y, float z)
{
    (*this) *= MakeTranslationMatrix(x, y, z);

    return *this;
}

Matrix4f& Matrix4f::Translate(const Vector3f& vector)
{
    return Translate(vector.x, vector.y, vector.z);
}

Matrix4f& Matrix4f::Rotate(float x, float y, float z)
{
    (*this) *= MakeRotationMatrix(x, y, z);

    return *this;
}

Matrix4f& Matrix4f::Rotate(const Vector3f& vector)
{
    return Rotate(vector.x, vector.y, vector.z);
}

Matrix4f Matrix4f::CreateProjectionMatrix(float fov, const Vector2i& screenSize, float zNear, float zFar)
{
    float h = tanf(fov * 0.5f);
    float ratio = screenSize.x / screenSize.y;

    // https://github.com/JOML-CI/JOML/blob/master/src/org/joml/Matrix4f.java
    Matrix4f matrix4f;
    matrix4f.Set(0, 0, 1.0f / (h * ratio));
    matrix4f.Set(1, 1, 1.0f / h);
    matrix4f.Set(2, 2, (zFar + zNear) / (zNear - zFar));
    matrix4f.Set(2, 3, -1.0f);
    matrix4f.Set(3, 2, ((zFar + zFar) * zNear) / (zNear - zFar));

    return matrix4f;
}

float* Matrix4f::First() const
{
    return &_m[0];
}

void Matrix4f::Set(unsigned short x, unsigned short y, float value)
{
    _m[x * 4 + y] = value;
}

float Matrix4f::Get(unsigned short x, unsigned short y) const
{
    return _m[x * 4 + y];
}

Matrix4f& Matrix4f::Transpose()
{
    Matrix4f tmp(*this);

    // swap first row -> first column
    Set(0, 0, tmp._m[0]);
    Set(1, 0, tmp._m[1]);
    Set(2, 0, tmp._m[2]);
    Set(3, 0, tmp._m[3]);

    // swap 2nd row -> 2nd column
    Set(0, 1, tmp._m[4]);
    Set(1, 1, tmp._m[5]);
    Set(2, 1, tmp._m[6]);
    Set(3, 1, tmp._m[7]);

    // swap 3th row -> 3th column
    Set(0, 2, tmp._m[8]);
    Set(1, 2, tmp._m[9]);
    Set(2, 2, tmp._m[10]);
    Set(3, 2, tmp._m[11]);

    // swap 4rd -> 4rd column
    Set(0, 3, tmp._m[12]);
    Set(1, 3, tmp._m[13]);
    Set(2, 3, tmp._m[14]);
    Set(3, 3, tmp._m[15]);

    return *this;
}

void Matrix4f::Dump() const
{
    std::cout << std::endl;
    for (int i = 0; i < 4; i++)
    {
        std::cout << _m[i * 4] << " " << _m[i * 4 + 1] << " " << _m[i * 4 + 2] << " " << _m[i * 4 + 3] << std::endl;
    }
}

Matrix4f Matrix4f::operator*(const Matrix4f& other) const
{
    Matrix4f val(*this);
    val *= other;
    return val;
}

void Matrix4f::operator*=(const Matrix4f& other)
{
    Matrix4f tmp(*this);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Set(i, j,
                (tmp.Get(i, 0) * other.Get(0, j)) +
                (tmp.Get(i, 1) * other.Get(1, j)) +
                (tmp.Get(i, 2) * other.Get(2, j)) +
                (tmp.Get(i, 3) * other.Get(3, j)));
        }
    }
}

Matrix4f Matrix4f::MakeRotationMatrix(float x, float y, float z)
{
    // https://en.wikipedia.org/wiki/Rotation_matrix
    // x axis rotation
    Matrix4f xAxis;
    float cosx = cos(x);
    float sinx = sin(x);
    xAxis.Set(1, 1, cosx);
    xAxis.Set(1, 2, -sinx);
    xAxis.Set(2, 1, sinx);
    xAxis.Set(2, 2, cosx);

    // y axis rotation
    Matrix4f yAxis;
    float cosy = cos(y);
    float siny = sin(y);
    yAxis.Set(0, 0, cosy);
    yAxis.Set(0, 2, siny);
    yAxis.Set(2, 0, -siny);
    yAxis.Set(2, 2, cosy);

    // z axis rotation
    Matrix4f zAxis;
    float cosz = cos(z);
    float sinz = sin(z);
    zAxis.Set(0, 0, cosz);
    zAxis.Set(0, 1, -sinz);
    zAxis.Set(1, 0, sinz);
    zAxis.Set(1, 1, cosz);

    return xAxis * yAxis * zAxis;
}

Matrix4f Matrix4f::MakeTranslationMatrix(float x, float y, float z)
{
    Matrix4f matrix;
    matrix.Set(0, 3, x);
    matrix.Set(1, 3, y);
    matrix.Set(2, 3, z);

    return matrix;
}


Matrix4f Matrix4f::MakeScaleMatrix(float x, float y, float z)
{
    Matrix4f matrix;
    matrix.Set(0, 0, x);
    matrix.Set(1, 1, y);
    matrix.Set(2, 2, z);

    return matrix;
}
