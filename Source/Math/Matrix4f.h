#ifndef GALILEO_MATRIX4F_H
#define GALILEO_MATRIX4F_H

#include "BaseMath.h"
#include "Vector3f.h"

class Matrix4f
{
public:
    /**
     * Create a matrix that is the identity matrix
     */
    Matrix4f();

    ~Matrix4f();

    /**
     * Reset current matrix as identity one
     * @return this
     */
    Matrix4f* Identity();

    void Scale(float x, float y, float z);

    void Scale(const Vector3f& vector);

    void Transform(float x, float y, float z);

    void Transform(const Vector3f& vector);

    void Rotate(float x, float y, float z);

    void Rotate(const Vector3f& vector);

    float* First() const;

    /**
     * Create a projection matrix from given args
     *
     * @param fov field of view
     * @param aspectRatio the aspect ratio (width / height)
     * @param zNear z plane near distance
     * @param zFar z plane far distance
     * @return built matrix
     */
    static Matrix4f CreateProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar);

private:
    float* _m;
};


#endif //GALILEO_MATRIX4F_H
