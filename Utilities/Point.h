#ifndef POINT_H
#define POINT_H

#include <vector>
#include <ostream>
#include <stdint.h>

struct Point
{
    Point() : x(0), y(0) {}
    Point(const int32_t x, const int32_t y) : x(x), y(y) {}

    int32_t x;
    int32_t y;
};
/*
std::ostream& operator<<(std::ostream& os, const Point& rhs){
    return os << "x: " << rhs.x << " y: " << rhs.y << std::endl;
}

Point operator+(const Point& lhs, const Point& rhs){
    return Point(lhs.x + rhs.x, lhs.y + rhs.y);
}

Point operator-(const Point& lhs, const Point& rhs){
    return Point(lhs.x - rhs.x, lhs.y - rhs.y);
}
*/
using Coordinates = std::vector<Point>;
/*
std::ostream& operator<<(std::ostream& os, const Coordinates& coord){
    for(const Point& p : coord){
        os << p;
    }
    return os;
}
*/
#endif // POINT_H
