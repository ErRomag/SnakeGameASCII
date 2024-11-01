#ifndef COLLISIONCHECKER_H
#define COLLISIONCHECKER_H

#include <stdint.h>

#include "Utilities/Point.h"

class CollisionChecker
{
public:
    CollisionChecker();

    static bool HasBorderCollision(const Point& point, const int32_t width, const int32_t height);

    static bool HasBorderCollision(const Coordinates &points, const int32_t width, const int32_t height);

    static bool HasObjectsCollision(const Point& lhs, const Point& rhs);

    static bool HasObjectsCollision(const Coordinates &lhs, const Point &rhs);

    static bool HasObjectsCollision(const Coordinates& lhs, const Coordinates& rhs);
};

#endif // COLLISIONCHECKER_H
