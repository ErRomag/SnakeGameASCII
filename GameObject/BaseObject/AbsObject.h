#ifndef ABSGAMEOBJECT_H
#define ABSGAMEOBJECT_H

#include "Utilities/Point.h"

// добавить флаг можно ли пройти через объект

template<typename T>
class AbsObject
{
public:
    AbsObject() : _symbol(' '), _position(T()) {}
    explicit AbsObject(const char symbol, const T& pos) :
        _symbol(symbol), _position(pos) {}

    char Symbol() const noexcept{
        return _symbol;
    }

    void SetPosition(const T& position){
        _position = position;
    }

    T& Coordinate() noexcept {
        return _position;
    }

    const T& Coordinate() const noexcept {
        return _position;
    }

protected:
    char _symbol;
    T _position;
};

#endif // ABSGAMEOBJECT_H
