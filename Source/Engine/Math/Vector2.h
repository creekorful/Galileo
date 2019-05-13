#ifndef GALILEO_VECTOR2_H
#define GALILEO_VECTOR2_H

#include <cmath>

template<class T>
class Vector2
{
public:
    T x;
    T y;

    Vector2() = default;

    Vector2(T x, T y)
    {
        this->x = x;
        this->y = y;
    }

    Vector2& Normalize()
    {
        double inverse = 1.0 / sqrt(x * x + y * y);
        x *= inverse;
        y *= inverse;
        return *this;
    }

    Vector2 operator+(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2& operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    static Vector2 Normalize(const Vector2& vector)
    {
        double inverse = 1.0 / sqrt(vector.x * vector.x + vector.y * vector.y);

        return Vector2(vector.x * inverse, vector.y * inverse);
    }
};

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;


#endif //GALILEO_VECTOR2_H
