#include "Snake.h"

Snake::Snake() :
    MovableObject<Coordinates>(snake_symbol, Coordinates())
{

}

Snake::Snake(const Coordinates &coordinate) :
    MovableObject<Coordinates>(snake_symbol, coordinate)
{

}

Point& Snake::Head()
{
    return _position[0];
}

const Point& Snake::Head() const
{
    return _position[0];
}

void Snake::Move(const Direction dir)
{
    last_direction = dir;
    tail_coordinate = _position.back();

    for(size_t i = _position.size() - 1; i > 0; --i) {
        _position[i] = _position[i - 1];
    }

    switch (dir)
    {
    case Direction::Up:
    {
        Head().y--;
        break;
    }
    case Direction::Down:
    {
        Head().y++;
        break;
    }
    case Direction::Left:
    {
        Head().x--;
        if(last_direction != Direction::Left) {
            Head().y--;
        }
        break;
    }
    case Direction::Right:
    {
        Head().x++;
        if(last_direction != Direction::Right) {
            Head().y++;
        }
        break;
    }
    default:
        throw std::runtime_error("Unknown move direction for Snake");
    }
}

void Snake::Grow()
{
    _position.push_back(tail_coordinate);
}
