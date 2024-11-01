#include "CollisionChecker.h"

#include <algorithm>

CollisionChecker::CollisionChecker()
{

}

bool CollisionChecker::HasBorderCollision(const Point &point, const int32_t width, const int32_t height)
{
    if(point.x < 0 || point.x > static_cast<int32_t>(width - 1) ||
            point.y < 0 || point.y > static_cast<int32_t>(height - 1)) {
        return true;
    }
    return false;
}

bool CollisionChecker::HasBorderCollision(const Coordinates &coord, const int32_t width, const int32_t height)
{
    for(const Point& coord : coord) {
        if(HasBorderCollision(coord, width, height)) {
            return true;
        }
    }
    return false;
}

bool CollisionChecker::HasObjectsCollision(const Point &lhs, const Point &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y ? true : false;
}

bool CollisionChecker::HasObjectsCollision(const Coordinates &lhs, const Point &rhs)
{
    for(size_t i = 0; i < lhs.size(); ++i){
        if(lhs.at(i).x == rhs.x || lhs.at(i).y == rhs.y){
            return false;
        }
    }
    return true;
}

bool CollisionChecker::HasObjectsCollision(const Coordinates &lhs, const Coordinates &rhs)
{
    for(const Point& coord_lhs : lhs) {
                for(const Point& coord_rhs : rhs) {
                    if(HasObjectsCollision(coord_lhs, coord_rhs)) {
                        return true;
                    }
                }
            }
            return false;
//    return std::any_of(lhs.begin(), lhs.end(), [&rhs](int element) {
//        return std::find(rhs.begin(), rhs.end(), element) != rhs.end();
//    });
}
