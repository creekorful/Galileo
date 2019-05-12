#ifndef GALILEO_BASEMATH_H
#define GALILEO_BASEMATH_H

#include <cmath>

#define PI 3.14159265358979323846

class BaseMath
{
public:
    static float ToRadians(float angleDegree);

    /**
     * Generate 2D noise using Perlin algorithm
     *
     * @param x x pos
     * @param y y position
     * @return noise at x,y
     */
    static float Noise(float x, float y);

    /**
     * Generate 3D noise using Perlin algorithm
     *
     * @param x x pos
     * @param y y pos
     * @param z z pos
     * @return noise at z,y,z
     */
    static float Noise(float x, float y, float z);
};


#endif //GALILEO_BASEMATH_H
