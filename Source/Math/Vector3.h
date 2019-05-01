#ifndef GALILEO_VECTOR3_H
#define GALILEO_VECTOR3_H

template<class T>
class Vector3
{
public:
    T x;
    T y;
    T z;

    Vector3() = default;

    Vector3(T x, T y, T z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

#endif //GALILEO_VECTOR3_H
