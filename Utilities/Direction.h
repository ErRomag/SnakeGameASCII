#ifndef DIRECTION_H
#define DIRECTION_H

#include <vector>
#include <stdexcept>

#include "Utilities/Key.h"

enum Direction
{
    Up,
    Down,
    Left,
    Right,
};

static std::vector<Direction> All_Directions({Direction::Up, Direction::Down,
                                              Direction::Left, Direction::Right});

inline Direction DirectionFromKey(const Key key)
{
    switch(key)
    {
        case Key::W: return Up;
        case Key::S: return Down;
        case Key::A: return Left;
        case Key::D: return Right;
        default:  throw std::logic_error("Unknown direction");
    }
}

#endif // DIRECTION_H
