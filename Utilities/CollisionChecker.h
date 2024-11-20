#ifndef COLLISIONCHECKER_H
#define COLLISIONCHECKER_H

#include <stdint.h>

#include "Utilities/Point.h"

class CollisionChecker
{
public:
    CollisionChecker();

    static bool HasBorderCollision(const Point& point, const int32_t width, const int32_t height) noexcept;

    static bool HasBorderCollision(const Coordinates &points, const int32_t width, const int32_t height) noexcept;

    static bool HasObjectsCollision(const Point& lhs, const Point& rhs) noexcept;

    static bool HasObjectsCollision(const Coordinates &lhs, const Point &rhs) noexcept;

    static bool HasObjectsCollision(const Coordinates& lhs, const Coordinates& rhs) noexcept;
};

#endif // COLLISIONCHECKER_H
