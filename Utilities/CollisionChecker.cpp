#include "CollisionChecker.h"

CollisionChecker::CollisionChecker()
{

}

bool CollisionChecker::HasBorderCollision(const Point &point,
                                          const int32_t width, const int32_t height) noexcept
{
    if((point.x < 0) || (point.y < 0)){
        return true;
    }

    if((point.x > (width - 1)) || (point.y > (height - 1))) {
        return true;
    }
    return false;
}

bool CollisionChecker::HasBorderCollision(const Coordinates &coord,
                                          const int32_t width, const int32_t height) noexcept
{
    for(const Point& coord : coord) {
        if(HasBorderCollision(coord, width, height)) {
            return true;
        }
    }
    return false;
}

bool CollisionChecker::HasObjectsCollision(const Point &lhs, const Point &rhs) noexcept
{
    return (lhs.x == rhs.x && lhs.y == rhs.y) ? true : false;
}

bool CollisionChecker::HasObjectsCollision(const Coordinates &lhs, const Point &rhs) noexcept
{
    for(const Point& point: lhs) {
        if(HasObjectsCollision(point, rhs)){
            return true;
        }
    }
    return false;
}

bool CollisionChecker::HasObjectsCollision(const Coordinates &lhs, const Coordinates &rhs) noexcept
{
    for(const Point& coord_lhs : lhs) {
        for(const Point& coord_rhs : rhs) {
            if(HasObjectsCollision(coord_lhs, coord_rhs)) {
                return true;
            }
        }
    }
    return false;
}
