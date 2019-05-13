#ifndef GALILEO_COMPONENT_H
#define GALILEO_COMPONENT_H


class Component
{
public:
    virtual ~Component() = default;

    virtual void Update(float dt) = 0;
};


#endif //GALILEO_COMPONENT_H
