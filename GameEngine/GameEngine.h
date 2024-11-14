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
    uint32_t score;
    int32_t field_width;
    int32_t field_height;
    ObjectGenerator objectGen;

    void ProcessKey();
    void HasCollision();
    void DrawField() const;
    void DrawGameOverScreen() const;
    void InitObjects();
};

#endif // GAMEENGINE_H
