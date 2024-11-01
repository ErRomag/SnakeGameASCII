#ifndef OBJECTGENERATOR_H
#define OBJECTGENERATOR_H

#include "GameObject/Eat.h"
#include "GameObject/Snake.h"
#include "Utilities/Direction.h"
#include "GameObject/BaseObject/AbsObject.h"

class ObjectGenerator
{
public:
    explicit ObjectGenerator(const int32_t field_width, const int32_t field_height);

    void makeEat(Eat& eat);
    void makeSnake(Snake& snake);

    template<typename T>
    void CreateObject(AbsObject<T>& object);

private:
    int32_t field_width;
    int32_t field_height;

    Direction makeRandomDir();
};

#endif // OBJECTGENERATOR_H
