#ifndef OBJECTGENERATOR_H
#define OBJECTGENERATOR_H

#include <type_traits>

#include "GameObject/Eat.h"
#include "GameObject/Snake.h"
#include "Utilities/Direction.h"
#include "GameObject/BaseObject/AbsObject.h"

class ObjectGenerator
{
public:
    ObjectGenerator();
    explicit ObjectGenerator(const int32_t field_width, const int32_t field_height);

    void Init(const int32_t width, const int32_t height);

    template<typename T>
    void CreateObject(AbsObject<T>& object);

    Direction MakeRandomDir();

private:
    int32_t field_width;
    int32_t field_height;

    void MakeEat(Eat& eat);
    void MakeSnake(Snake& object);
};

template<typename T>
void ObjectGenerator::CreateObject(AbsObject<T> &object)
{
    if(std::is_same<T, Point>::value) {
        MakeEat(dynamic_cast<Eat&>(object));
        return;
    }
    else if(std::is_same<T, Coordinates>::value) {
        MakeSnake(dynamic_cast<Snake&>(object));
        return;
    }

    throw std::logic_error(std::string("Unsupported object type"));
}

#endif // OBJECTGENERATOR_H
