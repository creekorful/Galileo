#ifndef GALILEO_BASEMATH_H
#define GALILEO_BASEMATH_H

#include <cmath>

#define PI 3.14159265358979323846

class BaseMath
{
public:
    static float ToRadians(float angleDegree);

    /**
     * Generate noise using Perlin algorithm
     *
     * @param x x pos
     * @param y y position
     * @return noise at x,y
     */
    static float Noise(float x, float y);
};


#endif //GALILEO_BASEMATH_H
