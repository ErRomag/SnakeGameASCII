#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <mutex>
#include <atomic>
#include <condition_variable>

#include "GameObject/Eat.h"
#include "GameObject/Snake.h"
#include "ObjectGenerator.h"

class GameEngine
{
public:
    explicit GameEngine(const int32_t width, const int32_t height);
    ~GameEngine();

    void Run();
    void Display();

private:
    Eat eat;
    Snake snake;
    std::atomic<bool> is_over;
    uint32_t score;
    int32_t field_width;
    int32_t field_height;
    ObjectGenerator objectGen;

    std::mutex mtx; // Мьютекс для синхронизации доступа к разделяемым данным
    std::condition_variable cv; // Условная переменная для уведомления о новых данных
    Direction last_dir;
    std::atomic<bool> ready; // Флаг, указывающий, что данные готовы для вывода

    void InitObjects();
    void ProcessKey();
    void ProcessCollision();
    void DrawField() const;
    void DrawGameOverScreen() const;
};

#endif // GAMEENGINE_H
