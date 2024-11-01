#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include "AbsObject.h"
#include "Utilities/Direction.h"

template <typename T>
class MovableObject : public AbsObject<T>
{
public:
    explicit MovableObject(const char symbol, const T& pos) :
        AbsObject<T>(symbol, pos) {};

    virtual void Move(const Direction dir) = 0;
};

#endif // MOVABLEOBJECT_H
