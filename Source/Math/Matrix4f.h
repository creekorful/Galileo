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
    Matrix4f& Identity();

    Matrix4f& Scale(float x, float y, float z);

    Matrix4f& Scale(const Vector3f& vector);

    Matrix4f& Scale(float factor);

    /**
     * Translate matrix by given offset
     *
     * @param x x offset
     * @param y y offset
     * @param z z offset
     * @return this, modified
     */
    Matrix4f& Translate(float x, float y, float z);

    /**
     * @see Matrix4f#Translate(float,float,float)
     */
    Matrix4f& Translate(const Vector3f& vector);

    Matrix4f& Rotate(float x, float y, float z);

    /**
     * Rotate matrix by given offset
     * angle must be in radians
     *
     * @param vector offset
     * @return this, rotated
     */
    Matrix4f& Rotate(const Vector3f& vector);

    /**
     * Transpose current matrix
     * @return this
     */
    Matrix4f& Transpose();

    /**
     * @return pointer to matrix (values are stored continuously in memory)
     */
    float* First() const;

    void Set(unsigned short x, unsigned short y, float value);

    float Get(unsigned short x, unsigned short y) const;

    void Dump() const;

    /**
     * Perform multiplication between this and other
     * this DOES NOT alter current matrix
     *
     * @param other other matrix
     * @return new matrix result of this * other
     */
    Matrix4f operator*(const Matrix4f& other) const;

    /**
     * Perform multiplication between this and other
     * this DOES alter current matrix
     *
     * @param other other matrix
     */
    void operator*=(const Matrix4f& other);

    static Matrix4f MakeRotationMatrix(const Vector3f& angles);
    static Matrix4f MakeRotationMatrix(float x, float y, float z);
    static Matrix4f MakeTranslationMatrix(const Vector3f& values);
    static Matrix4f MakeTranslationMatrix(float x, float y, float z);
    static Matrix4f MakeScaleMatrix(const Vector3f& factor);
    static Matrix4f MakeScaleMatrix(float x, float y, float z);
    static Matrix4f MakeScaleMatrix(float factor);

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

    /**
     * Perform dot product of this row by other matrix
     * this will update row of this by multiplication of each column of other
     *
     * @param other other matrix
     */
    void DotProduct(int row, const Matrix4f& other);
};


#endif //GALILEO_MATRIX4F_H
