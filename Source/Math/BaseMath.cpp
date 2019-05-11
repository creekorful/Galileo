#include "BaseMath.h"

#define STB_PERLIN_IMPLEMENTATION

#include "../../ThirdParty/stb_perlin.h"

float BaseMath::ToRadians(float angleDegree)
{
    return angleDegree / 180.0 * PI;
}

float BaseMath::Noise(float x, float y)
{
    return stb_perlin_noise3(x, y, 0.0, 0, 0, 0);
}
