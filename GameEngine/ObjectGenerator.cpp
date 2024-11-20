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
    //std::srand(static_cast<uint32_t>(time(0)));
}

void ObjectGenerator::Init(const int32_t width, const int32_t height)
{
    field_width  = width;
    field_height = height;
    //std::srand(static_cast<uint32_t>(time(0)));
}

void ObjectGenerator::MakeEat(Eat &eat)
{
    //eat.SetPosition(Point(std::rand() % field_width, std::rand() % field_height));
    std::uniform_int_distribution<int> distribution_x(0, field_width - 1);
    std::uniform_int_distribution<int> distribution_y(0, field_height - 1);
    int random_x = distribution_x(generator);
    int random_y = distribution_y(generator);
    eat.SetPosition(Point(random_x, random_y));
}

void ObjectGenerator::MakeSnake(Snake& object)
{
    const uint32_t snake_lenght = 2;

    Coordinates body_coordinate;

//    Point head(Point(std::rand() % (field_width - snake_lenght - 1),
//                     std::rand() % (field_height - snake_lenght - 1)));

    std::uniform_int_distribution<int> distribution_x(field_width - 1 - snake_lenght,
                                                      field_height - 1 - snake_lenght);
    std::uniform_int_distribution<int> distribution_y(field_width - 1 - snake_lenght,
                                                      field_height - 1 - snake_lenght);
//    int random_x = distribution_x(generator);
//    int random_y = distribution_y(generator);
    Point head(Point(distribution_x(generator), distribution_y(generator)));

    body_coordinate.push_back(head);

    Direction random_dir = MakeRandomDir();
    for(uint32_t i = 0; i < snake_lenght - 1; ++i)
    {
        Point tail = body_coordinate.back();
        switch (random_dir)
        {
            case Direction::Up: {
                tail.y--;
                break;
            }
            case Direction::Down: {
                tail.y++;
                break;
            }
            case Direction::Left: {
                tail.x--;
                break;
            }
            case Direction::Right: {
                tail.x++;
                break;
            }
            default: throw std::logic_error("Unknown direction");
        }
        body_coordinate.push_back(tail);
    }

    object.SetPosition(body_coordinate);
}

Direction ObjectGenerator::MakeRandomDir() noexcept
{
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rand_dir(0, All_Directions.size() - 1);

    return static_cast<Direction>(rand_dir(gen));
}
/*
  01234
 #######
0#-----#
1#-- --#
2#-- --#
3#-- --#
4#-----#
 #######
*/
