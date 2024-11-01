#include "ObjectGenerator.h"

#include "time.h"
#include <random>
#include <stdexcept>

ObjectGenerator::ObjectGenerator(const int32_t width, const int32_t height)
    : field_width(width), field_height(height)
{
    std::srand(static_cast<uint32_t>(time(0)));
}

template<typename T>
void ObjectGenerator::CreateObject(AbsObject<T> &object)
{
    //изменить на switch(тип объекта) ??
    if (dynamic_cast<Eat*>(&object)) {
        makeEat(static_cast<Eat&>(object));
    }
    else if (dynamic_cast<Snake*>(&object)) {
        makeSnake(static_cast<Snake&>(object));
    }
    else {
        throw std::logic_error(std::string("Unsupported object type"));
    }
}

void ObjectGenerator::makeEat(Eat &eat)
{
    eat.SetPosition(Point(std::rand() % field_width, std::rand() % field_height));
}

void ObjectGenerator::makeSnake(Snake &snake)
{
    const uint32_t body_count = 2;

    Coordinates body_coordinate;

    Point head(std::rand() % (field_width - body_count - 1) ,
               std::rand() % (field_height - body_count - 1));

    body_coordinate.push_back(head);

    Direction tail_dir = static_cast<Direction>(std::rand() % All_Directions.size() - 1);
    for(uint32_t i = 0; i < body_count; ++i)
    {
        Point tail;
        switch (tail_dir)
        {
            case Direction::Up: {
            tail = Point(--body_coordinate.back().x, body_coordinate.back().y);
            break;
        }
        case Direction::Down: {
            tail = Point(++body_coordinate.back().x, body_coordinate.back().y);
            break;
        }
        case Direction::Left: {
            tail = Point(body_coordinate.back().x, --body_coordinate.back().y);
            break;
        }
        case Direction::Right: {
            tail = Point(body_coordinate.back().x, ++body_coordinate.back().y);
            break;
        }
        }
        body_coordinate.push_back(tail);
    }

    snake.SetPosition(body_coordinate);
}
