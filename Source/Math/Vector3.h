#ifndef GALILEO_VECTOR3_H
#define GALILEO_VECTOR3_H

template<class T>
class Vector3
{
public:
    T x;
    T y;
    T z;

    Vector3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Vector3(T x, T y, T z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void operator+=(const Vector3& other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
    }
};

typedef Vector3<float> Vector3f;

#endif //GALILEO_VECTOR3_H
