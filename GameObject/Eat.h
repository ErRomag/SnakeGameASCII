#ifndef EAT_H
#define EAT_H

#include "BaseObject/AbsObject.h"

class Eat : public AbsObject<Point>
{
    static const char eat_symbol = 'E';
public:
    Eat() :
        AbsObject<Point>(eat_symbol, Point()) {}
    explicit Eat(const Point& point) :
        AbsObject<Point>(eat_symbol, point) {}
};

#endif // EAT_H
