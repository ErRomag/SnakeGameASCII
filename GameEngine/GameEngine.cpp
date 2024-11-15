#include "GameEngine.h"

#include <thread>
#include <iostream>

#include "Utilities/CollisionChecker.h"

GameEngine::GameEngine(const int32_t width, const int32_t height) :
    is_over(false),
    score(0),
    field_width(width),
    field_height(height),
    ready(false)
{
    InitObjects();
}

GameEngine::~GameEngine()
{

}

void GameEngine::Run()
{
    DrawField();

    std::thread displayThread(&GameEngine::Display, this);
    std::thread inputThread(&GameEngine::ProcessKey, this);

    displayThread.join();
    inputThread.join();
}

void GameEngine::Display()
{
    const int64_t draw_delay = 500;

    while (!is_over)
    {
        DrawField();
        ProcessCollision();
        {
            std::lock_guard<std::mutex> lock(mtx);
            snake.Move(last_dir);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(draw_delay));
    }

    DrawGameOverScreen();
}

void GameEngine::DrawField() const
{
    system("clear");

    bool is_space_print;
    for(int32_t h = 0; h < field_height + 2; ++h)
    {
        for(int32_t w = 0; w < field_width + 2; ++w)
        {
            is_space_print = true;
            if((w == 0) || (w == field_width + 1) ||
                    (h == 0) || (h == field_height + 1)) {
                std::cout << '#';
                continue;
            }

            if((w - 1 == eat.Coordinate().x) &&
                    (h - 1 == eat.Coordinate().y)) {
                std::cout << eat.Symbol();
                continue;
            }

            for(const Point& coord : snake.Coordinate()) {
                if((w - 1 == coord.x) && (h - 1 == coord.y)) {
                    std::cout << snake.Symbol();
                    is_space_print = false;
                }
                continue;
            }

            if(is_space_print) {
                std::cout << ' ';
            }
        }
        std::cout << "\n";
    }
    //std::cout << "Snake" << std::endl;
    //PrintObjectCoordinate(snake);
    //std::cout << "Fruit" << std::endl;
    //PrintObjectCoordinate(fruit);
    std::cout << "Score: " << score << std::endl;
}

void GameEngine::DrawGameOverScreen() const
{
    system("clear");
    std::cout << "****** GAME OVER ******" << std::endl;
    std::cout << "****** SCORE " << score << " ******" << std::endl;
}

void GameEngine::InitObjects()
{
    objectGen.Init(field_width, field_height);

    objectGen.CreateObject<Coordinates>(snake);
    do{
        objectGen.CreateObject<Point>(eat);
    } while(CollisionChecker::HasObjectsCollision(snake.Coordinate(), eat.Coordinate()));

    last_dir = objectGen.MakeRandomDir();
}

void GameEngine::ProcessKey()
{
    char input_symbol;
    while (!is_over)
    {
        std::cin >> input_symbol;
        Direction curr_dir = Left;

        Key pressed_key = KeyFromChar(input_symbol);
        switch (pressed_key)
        {
            case Key::Q: {is_over = true; break;}
            case Key::W:
            case Key::A:
            case Key::S:
            case Key::D: {
                try {
                    curr_dir = DirectionFromKey(pressed_key);
                } catch (std::logic_error) {
                    std::cout << "Unknown direction" << std::endl;
                }
                break;
            }
            default: continue;
        }

        {
            std::lock_guard<std::mutex> lock(mtx);
            last_dir = curr_dir;
        }
    }
}

void GameEngine::ProcessCollision()
{
    const uint32_t score_step = 10;

    if(CollisionChecker::HasBorderCollision(snake.Head(), field_width, field_height)) {
        std::lock_guard<std::mutex> lock(mtx);
        is_over = true;
        return;
    }

    if(CollisionChecker::HasObjectsCollision(snake.Head(), eat.Coordinate())) {
        score += score_step;
        snake.Grow();
        do{
            objectGen.CreateObject<Point>(eat);
        } while(CollisionChecker::HasObjectsCollision(snake.Coordinate(), eat.Coordinate()));
    }
}
