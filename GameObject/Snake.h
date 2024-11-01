#ifndef SNAKE_H
#define SNAKE_H

#include "BaseObject/MovableObject.h"

class Snake : public MovableObject<Coordinates>
{
    static const char snake_symbol = 'S';
public:
    Snake();
    explicit Snake(const Coordinates& coordinate);

    Point& Head();
    const Point& Head() const;

    void Move(const Direction dir);

    void Grow();

private:
    Direction last_direction;
    Point tail_coordinate;
};

#endif // SNAKE_H
