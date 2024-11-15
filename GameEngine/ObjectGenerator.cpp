#include "ObjectGenerator.h"

#include "time.h"
#include <random>
#include <stdexcept>

ObjectGenerator::ObjectGenerator()
    : field_width(0), field_height(0)
{

}

ObjectGenerator::ObjectGenerator(const int32_t width, const int32_t height)
    : field_width(width), field_height(height)
{
    std::srand(static_cast<uint32_t>(time(0)));
}

void ObjectGenerator::Init(const int32_t width, const int32_t height)
{
    field_width  = width;
    field_height = height;
    std::srand(static_cast<uint32_t>(time(0)));
}

void ObjectGenerator::MakeEat(Eat &eat)
{
    eat.SetPosition(Point(std::rand() % field_width, std::rand() % field_height));
}

void ObjectGenerator::MakeSnake(Snake& object)
{
    const uint32_t snake_lenght = 2;

    Coordinates body_coordinate;

    Point head(Point(std::rand() % field_width, std::rand() % field_height));
    body_coordinate.push_back(head);

    for(uint32_t i = 0; i < snake_lenght - 1; ++i)
    {
        Point tail;
        switch (MakeRandomDir())
        {
            case Direction::Up: {
                tail = Point(body_coordinate.back().x, --body_coordinate.back().y);
                break;
            }
            case Direction::Down: {
                tail = Point(body_coordinate.back().x, ++body_coordinate.back().y);
                break;
            }
            case Direction::Left: {
                tail = Point(--body_coordinate.back().x, body_coordinate.back().y);
                break;
            }
            case Direction::Right: {
                tail = Point(++body_coordinate.back().x, body_coordinate.back().y);
                break;
            }
        }
        body_coordinate.push_back(tail);
    }

    object.SetPosition(body_coordinate);
}

Direction ObjectGenerator::MakeRandomDir()
{
    return static_cast<Direction>(std::rand() % All_Directions.size() - 1);
}
