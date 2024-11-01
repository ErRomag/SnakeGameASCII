#ifndef KEY_H
#define KEY_H

#include <stdexcept>

enum Key
{
    W,
    A,
    S,
    D,
    Q
};

inline Key KeyFromChar(const char input_char)
{
    switch (input_char) {
        case 'q': return Key::Q;
        case 'w': return Key::W;
        case 'a': return Key::A;
        case 's': return Key::S;
        case 'd': return Key::D;
        default:  throw std::logic_error("Unknown input char");
    }
}

#endif // KEY_H
