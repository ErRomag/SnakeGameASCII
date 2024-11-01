#ifndef DIRECTION_H
#define DIRECTION_H

#include <string>
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

#endif // DIRECTION_H
