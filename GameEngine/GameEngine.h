#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <mutex>
#include <atomic>

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
    std::mutex mtx;
    uint32_t score;
    Direction last_dir;
    int32_t field_width;
    int32_t field_height;
    std::atomic<bool> is_over;
    ObjectGenerator objectGen;

    void Display();
    void InitObjects();
    void ProcessKey();
    void ProcessCollision();
    void DrawField() const;
    void DrawGameOverScreen() const;
};

#endif // GAMEENGINE_H
