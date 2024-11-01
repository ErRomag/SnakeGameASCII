#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "GameObject/Eat.h"
#include "GameObject/Snake.h"
#include "ObjectGenerator.h"

class GameEngine
{
public:
    explicit GameEngine(const int32_t width, const int32_t height);
    ~GameEngine();

    void Run();

private:
    Eat eat;
    Snake snake;
    bool is_over;
    int32_t score;
    int32_t field_width;
    uint32_t field_height;
    ObjectGenerator objectGen;

    void ProcessKey();
    void HasCollision();
    void DrawField() const;
    void DrawGameOverScreen() const;

    Key KeyFromChar(const char input_char);
    Direction DirectionFromKey(const Key key);
};

#endif // GAMEENGINE_H
