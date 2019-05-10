#ifndef GALILEO_VECTOR2_H
#define GALILEO_VECTOR2_H


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
};

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;


#endif //GALILEO_VECTOR2_H
