#ifndef GALILEO_MATRIX4F_H
#define GALILEO_MATRIX4F_H

#include "BaseMath.h"

class Matrix4f
{
public:
    /**
     * Create a matrix that is the identity matrix
     */
    Matrix4f();

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
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;
};


#endif //GALILEO_MATRIX4F_H
