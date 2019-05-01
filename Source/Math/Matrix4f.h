#ifndef GALILEO_MATRIX4F_H
#define GALILEO_MATRIX4F_H

#include "BaseMath.h"
#include "Vector3.h"
#include "Vector2.h"

#include <iostream>

class Matrix4f
{
public:
    /**
     * Create a matrix that is the identity matrix
     */
    Matrix4f();

    /**
     * Create matrix as a copy of provided one
     * @param other matrix to be copied
     */
    Matrix4f(const Matrix4f& other);

    ~Matrix4f();

    /**
     * Reset current matrix as identity one
     * @return this
     */
    Matrix4f* Identity();

    Matrix4f* Scale(float x, float y, float z);

    Matrix4f* Scale(const Vector3f& vector);

    Matrix4f* Translate(float x, float y, float z);

    Matrix4f* Translate(const Vector3f& vector);

    Matrix4f* Rotate(float x, float y, float z);

    Matrix4f* Rotate(const Vector3f& vector);

    /**
     * Transpose current matrix
     * @return this
     */
    Matrix4f* Transpose();

    float* First() const;

    void Set(unsigned short x, unsigned short y, float value);

    void Dump() const;

    /**
     * Create a projection matrix from given args
     *
     * @param fov field of view
     * @param screenSize the screen size
     * @param zNear z plane near distance
     * @param zFar z plane far distance
     * @return built matrix
     */
    static Matrix4f CreateProjectionMatrix(float fov, const Vector2i& screenSize, float zNear, float zFar);

private:
    float* _m;
};


#endif //GALILEO_MATRIX4F_H
